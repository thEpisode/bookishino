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

        if (_wifiController->isConnected() == false)
        {
            return;
        }

        Serial.println("Static micro-node handling...");

        _ds18b20Controller = new Ds18b20(2, "sns-1234-2");  // <--- Change this id

        Serial.println("Reading sen0193...");
        String payloadSen0193 = _sen0193Controller->response();
        _wifiController->sendMessage(requestOrigin, requestRoute, payloadSen0193, requestMethod);
        delay(1000);

        // Printing data

        Serial.println("Neo6m " + payloadNeo6m);
    }
}

void macronodeRole()
{
    if (_settingsController->settings.is_macronode_role == true &&
        _settingsController->settings.is_wifiserver_enabled == true)
    {
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

    _setupController->deviceInit();
}

void loop()
{
    currentMillis = millis(); // capture the latest value of millis()
                              //   this is equivalent to noting the time from a clock
                              //   use the same time for all LED flashes to keep them synchronized

    handleOta();
    flashingMode();
    staticMode();

    delay(1);
    reset();
}
