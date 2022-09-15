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

Core::Backend backend()
{
    return this->_backend;
}

void setBackend(String origin, std::vector<Core::route> routes)
{
    this->_backend = new Core::Backend(origin, routes);
}

Core::Ble ble()
{
    return this->_ble;
}

void setBle(std::string deviceName, std::string serviceUuid, std::string characteristicUuid, std::string defaultvalue)
{
    this->_ble = new Core::Ble(deviceName, serviceUuid, characteristicUuid, defaultvalue);
}

Core::Ota ota()
{
    return this->_ota;
}

void setOta()
{
    this->_ota = new Core::Ota();
}

Core::Wifi wifi()
{
    return this->_wifi;
}

void setWifi()
{
    this->_wifi = new Core::Wifi();
}

Core::LocalStorage localStorage()
{
    return this->_localStorage;
}

void setLocalStorage()
{
    this->_localStorage = new Core::LocalStorage();
}

Core::Operations operations()
{
    return this->_operations;
}

void setOperations()
{
    this->_operations = new Core::Operations();
}

Core::Settings settings()
{
    return this->_settings;
}

void setSettings()
{
    this->_settings = new Core::Settings();
}

Core::Setup setup()
{
    return this->_setup;
}

void setSetup()
{
    this->_setup = new Core::Setup();
}