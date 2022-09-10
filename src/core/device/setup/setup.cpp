/*
 * setup.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include "Arduino.h"
#include <ArduinoOTA.h>

#include "setup.h"

Setup::Setup()
{
  _localStorage = new LocalStorage();
  _settingsJson = _localStorage->read(filename);

  if (_settingsJson.length() > 0)
  {
    setProperties();
  }
}

void handleOta()
{
    ArduinoOTA.handle();
}

void startOta()
{
    Serial.println("Setting OTA password");
    ArduinoOTA.setPassword(_settingsController->settings.ota_password.c_str());

    Serial.println("Declaring OTA events");
    ArduinoOTA.onStart([]()
                       {
              String type;
              if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
              else // U_SPIFFS
                type = "filesystem";

              // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
              Serial.println("Start updating " + type); })
        .onEnd([]()
               { Serial.println("\nEnd"); })
        .onProgress([](unsigned int progress, unsigned int total)
                    { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
        .onError([](ota_error_t error)
                 {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR)
          Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)
          Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR)
          Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR)
          Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR)
          Serial.println("End Failed"); });

    Serial.println("beginning OTA");
    ArduinoOTA.begin();
}

void wifiInit()
{
    Serial.println("Setting up Wifi...");

    _wifiController = new Wifi(_settingsController->settings.device_id);
    String localIp = "";

    if (_settingsController->settings.is_wifiap_enabled == true)
    {
        _wifiController->enableAP(
            _settingsController->settings.ap_ssid,
            _settingsController->settings.ap_pass,
            _settingsController->settings.wifi_server_ip,
            _settingsController->settings.wifi_ap_gateway,
            _settingsController->settings.wifi_ap_subnet);
    }

    if (_settingsController->settings.is_macronode_role == true &&
        _settingsController->settings.is_wifi_static_ip_enabled == true)
    {
        _wifiController->setStaticIp(
            _settingsController->settings.wifi_server_ip,
            _settingsController->settings.wifi_ap_gateway,
            _settingsController->settings.wifi_ap_subnet,
            _settingsController->settings.wifi_ap_primary_dns,
            _settingsController->settings.wifi_ap_secondary_dns);
    }

    if (_settingsController->settings.is_micronode_role == true ||
        _settingsController->settings.is_radiationnode_role == true ||
        _settingsController->settings.is_weathernode_role == true)
    {
        if (_stageConfig.developerMode)
        {
            Serial.println("Connecting to Wifi as developer mode...");

            localIp = _wifiController->connect(_settingsController->settings.wifi_dev_ssid, _settingsController->settings.wifi_dev_pass);
        }
        else
        {
            Serial.println("Connecting to Wifi as production mode...");

            localIp = _wifiController->connect(_settingsController->settings.wifi_prod_ssid, _settingsController->settings.wifi_prod_pass);
        }

        startOta();
    }

    if (_settingsController->settings.is_macronode_role == true &&
        _settingsController->settings.is_wifiserver_enabled == true)
    {
        _wifiController->enableServer(80);
    }
}

void apiInit()
{
    Serial.println("Setting up Api...");

    _settingsController->settings.routes.push_back({"status", "/status", "GET"});
    _settingsController->settings.routes.push_back({"get-node", "/node", "GET"});
    _settingsController->settings.routes.push_back({"get-sensors-by-nodeid", "/sensor", "GET"});
    _settingsController->settings.routes.push_back({"post-insight", "/insight", "POST"});

    if (_stageConfig.developerMode)
    {
        _apiController = new Api(_settingsController->settings.api_dev_origin, _settingsController->settings.routes);
    }
    else
    {
        _apiController = new Api(_settingsController->settings.api_prod_origin, _settingsController->settings.routes);
    }
}

void bleInit()
{
    Serial.println("Setting up BLE...");
    _bleConfig.deviceName = "d-0012";

    _bleController = new Ble(_bleConfig.deviceName);
}

void setupCommunications()
{
    Serial.println("Setting up communications...");

    if (true == _settingsController->settings.is_ble_enabled)
    {
        bleInit();
    }

    if (true == _settingsController->settings.is_wifi_enabled)
    {
        wifiInit();

        if (_settingsController->settings.is_api_enabled)
        {
            apiInit();
        }
    }
}

void setupSensors()
{
    getSensorsByNodeId();
}

void getSensorsByNodeId()
{
    String requestRoute = "";
    String requestMethod = "";
    String response = "";

    requestRoute = _apiController->getRoute("get-sensors-by-nodeid");
    requestMethod = _apiController->getMethod("get-sensors-by-nodeid");
    Serial.println(requestMethod + " " + requestRoute + "?id=" + _settingsController->settings.device_id);
    response = _apiController->requestParameters(requestRoute, "id=" + _settingsController->settings.device_id, requestMethod);
    Serial.println(response);

    DynamicJsonDocument responseJson = _apiController->deserialize(response);
    bool success = responseJson["success"];

    if (success == true)
    {
        JsonArray result = responseJson["result"];

        for (JsonVariant sensor : result)
        {
            // FIXME: Get sensor information
            // sensor.as<Sensor>();
        }
    }
}

void enableAPServer()
{
    if (_settingsController->settings.is_wifiserver_enabled == true)
    {
        _wifiController->APServerClientHandling();
    }
}

void getDeviceInformation()
{
    /* Getting information to backend */
    Serial.println("Getting settings...");
    String requestRoute = "";
    String requestMethod = "";
    String response = "";

    requestRoute = _apiController->getRoute("get-node");
    requestMethod = _apiController->getMethod("get-node");
    Serial.println(requestMethod + " " + requestRoute + "?id=" + _settingsController->settings.device_id);
    response = _apiController->requestParameters(requestRoute, "id=" + _settingsController->settings.device_id, requestMethod);
    Serial.println(response);

    DynamicJsonDocument responseJson = _apiController->deserialize(response);
    bool success = responseJson["success"];

    if (success == true)
    {
        _settingsController->settings.is_flash_mode = false;

        /* Sensors */
        setupSensors();
    }
}

void setupStage(bool developerMode)
{
    Serial.println("Setting up stage...");
    Serial.println("Developer mode: " + developerMode ? "Yes" : "No");
    _stageConfig.developerMode = developerMode;
}

void setupDevice()
{
    Serial.println("Setting up device....");

    _settingsController = new Settings("settings.json");
}

void deviceInit()
{
    Serial.println("Loading configuration...");

    setupStage(true);
    setupDevice();

    /* Communications */
    setupCommunications();
}

