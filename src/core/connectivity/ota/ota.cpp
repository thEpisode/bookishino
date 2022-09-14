/*
 * settings.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Sep 13, 2022
 * Updated on: Sep 13, 2022
 */

#include "Arduino.h"

#include "ota.h"

using namespace Core;

Ota::Ota(String filename)
{
  _filename = filename;
}

void Ota::start()
{
    Serial.println("Setting OTA password");
    ArduinoOTA.setPassword(_settings->device_config.ota_password.c_str());

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

void Ota::handle()
{
    ArduinoOTA.handle();
}
