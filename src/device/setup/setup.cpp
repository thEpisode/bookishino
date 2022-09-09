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
        _wifiController->enableServer(80, _loraController);
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

void loraInit()
{
    Serial.println("Setting up LoRa...");
    _loraConfig.address = 0xB0;
    _loraConfig.csPin = 5;
    _loraConfig.resetPin = 14;
    _loraConfig.irqPin = 2;
    _loraConfig.listenMessages = true;
    _loraConfig.type = lora_type::transceiver;
    _loraConfig.frequency = 866000000;

    _loraController = new Lora(
        _loraConfig.csPin,
        _loraConfig.resetPin,
        _loraConfig.irqPin,
        _loraConfig.address,
        _loraConfig.listenMessages,
        _loraConfig.frequency);
}

void setupCommunications()
{
    Serial.println("Setting up communications...");

    if (true == _settingsController->settings.is_ble_enabled)
    {
        bleInit();
    }

    if (true == _settingsController->settings.is_lora_enabled)
    {
        loraInit();
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