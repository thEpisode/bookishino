/*
 * settings.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include "Arduino.h"
#include <ArduinoJson.h>
#include "../localstorage/localstorage.h"
#include "../../connectivity/api/api.h"
#include "../../sensors/sensor/sensor.h"

class Settings
{
public:
  Settings(String filename);
  void setProperties();

  typedef struct device_config
  {
    // Micro-node
    static bool is_wifi_enabled = true;
    static bool is_ble_enabled = true;
    static bool is_api_enabled = true;
    static bool is_flash_mode = false;
    static bool is_wifiap_enabled = false;
    static bool is_metering_mode = false;
    static bool is_macronode_role = false;
    static bool is_micronode_role = true;
    static bool is_radiationnode_role = false;
    static bool is_weathernode_role = false;
    static bool is_wifiserver_enabled = false;
    static bool is_wifi_static_ip_enabled = false;

    static long main_thread_cycle = 100;
    static int wifi_server_ip[4] = {192, 168, 1, 2};
    static int wifi_ap_gateway[4] = {192, 168, 1, 254};
    static int wifi_ap_subnet[4] = {255, 255, 255, 0};
    static int wifi_ap_primary_dns[4] = {8, 8, 8, 8};
    static int wifi_ap_secondary_dns[4] = {8, 8, 4, 4};
    static String device_id = "nod-1c29d6b882";
    static String settings_filename = "settings.json";
    static String ap_ssid = "Bookish default ssid";
    static String ap_pass = "B00k1sh";
    static String wifi_prod_ssid = "Bookish default ssid";
    static String wifi_prod_pass = "B00k1sh";
    static String api_dev_origin = "192.168.1.2";
    static String api_prod_origin = "192.168.1.2";
    static String ota_password = "B00k1sh_4dm1n_OTA";
    static std::vector<route> routes;
    static std::vector<Sensor> sensors;
  };

  struct device_config settings;

private:
  String _filename;
  String _settingsJson;
  LocalStorage *_localStorage;
};

#endif