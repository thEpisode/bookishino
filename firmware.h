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
struct firmware
{
    /* Device */
    Settings *_settingsController;
    Setup *_setupController;

    /* Communications */
    Wifi *_wifiController;
    Api *_apiController;
    Ble *_bleController;

    /* Sensors */
    Virtual32 *_virtual32Controller;
    Virtual8266 *_virtual8266Controller;

    /* Threads */
    Thread::Template *_templateThread;

    /* data */
    unsigned long currentMilliseconds = 0; // stores the value of millis() in each iteration of loop()
    unsigned long previousDeviceCycleMilliseconds = 0;
};

#endif