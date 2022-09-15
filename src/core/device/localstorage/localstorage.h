/*
 * localstorage.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef LOCALSTORAGE_H
#define LOCALSTORAGE_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

namespace Core
{
    class LocalStorage
    {
    public:
        LocalStorage();
        DynamicJsonDocument deserialize(String json);
        std::string serialize(JsonObject json);
        String read(String filename);
        int overwrite(String filename, std::string payload);
        int append(std::string filename, std::string payload);

    private:
    };
} // namespace Core

#endif