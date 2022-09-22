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

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

namespace Core
{
    class Ble
    {
    public:
        Ble(String deviceName, String serviceUuid, String characteristicUuid, String defaultvalue);
        void startService();

    private:
        String _deviceName;
        String _serviceUuid;
        String _characteristicUuid;
        String _defaultvalue;
        BLEServer *_bleServer;
        BLEService *_bleService;
        BLECharacteristic *_bleDefaultCharacteristic;
        BLEAdvertising *_bleAdvertising;

        void initializeBleServices();
        void setupDefaultCharacteristic();
        void startBleService();
    };
} // namespace Core

#endif