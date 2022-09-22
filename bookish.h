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

#ifndef BOOKISH_H
#define BOOKISH_H

// System libraries
#include <ArduinoJson.h>

// Firmware
#include "src/core/firmware/firmware.h"

// Typos
#include "typos.h"

Core::Firmware *firmware;

struct sensors_typo sensors;
struct threads_typo threads;

#endif