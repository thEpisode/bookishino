/*
 * localstorage.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include "Arduino.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>

#include "localstorage.h"

LocalStorage::LocalStorage()
{
  if (!SPIFFS.begin(true))
  {
    return;
  }
}

DynamicJsonDocument LocalStorage::deserialize(String json)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, json.c_str());

  return doc;
}

std::string LocalStorage::serialize(JsonObject json)
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

String LocalStorage::read(String filename)
{
  String content = "";
  filename = "/" + filename;
  File file = SPIFFS.open(filename, "r");

  if (!file)
  {
    return "";
  }

  while (file.available())
  {
    content += (char)file.read();
  }

  file.close();
  return content;
}

int LocalStorage::overwrite(String filename, std::string payload)
{
  int error = 0;
  filename = "/" + filename;
  char *payloadChar = new char[strlen(payload.c_str())];

  if (!SPIFFS.exists(filename))
  {
    error = -3;
  }

  strcpy(payloadChar, payload.c_str());
  File file = SPIFFS.open(filename, "w+");

  if (!file)
  {
    error = -2;
  }

  if (!file.print(payloadChar))
  {
    error = -1;
  }

  file.close();
  return error;
}

int LocalStorage::append(std::string filename, std::string payload)
{
  int error = 0;
  filename = "/" + filename;
  char *payloadChar = new char[strlen(payload.c_str())];

  if (!SPIFFS.exists(filename.c_str()))
  {
    error = -3;
  }

  strcpy(payloadChar, payload.c_str());
  File file = SPIFFS.open(filename.c_str(), "a+");

  if (!file)
  {
    error = -2;
  }

  if (!file.print(payloadChar))
  {
    error = -1;
  }

  file.close();
  return error;
}
