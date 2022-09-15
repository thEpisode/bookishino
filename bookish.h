/*
 * bookish.h
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

// Firmware
#include "src/core/firmware/firmware.h"

// Sensors
#include "src/sensors/sensor/sensor.h"
#include "src/sensors/virtual32/virtual32.h"
#include "src/sensors/virtual8266/virtual8266.h"

// Threads
#include "src/threads/template/template.thread.h"

Core::Firmware *firmware;

struct sensors
{
    /* My Sensors */
    Virtual32 *_virtual32Controller;
    Virtual8266 *_virtual8266Controller;
};

struct threads
{
    /* My Threads */
    Thread::Template *_templateThread;
}

#endif