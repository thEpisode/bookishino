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

#include "../../device/settings/settings.h"

namespace Core
{
    class Ota
    {
    public:
        Ota(String password);
        void handle();
        void start();

    private:
        String _password;

        void setupOta();
        void setupAdminPassword();
        void setupEvents();
        void otaOnStart();
        void otaOnEnd();
        void otaOnProgress(unsigned int progress, unsigned int total);
        void otaOnError(ota_error_t error);
    };
} // namespace Core

#endif
