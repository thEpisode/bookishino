/*
 * firmware.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Sep 15, 2022
 * Updated on: Sep 15, 2022
 */

#include "firmware.h"

/// @brief Constructor
Core::Firmware::Firmware()
{
}

/* Null, because instance will be initialized on demand. */
Core::Firmware *Core::Firmware::instance = 0;

/// @brief Validate if exist current instance or not
/// @return Instance
Core::Firmware *Core::Firmware::getInstance()
{
    if (instance == 0)
    {
        instance = new Firmware();
    }

    return instance;
}

Core::Backend* Core::Firmware::backend()
{
    return this->_backend;
}

void Core::Firmware::setBackend(String origin, std::vector<Core::route_typo> routes)
{
    this->_backend = new Core::Backend(origin, routes);
}

Core::Ble* Core::Firmware::ble()
{
    return this->_ble;
}

void Core::Firmware::setBle(String deviceName, String serviceUuid, String characteristicUuid, String defaultvalue)
{
    this->_ble = new Core::Ble(deviceName, serviceUuid, characteristicUuid, defaultvalue);
}

Core::Ota* Core::Firmware::ota()
{
    return this->_ota;
}

void Core::Firmware::setOta()
{
    this->_ota = new Core::Ota(this->settings()->device.ota_password);
}

Core::Wifi* Core::Firmware::wifi()
{
    return this->_wifi;
}

void Core::Firmware::setWifi()
{
    this->_wifi = new Core::Wifi();
}

Core::LocalStorage* Core::Firmware::localStorage()
{
    return this->_localStorage;
}

void Core::Firmware::setLocalStorage()
{
    this->_localStorage = new Core::LocalStorage();
}

Core::Operations* Core::Firmware::operations()
{
    return this->_operations;
}

void Core::Firmware::setOperations()
{
    this->_operations = new Core::Operations();
}

Core::Settings* Core::Firmware::settings()
{
    return this->_settings;
}

void Core::Firmware::setSettings()
{
    this->_settings = new Core::Settings(this->_settings->device.settings_filename);
}

Core::Setup* Core::Firmware::setup()
{
    return this->_setup;
}

void Core::Firmware::setSetup()
{
    this->_setup = new Core::Setup();
}