/*
 * setup.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef SETUP_H
#define SETUP_H

#include "Arduino.h"
#include <ArduinoJson.h>

class Setup
{
public:
  Setup();
  void deviceInit();

private:
  String _filename;
  String _settingsJson;
};

#endif
