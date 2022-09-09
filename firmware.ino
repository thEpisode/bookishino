/*
 * firmware.ino - Sketch for flashing ESP32 micro-node.
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include "Arduino.h"
#include <ArduinoJson.h>

#include "firmware.h"




void staticSensorDevice()
{
}

void flashingMode()
{
    if (_settingsController->settings.is_flash_mode == true && _wifiController->isConnected() == true)
    {
        Serial.println("Conected to Wifi & flashing mode");
        getDeviceInformation();
        delay(_settingsController->settings.flash_mode_delay);
    }
}

void meteringMode()
{
    if (_settingsController->settings.is_metering_mode == true && _wifiController->isConnected() == true)
    {
        Serial.println("Conected to Wifi & metering mode");
        // TODO: Start metering...
        delay(_settingsController->settings.meter_mode_delay);
    }
}

void staticMode()
{
    String requestRoute = "";
    String requestMethod = "";
    String requestOrigin = "";

    requestOrigin = _apiController->getOrigin();
    requestRoute = _apiController->getRoute("post-insight");
    requestMethod = _apiController->getMethod("post-insight");

    if (_settingsController->settings.is_static_mode == false)
    {
        return;
    }

    if (currentMillis - previousStaticModeMillis >= _settingsController->settings.static_mode_delay)
    {
        previousStaticModeMillis = currentMillis;

        if (_settingsController->settings.is_micronode_role == true && _wifiController->isConnected() == true)
        {
            Serial.println("Static micro-node handling...");

            _ds18b20Controller = new Ds18b20(2, "sns-1234-2");  // <--- Change this id
            _neo6mController = new Neo6m(1, 3, "sns-1235-2");   // <--- Change this id
            _sen0193Controller = new Sen0193(34, "sns-1236-2"); // <--- Change this id

            Serial.println("Reading sen0193...");
            String payloadSen0193 = _sen0193Controller->response();
            _wifiController->sendMessage(requestOrigin, requestRoute, payloadSen0193, requestMethod);
            delay(1000);

            Serial.println("Reading ds18b20...");
            String payloadDs18b20 = _ds18b20Controller->response();
            _wifiController->sendMessage(requestOrigin, requestRoute, payloadDs18b20, requestMethod);
            delay(1000);

            Serial.println("Reading neo6m...");
            String payloadNeo6m = _neo6mController->response();
            _wifiController->sendMessage(requestOrigin, requestRoute, payloadNeo6m, requestMethod);

            // Printing data

            Serial.println("Neo6m " + payloadNeo6m);
            /* Serial.println("DS18B20 " + payloadDs18b20);
            Serial.println("Sen0193 " + payloadSen0193);
            */
        }
        else if (_settingsController->settings.is_radiationnode_role == true && _wifiController->isConnected() == true)
        {
            Serial.println("Static radiation-node handling...");

            _pdvp8001Controller = new Pdvp8001(35, "sns-1238-1"); // <--- Change this id
            _veml6075Controller = new Veml6075("sns-1239-1");     // <--- Change this id

            Serial.println("Reading pdvp8001...");
            String payloadPdvp8001 = _pdvp8001Controller->response();
            _wifiController->sendMessage(requestOrigin, requestRoute, payloadPdvp8001, requestMethod);
            delay(1000);

            Serial.println("Reading veml6075...");
            String payloadVeml6075 = _veml6075Controller->response();
            _wifiController->sendMessage(requestOrigin, requestRoute, payloadVeml6075, requestMethod);
            delay(1000);
        }
        else if (_settingsController->settings.is_weathernode_role == true && _wifiController->isConnected() == true)
        {
            Serial.println("Static weather-node handling...");

            // TODO: Implement code for weather station
        }
        else if (_settingsController->settings.is_macronode_role == true && _loraController->isConnected() == true)
        {
            Serial.println("Static macro-node handling...");
            if (!_am2315Controller)
            {
                _am2315Controller = new Am2315("sns-1237-1"); // <--- Change this id
            }

            // Reading data
            Serial.println("Reading am2315...");
            String responseam = _am2315Controller->response();
            Serial.println("Readed am2315...");
            delay(1);

            _loraController->sendMessage(responseam, 0xF3);
            //_wifiController->sendMessage(requestRoute, responseam, requestMethod);

            // Printing data
            Serial.println("Am2315: " + responseam);
        }
    }
}

void macronodeRole()
{
    if (_settingsController->settings.is_macronode_role == true &&
        _settingsController->settings.is_wifiserver_enabled == true)
    {
        //_loraController->sendMessage("Hola", 0xF3);
        _wifiController->APServerClientHandling();
    }
}

void reset()
{
    if (currentMillis - previousResetMillis >= _settingsController->settings.restart_delay)
    {
        ESP.restart();
    }
}

void handleOta()
{
    ArduinoOTA.handle();
}

void startOta()
{
    Serial.println("Setting OTA password");
    // ArduinoOTA.setPassword(_settingsController->settings.ota_password.c_str());

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

void setup()
{
    Serial.begin(9600);

    deviceInit();
}

void loop()
{
    currentMillis = millis(); // capture the latest value of millis()
                              //   this is equivalent to noting the time from a clock
                              //   use the same time for all LED flashes to keep them synchronized

    handleOta();
    flashingMode();
    staticMode();
    meteringMode();
    macronodeRole();

    delay(1);
    reset();
}
