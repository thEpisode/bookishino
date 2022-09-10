/*
 * api.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include "Arduino.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "api.h"

Api::Api(String origin, std::vector<route> routes)
{
    _origin = origin;
    _routes = routes;
}

DynamicJsonDocument Api::deserialize(String json)
{
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json.c_str());

    return doc;
}

std::string Api::serialize(JsonObject json)
{
    StaticJsonDocument<1024> doc;

    for (JsonObject::iterator it = json.begin(); it != json.end(); ++it)
    {
        doc[it->key()] = it->value();
    }
    std::string jsonSerialized;
    serializeJson(doc, jsonSerialized);

    return jsonSerialized;
}

String Api::requestPayload(String endpoint, String payload, String method)
{
    int httpCode = 0;
    HTTPClient http;

    http.begin(_origin + endpoint + "");
    http.addHeader("Content-Type", "application/json");

    if (method == "GET")
    {
        httpCode = http.GET();
    }
    else if (method == "POST")
    {
        httpCode = http.POST(payload);
    }
    else if (method == "PATCH")
    {
        httpCode = http.PATCH(payload);
    }
    String response = http.getString();
    http.end();

    return response;
}

String Api::requestParameters(String endpoint, String parameters, String method)
{
    int httpCode = 0;
    HTTPClient http;

    http.begin(endpoint + "?" + parameters);

    if (method == "GET")
    {
        httpCode = http.GET();
    }
    else if (method == "POST")
    {
        http.addHeader("Content-Type", "application/json");
        httpCode = http.POST(parameters);
    }
    else if (method == "PATCH")
    {
        http.addHeader("Content-Type", "application/json");
        httpCode = http.PATCH(parameters);
    }
    String response = http.getString();
    http.end();

    return response;
}

String Api::getRoute(String name)
{
    String path = "";

    for (std::vector<int>::size_type i = 0; i != _routes.size(); i++)
    {
        if (_routes[i].name == name)
        {
            path = _routes[i].endpoint;
            break;
        }
    }

    return path;
}

String Api::getOrigin()
{
    return _origin;
}

String Api::getMethod(String name)
{
    String method = "";

    for (std::vector<int>::size_type i = 0; i != _routes.size(); i++)
    {
        if (_routes[i].name == name)
        {
            method = _routes[i].method;
            break;
        }
    }

    return method;
}
