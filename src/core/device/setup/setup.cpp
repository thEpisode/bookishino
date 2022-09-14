/*
 * setup.cpp
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include <Arduino.h>
#include <ArduinoOTA.h>

#include "setup.h"

using namespace Core;

Setup::Setup(
    Settings *settings
    Api *api)
{
    _settings = settings;
    _api = api;
}

/*
 * Initialize configurations and start all services.
 *
 * @return {void}
 */
void setupDevice()
{
    setupStage();
    setupCommunications();
}

void setupCommunications()
{
    Serial.println("Setting up communications...");

    if (true == _settings->device_config.is_ble_enabled)
    {
        bleInit();
    }

    if (true == _settings->device_config.is_wifi_enabled)
    {
        wifiInit();

        if (_settings->device_config.is_api_enabled)
        {
            apiInit();
        }
    }
}

void bleInit()
{
    Serial.println("Setting up BLE...");

    _bleController = new Ble(_settings->device_config.device_name);
}

void wifiInit()
{
    Serial.println("Setting up Wifi...");

    _wifiController = new Wifi(_settings->device_config.device_id);
    String localIp = "";

    if (_settings->device_config.is_wifiap_enabled == true)
    {
        // Enable Access Point
        _wifiController->enableAccessPoint(
            _settings->device_config.ap_ssid,
            _settings->device_config.ap_pass,
            _settings->device_config.wifi_server_ip,
            _settings->device_config.wifi_ap_gateway,
            _settings->device_config.wifi_ap_subnet);
    }

    if (_settings->device_config.is_wifi_static_ip_enabled == true)
    {
        // Enable static IP
        _wifiController->setStaticIp(
            _settings->device_config.wifi_server_ip,
            _settings->device_config.wifi_ap_gateway,
            _settings->device_config.wifi_ap_subnet,
            _settings->device_config.wifi_ap_primary_dns,
            _settings->device_config.wifi_ap_secondary_dns);
    }

    if (_settings->device_config.is_developer_mode.developerMode)
    {
        Serial.println("Connecting to Wifi as developer mode...");

        localIp = _wifiController->connect(_settings->device_config.wifi_dev_ssid, _settings->device_config.wifi_dev_pass);
    }
    else
    {
        Serial.println("Connecting to Wifi as production mode...");

        localIp = _wifiController->connect(_settings->device_config.wifi_prod_ssid, _settings->device_config.wifi_prod_pass);
    }

    if (_settingsController->settings.is_wifiserver_enabled == true)
    {
        _wifiController->enableServer(80);
    }

    startOTA();
}

void apiInit()
{
    Serial.println("Setting up Api...");

    // Add new routes to settings be request to a desired Backend service
    _settings->device_config.routes.push_back({"status", "/status", "GET"});
    _settings->device_config.routes.push_back({"get-node", "/node", "GET"});
    _settings->device_config.routes.push_back({"get-sensors-by-nodeid", "/sensor", "GET"});
    _settings->device_config.routes.push_back({"post-insight", "/insight", "POST"});

    if (_settings->device_config.is_developer_mode.developerMode)
    {
        // Setup development origins
        _api = new Api(_settings->device_config.api_dev_origin, _settings->device_config.routes);
    }
    else
    {
        // Setup production origins
        _api = new Api(_settings->device_config.api_prod_origin, _settings->device_config.routes);
    }
}

void setupStage(bool developerMode)
{
    Serial.println("Setting up stage...");
    Serial.println("Developer mode: " + developerMode ? "Yes" : "No");
    _settings->device_config.is_developer_mode.developerMode = developerMode;
}
