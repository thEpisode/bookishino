/*
 * wifi.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <WiFi.h>

#include "../../../../firmware.h"
#include "../../device/settings/settings.h"

typedef struct wifi_credentials
{
    char *ssid;
    char *pass;
};

namespace Core
{
    class Wifi
    {
    public:
        Wifi();
        String connect(String ssid, String password);
        bool isConnected();
        void enableAccessPoint(String ssid, String password, int localIp[], int gateway[], int subnet[]);
        void enableServer(int port);
        void setStaticIp(int localIp[], int gateway[], int subnet[], int primaryDNS[], int secondaryDNS[]);
        void sendMessage(String origin, String endpoint, String payload, String method);
        void APServerClientHandling();

    private:
        Core::Firmware *firmware;
        Settings *_settings;

        String _deviceId;
        String _ssid;
        String _password;
        WebServer *_server;

        void handleRoot();
        void handleAPI();
        void handleNotFound();
    };
} // namespace Core

#endif