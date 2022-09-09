/*
 * ble.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */
// https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "ble.h"

Ble::Ble(std::string deviceName)
{
  _deviceName = deviceName;
  createServer();
}

void Ble::createServer()
{
  BLEDevice::init(_deviceName);
  _bleServer = BLEDevice::createServer();

  BLEDevice::startAdvertising();
}

void Ble::createService(std::string serviceUuid, std::string characteristicUuid, std::string value)
{
  BLEService *bleService = _bleServer->createService(serviceUuid);
  BLECharacteristic *bleCharacteristic = bleService->createCharacteristic(
      characteristicUuid,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  bleCharacteristic->setValue(value);
  bleService->start();

  BLEAdvertising *bleAdvertising = BLEDevice::getAdvertising();
  bleAdvertising->addServiceUUID(serviceUuid);
  bleAdvertising->setScanResponse(true);
  bleAdvertising->setMinPreferred(0x06); // functions that help with iPhone connections issue
  bleAdvertising->setMinPreferred(0x12);
  BLEDevice::getAdvertising()->stop();
  delay(200);
  BLEDevice::startAdvertising();
}