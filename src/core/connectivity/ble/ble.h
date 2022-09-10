/*
 * ble.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef BLE_H
#define BLE_H

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class Ble
{
public:
  Ble(std::string deviceName);
  void createServer();
  void createService(std::string serviceUuid, std::string characteristicUuid, std::string value);

private:
  std::string _deviceName;
  BLEServer *_bleServer;
};

#endif