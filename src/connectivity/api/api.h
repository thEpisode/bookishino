/*
 * api.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#include <string>
#include <vector>

#include "Arduino.h"
#include <ArduinoJson.h>
#include <WiFi.h>

#ifndef API_H
#define API_H

struct route
{
  String name;
  String endpoint;
  String method;
};

class Api
{
public:
  Api(String origin, std::vector<route> routes);
  DynamicJsonDocument deserialize(String json);
  std::string serialize(JsonObject json);
  String requestPayload(String endpoint, String payload, String method);
  String requestParameters(String endpoint, String parameters, String method);
  String getRoute(String name);
  String getMethod(String name);
  void handleAPServerRoutes(WiFiClient client /* , Lora &_loraController */);
  String getOrigin();

private:
  String _origin;
  String _endpoint;
  std::vector<route> _routes;
};

#endif
