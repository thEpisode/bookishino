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
    typedef struct route_typo
    {
        String name;
        String endpoint;
        String method;
    };

    class Settings
    {
    public:
        Settings(String filename);
        void setProperties();
        void setIsDeveloperMode(bool developerMode);

        typedef struct device_config
        {
            /* Communications */
            // WIFI
            bool is_wifi_enabled = true;
            bool is_wifi_static_ip_enabled = false;
            int wifi_server_ip[4] = {192, 168, 1, 2};
            String wifi_prod_ssid = "Bookish default prod ssid";
            String wifi_prod_pass = "B00k1sh";
            String wifi_dev_ssid = "Bookish default dev ssid";
            String wifi_dev_pass = "B00k1sh";

            // Server
            bool is_server_enabled = false;
            int server_port = 80;

            // Backend services
            bool is_backend_enabled = true;
            String api_dev_origin = "192.168.1.2";
            String api_prod_origin = "api.bookish.com";

            // WIFI Access Point
            bool is_wifiap_enabled = false;
            String ap_ssid = "Bookish default ssid";
            String ap_pass = "B00k1sh";
            int wifi_ap_gateway[4] = {192, 168, 1, 254};
            int wifi_ap_subnet[4] = {255, 255, 255, 0};
            int wifi_ap_primary_dns[4] = {8, 8, 8, 8};
            int wifi_ap_secondary_dns[4] = {8, 8, 4, 4};

            // Bluetooth Low Energy (BLE)
            bool is_ble_enabled = true;
            String service_uuid = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
            String characteristic_uuid = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
            String default_value = "my_default_value";

            // Over The Air (OTA)
            bool is_ota_enabled = true;
            String ota_password = "B00k1sh_4dm1n_OTA";

            // Developer
            bool is_developer_mode = true;

            /* Device */
            long main_thread_cycle = 100;
            String device_id = "nod-1c29d6b882";
            String device_name = "d-0012";
            String settings_filename = "settings.json";

            std::vector<Core::route_typo> backend_routes;
            std::vector<Sensor::sensor_typo> sensors;
        };

        struct device_config device;

    private:
        String _filename;
        String _settingsJson;
        LocalStorage *_localStorage;
    };
} // namespace Core

#endif