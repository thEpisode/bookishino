/*
 * ota.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Sep 13, 2022
 * Updated on: Sep 13, 2022
 */

#pragma once

#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <ArduinoOTA.h>

#include "../settings/settings.h"

namespace Core
{
    class Ota
    {
    public:
        Ota(Settings *settings);
        void Ota::handle();
        void Ota::start();

    private:
        String _password;
    };
} // namespace Core

#endif
