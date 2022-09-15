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

Core::Setup::Setup(firmware_dependencies &dependencies)
{
    _dependencies = dependencies;
    _settings = _dependencies.settings;
    _backend = _dependencies.backend;
    _ble = _dependencies.ble;
    _wifi = _dependencies.wifi;
}

/*
 * Initialize configurations and start all services.
 *
 * @return {void}
 */
void Core::Setup::setupDevice()
{
    setupStage();
    setupCommunications();
}

void Core::Setup::setupStage(bool developerMode)
{
    Serial.println("Setting up stage...");
    Serial.println("Developer mode: " + developerMode ? "Yes" : "No");
    _settings->device_config.is_developer_mode.developerMode = developerMode;
}

void Core::Setup::setupCommunications()
{
    Serial.println("Setting up communications...");

    if (_settings->device_config.is_backend_enabled)
    {
        backendInit();
    }

    if (true == _settings->device_config.is_ble_enabled)
    {
        bleInit();
    }

    if (true == _settings->device_config.is_wifi_enabled)
    {
        wifiInit();
    }
}

void Core::Setup::backendInit()
{
    Serial.println("Setting up Backend...");

    // Add new routes to settings be request to a desired Backend service
    _settings->device_config.backend_routes.push_back({"status", "/status", "GET"});
    _settings->device_config.backend_routes.push_back({"get-node", "/node", "GET"});
    _settings->device_config.backend_routes.push_back({"get-sensors-by-nodeid", "/sensor", "GET"});
    _settings->device_config.backend_routes.push_back({"post-insight", "/insight", "POST"});

    if (_settings->device_config.is_developer_mode.developerMode)
    {
        // Setup development origins
        _backend = new Backend(_settings->device_config.api_dev_origin, _settings->device_config.routes);
    }
    else
    {
        // Setup production origins
        _backend = new Backend(_settings->device_config.api_prod_origin, _settings->device_config.routes);
    }
}

void Core::Setup::bleInit()
{
    Serial.println("Setting up BLE...");

    _ble = new Ble(_settings->device_config.device_name);
    _ble->startService();
}

void Core::Setup::wifiInit()
{
    Serial.println("Setting up Wifi...");

    _wifi = new Wifi(_dependencies);

    enableAccessPoint();
    enableStaticIP();
    stablishNetworkConnection();
    enableServer();
}

void Core::Setup::enableAccessPoint()
{
    if (_settings->device_config.is_wifiap_enabled == true)
    {
        // Enable Access Point
        _wifi->enableAccessPoint(
            _settings->device_config.ap_ssid,
            _settings->device_config.ap_pass,
            _settings->device_config.wifi_server_ip,
            _settings->device_config.wifi_ap_gateway,
            _settings->device_config.wifi_ap_subnet);
    }
}

void Core::Setup::enableStaticIP()
{
    if (_settings->device_config.is_wifi_static_ip_enabled == true)
    {
        // Enable static IP
        _wifi->setStaticIp(
            _settings->device_config.wifi_server_ip,
            _settings->device_config.wifi_ap_gateway,
            _settings->device_config.wifi_ap_subnet,
            _settings->device_config.wifi_ap_primary_dns,
            _settings->device_config.wifi_ap_secondary_dns);
    }
}

void Core::Setup::stablishNetworkConnection()
{
    String localIp = "";

    if (_settings->device_config.is_developer_mode.developerMode)
    {
        Serial.println("Connecting to Wifi as developer mode...");

        localIp = _wifi->connect(_settings->device_config.wifi_dev_ssid, _settings->device_config.wifi_dev_pass);
    }
    else
    {
        Serial.println("Connecting to Wifi as production mode...");

        localIp = _wifi->connect(_settings->device_config.wifi_prod_ssid, _settings->device_config.wifi_prod_pass);
    }
}

void Core::Setup::enableServer()
{
    if (_settingsController->settings.is_server_enabled == true)
    {
        _wifi->enableServer(_settingsController->settings.server_port);
    }
}