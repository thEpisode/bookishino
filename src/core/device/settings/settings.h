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

#include <Arduino.h>
#include <ArduinoJson.h>

#include "../localstorage/localstorage.h"
#include "../../connectivity/backend/backend.h"
#include "../../../sensors/sensor/sensor.h"

namespace Core
{
    class Settings
    {
    public:
        Settings(String filename);
        void setProperties();

        typedef struct device_config
        {
            /* Communications */
            // WIFI
            const bool is_wifi_enabled = true;
            const bool is_wifi_static_ip_enabled = false;
            const int wifi_server_ip[4] = {192, 168, 1, 2};
            const String wifi_prod_ssid = "Bookish default prod ssid";
            const String wifi_prod_pass = "B00k1sh";
            const String wifi_dev_ssid = "Bookish default dev ssid";
            const String wifi_dev_pass = "B00k1sh";

            // Server
            const bool is_server_enabled = false;
            const int server_port = 80;

            // Backend services
            const bool is_backend_enabled = true;
            const String api_dev_origin = "192.168.1.2";
            const String api_prod_origin = "api.bookish.com";

            // WIFI Access Point
            const bool is_wifiap_enabled = false;
            const String ap_ssid = "Bookish default ssid";
            const String ap_pass = "B00k1sh";
            const int wifi_ap_gateway[4] = {192, 168, 1, 254};
            const int wifi_ap_subnet[4] = {255, 255, 255, 0};
            const int wifi_ap_primary_dns[4] = {8, 8, 8, 8};
            const int wifi_ap_secondary_dns[4] = {8, 8, 4, 4};

            // Bluetooth Low Energy (BLE)
            const bool is_ble_enabled = true;
            const String service_uuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
            const String characteristic_uuid = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
            const String default_value = "my_default_value";

            // Over The Air (OTA)
            const bool is_ota_enabled = true;
            const String ota_password = "B00k1sh_4dm1n_OTA";

            // Developer
            const bool is_developer_mode = true;

            /* Device */
            const long main_thread_cycle = 100;
            const String device_id = "nod-1c29d6b882";
            const String device_name = "d-0012";
            const String settings_filename = "settings.json";

            const std::vector<Core::route> backend_routes;
            const std::vector<Sensor> sensors;
        };

        struct device_config device;

    private:
        String _filename;
        String _settingsJson;
        LocalStorage *_localStorage;
    };
} // namespace Core

#endif