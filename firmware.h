/*
 * firmware.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef FIRMWARE_H
#define FIRMWARE_H

// System libraries
#include <ArduinoJson.h>

// Device
#include "src/device/localstorage/localstorage.h"
#include "src/device/settings/settings.h"
#include "src/device/setup/setup.h"

// Conectivity
#include "src/connectivity/api/api.h"
#include "src/connectivity/ble/ble.h"
#include "src/connectivity/wifi/wifi.h"

// Sensors
#include "src/sensors/sensor/sensor.h"
#include "src/sensors/virtual32/virtual32.h"
#include "src/sensors/virtual8266/virtual8266.h"

// Threads
#include "src/threads/template/template.thread.h"

// Structs

struct stage_config
{
    bool developerMode;
} _stageConfig;

struct device_config
{
    bool is_wifi_enabled;
    bool is_ble_enabled;
    bool is_api_enabled;
    bool is_flash_mode;
    long flash_mode_delay;
    String device_id;
    String settings_filename;
    std::vector<route> routes;
} _deviceConfig;

struct api_origin
{
    String origin;
} _apiProduction, _apiDev;

struct ble_config
{
    std::string deviceName;
} _bleConfig;

/* Device */
Settings *_settingsController;
Setup *_setupController;

/* Communications */
Wifi *_wifiController;
Api *_apiController;
Ble *_bleController;

wifi_credentials _wifiProd;
wifi_credentials _wifiDev;

/* Sensors */
Virtual32 *_virtual32Controller;
Virtual8266 *_virtual8266Controller;

unsigned long currentMilliseconds = 0; // stores the value of millis() in each iteration of loop()
unsigned long previousDeviceCycleMilliseconds = 0;

/* Threads */
Thread::Template *_templateThread;

#endif