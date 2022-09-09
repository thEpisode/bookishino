/*
 * virtual8266.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef VIRTUAL8266_H
#define VIRTUAL8266_H

#include "Arduino.h"

class Virtual8266
{
public:
  Virtual8266(int inputPin, String sensorId);
  float read();
  String response();

private:
  int _pin;
  const String _sensorName = "Virtual8266";
  String _sensorId;
};

#endif