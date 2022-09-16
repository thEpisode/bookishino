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

#ifndef SETUPP_H
#define SETUPP_H

#include <Arduino.h>
#include <ArduinoJson.h>

#include "../../../../bookish.h"
#include "../../firmware/firmware.h"
#include "../settings/settings.h"
#include "../../connectivity/backend/backend.h"
#include "../../connectivity/ble/ble.h"
#include "../../connectivity/wifi/wifi.h"

namespace Core
{
    class Setup
    {
    public:
        Setup();
        void setupDevice();

    private:
        // Default properties
        Core::Firmware *firmware;
        Settings *_settings;
        
        // Custom properties
        Backend *_backend;
        Ble *_ble;
        Wifi *_wifi;
        String _filename;
        String _settingsJson;
    };
} // namespace Core

#endif
