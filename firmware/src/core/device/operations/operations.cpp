/*
 * settings.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Sep 13, 2022
 * Updated on: Sep 13, 2022
 */

#include <Arduino.h>

#include "operations.h"

Core::Operations::Operations()
{
}

void Core::Operations::reset()
{
    ESP.restart();
}

void Core::Operations::enableAPServer()
{
    if (_settingsController->settings.is_server_enabled == true)
    {
        _wifiController->APServerClientHandling();
    }
}
