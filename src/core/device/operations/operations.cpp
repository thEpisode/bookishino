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

using namespace Core;

Operations::Operations()
{
}

void Operations::reset()
{
    ESP.restart();
}

void Operations::enableAPServer()
{
    if (_settingsController->settings.is_wifiserver_enabled == true)
    {
        _wifiController->APServerClientHandling();
    }
}
