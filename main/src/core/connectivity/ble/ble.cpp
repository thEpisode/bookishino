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

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "ble.h"

class IncomingDefaultDataCallback : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *characteristic)
    {
        std::string value = characteristic->getValue();

        if (value.length() <= 0)
        {
            return;
        }

        Serial.println("==========");
        Serial.print("BLE value: ");
        for (int i = 0; i < value.length(); i++)
            Serial.print(value[i]);

        Serial.println();
        Serial.println("==========");
    }
};

Core::Ble::Ble(String deviceName, String serviceUuid, String characteristicUuid, String defaultvalue)
{
    _deviceName = deviceName;
    _serviceUuid = serviceUuid;
    _characteristicUuid = characteristicUuid;
    _defaultvalue = defaultvalue;
}

void Core::Ble::startService()
{
    initializeBleServices();

    setupDefaultCharacteristic();

    startBleService();
}

void Core::Ble::initializeBleServices()
{
    BLEDevice::init(_deviceName.c_str());
    _bleServer = BLEDevice::createServer();
    _bleService = _bleServer->createService(_serviceUuid.c_str());
}

void Core::Ble::setupDefaultCharacteristic()
{
    // Create a new characteristic to income data
    _bleDefaultCharacteristic = _bleService->createCharacteristic(
        _characteristicUuid.c_str(),
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);

    // Setup the callback
    _bleDefaultCharacteristic->setCallbacks(new IncomingDefaultDataCallback());

    // Set default value to characteristic
    _bleDefaultCharacteristic->setValue(_defaultvalue.c_str());
}

void Core::Ble::startBleService()
{
    // Start service
    _bleService->start();

    // Initialize BLE advertising
    _bleAdvertising = _bleServer->getAdvertising();
    _bleAdvertising->start();
}
