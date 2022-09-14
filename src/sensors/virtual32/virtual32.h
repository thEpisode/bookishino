/*
 * virtual32.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef VIRTUAL32_H
#define VIRTUAL32_H

#include "Arduino.h"

class Virtual32
{
public:
    Virtual32(int inputPin, String sensorId);
    float read();
    String response();

private:
    int _pin;
    const String _sensorName = "virtual32";
    String _sensorId;
};

#endif
