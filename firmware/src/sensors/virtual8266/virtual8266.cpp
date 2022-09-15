/*
 * virtual8266.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include <Arduino.h>

#include "virtual8266.h"

Virtual8266::Virtual8266(int inputPin, String sensorId)
{
    _pin = inputPin;
    _sensorId = sensorId;
}

float Virtual8266::read()
{
    randomSeed(_pin);
    long randomNumber = random(1, 100);
    return float(randomNumber);
}

String Virtual8266::response()
{
    String payload = "{";
    payload += "\"success\": \"true\",";
    payload += "\"result\": {";
    payload += "\"sensorId\": \"" + _sensorId + "\",";
    payload += "\"sensorName\": \"" + _sensorName + "\",";
    payload += "\"payload\": {";
    payload += "\"value_variant_1\": " + String(read()) + ",";
    payload += "\"value_variant_2\": " + String(read());
    payload += "}";
    payload += "},";
    payload += "\"message\": \"Operation completed succesfully\"";
    payload += "}";

    return payload;
}