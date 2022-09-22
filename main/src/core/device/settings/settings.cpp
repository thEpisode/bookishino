/*
 * settings.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include <Arduino.h>
#include <HTTPClient.h>

#include "settings.h"
#include <ArduinoJson.h>
#include "../localstorage/localstorage.h"

Core::Settings::Settings(String settings_filename)
{
    _filename = device.settings_filename;
    _localStorage = new LocalStorage();
    _settingsJson = _localStorage->read(_filename);

    if (_settingsJson.length() > 0)
    {
        setProperties();
    }
}

void Core::Settings::setProperties()
{
    // FIXME: Set the settings
    /* DynamicJsonDocument doc(1024);
    deserializeJson(doc, _settingsJson.c_str());

    settings.device_id = doc["id"];
    settings.is_wifi_enabled = doc["is_wifi_enabled"];
    settings.is_backend_enabled = doc["is_backend_enabled"];
    settings.is_ble_enabled = doc["is_ble_enabled"];
    settings.is_flash_mode = doc["is_flash_mode"];
    settings.settings_filename = doc["settings_filename"];
    settings.flash_mode_delay = doc["flash_mode_delay"]; */
}

void Core::Settings::setIsDeveloperMode(bool developerMode)
{
    device.is_developer_mode = developerMode;
}