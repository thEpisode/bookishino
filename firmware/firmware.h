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
#include "src/core/device/localstorage/localstorage.h"
#include "src/core/device/settings/settings.h"
#include "src/core/device/setup/setup.h"

// Conectivity
#include "src/core/connectivity/backend/backend.h"
#include "src/core/connectivity/ble/ble.h"
#include "src/core/connectivity/wifi/wifi.h"

// Sensors
#include "src/sensors/sensor/sensor.h"
#include "src/sensors/virtual32/virtual32.h"
#include "src/sensors/virtual8266/virtual8266.h"

// Threads
#include "src/threads/template/template.thread.h"

// Structs
struct firmware_dependencies
{
    /* Device */
    Core::Settings *_settings;
    Core::Setup *_setup;

    /* Communications */
    Core::Wifi *_wifi;
    Core::Backend *_backend;
    Core::Ble *_ble;

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