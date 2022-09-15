/*
 * settings.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Sep 13, 2022
 * Updated on: Sep 13, 2022
 */

#include <Arduino.h>
#include <ArduinoOTA.h>

#include "ota.h"

Core::Ota::Ota(String password)
{
    _password = password;

    setupOta();
}

void Core::Ota::setupOta()
{
    setupAdminPassword();

    setupEvents();

    // Starting services
    ArduinoOTA.begin();
}

void Core::Ota::handle()
{
    ArduinoOTA.handle();
}

void Core::Ota::setupAdminPassword()
{
    Serial.println("Setting OTA password...");
    ArduinoOTA.setPassword(_password.c_str());
}

void Core::Ota::setupEvents()
{
    Serial.println("Declaring OTA events...");

    // Declaration of start event
    ArduinoOTA.onStart(&Core::Ota::otaOnStart);

    // Declaration of end event
    ArduinoOTA.onEnd(&Core::Ota::otaOnEnd);

    // Declaration of progress event
    ArduinoOTA.onProgress(&Core::Ota::otaOnProgress);

    // Declaration of error event
    ArduinoOTA.onError(&Core::Ota::otaOnError);

    Serial.println("beginning OTA service...");
}

// typedef THandlerFunction: https://github.com/esp8266/Arduino/blob/master/libraries/ArduinoOTA/ArduinoOTA.h
THandlerFunction Core::Ota::otaOnStart()
{
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
        type = "sketch";
    }
    else
    { // U_SPIFFS
        type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
}

THandlerFunction Core::Ota::otaOnEnd()
{
    Serial.println("\nEnd");
}

THandlerFunction_Progress Core::Ota::otaOnProgress(unsigned int progress, unsigned int total)
{
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
}

THandlerFunction_Error Core::Ota::otaOnError(ota_error_t error)
{
    Serial.printf("OTA Service Error[%u]: ", error);

    switch (error)
    {
    case OTA_AUTH_ERROR:
        Serial.println("OTA Service: Auth Failed");
        break;
    case OTA_BEGIN_ERROR:
        Serial.println("OTA Service: Begin Failed");
        break;
    case OTA_CONNECT_ERROR:
        Serial.println("OTA Service: Connect Failed");
        break;
    case OTA_RECEIVE_ERROR:
        Serial.println("OTA Service: Receive Failed");
        break;
    case OTA_END_ERROR:
        Serial.println("OTA Service: End Failed");
        break;
    default:
        Serial.println("OTA Service: Unknown Failed");
        break;
    }
}