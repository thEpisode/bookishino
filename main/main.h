/*
 * main.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef BOOKISH_H
#define BOOKISH_H

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

// Typos
#include "typos.h"

Core::Firmware *firmware;

typedef struct sensors_typo
{
    /* My Sensors */
    Sensor::Virtual32 *_virtual32Controller;
    Sensor::Virtual8266 *_virtual8266Controller;
};

typedef struct threads_typo
{
    /* My Threads */
    Thread::Template *_templateThread;
};

sensors_typo sensors;
threads_typo threads;

#endif