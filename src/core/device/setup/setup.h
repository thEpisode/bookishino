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

#include <Arduino.h>
#include <ArduinoJson.h>

#include "../settings/settings.h"
#include "../../connectivity/backend/backend.h"
#include "../../connectivity/ble/ble.h"
#include "../../connectivity/wifi/wifi.h"
#include "../../../../firmware.h"

namespace Core
{
    class Setup
    {
    public:
        Setup(firmware_dependencies &dependencies);
        void setupDevice();

    private:
        String _filename;
        String _settingsJson;
        Settings *_settings;
        Backend *_backend;
        Ble *_ble;
        Wifi *_wifi;
    };
} // namespace Core

#endif
