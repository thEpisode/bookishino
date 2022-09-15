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
            static bool is_wifi_enabled = true;
            static bool is_wifi_static_ip_enabled = false;
            static int wifi_server_ip[4] = {192, 168, 1, 2};
            static String wifi_prod_ssid = "Bookish default prod ssid";
            static String wifi_prod_pass = "B00k1sh";
            static String wifi_dev_ssid = "Bookish default dev ssid";
            static String wifi_dev_pass = "B00k1sh";

            // Server
            static bool is_server_enabled = false;
            static int server_port = 80;

            // Backend services
            static bool is_backend_enabled = true;
            static String api_dev_origin = "192.168.1.2";
            static String api_prod_origin = "api.bookish.com";

            // WIFI Access Point
            static bool is_wifiap_enabled = false;
            static String ap_ssid = "Bookish default ssid";
            static String ap_pass = "B00k1sh";
            static int wifi_ap_gateway[4] = {192, 168, 1, 254};
            static int wifi_ap_subnet[4] = {255, 255, 255, 0};
            static int wifi_ap_primary_dns[4] = {8, 8, 8, 8};
            static int wifi_ap_secondary_dns[4] = {8, 8, 4, 4};

            // Bluetooth Low Energy (BLE)
            static bool is_ble_enabled = true;
            static String service_uuid "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
            static String characteristic_uuid "beb5483e-36e1-4688-b7f5-ea07361b26a8";

            // Over The Air (OTA)
            static bool is_ota_enabled = true;
            static String ota_password = "B00k1sh_4dm1n_OTA";

            // Developer
            static bool is_developer_mode = true;

            /* Device */
            static long main_thread_cycle = 100;
            static String device_id = "nod-1c29d6b882";
            static String device_name = "d-0012";
            static String settings_filename = "settings.json";

            static std::vector<Core::route> backend_routes;
            static std::vector<Sensor> sensors;
        };

        struct device_config settings;

    private:
        String _filename;
        String _settingsJson;
        LocalStorage *_localStorage;
    };
} // namespace Core

#endif