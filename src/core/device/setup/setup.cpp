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

Core::Setup::Setup()
{
    // Initialize firmware instance
    firmware = firmware->getInstance();
}

/*
 * Initialize configurations and start all services.
 *
 * @return {void}
 */
void Core::Setup::setupDevice()
{
    setupStage(firmware->settings()->device.is_developer_mode);
    setupCommunications();
}

void Core::Setup::setupStage(bool developerMode)
{
    Serial.println("Setting up stage...");
    Serial.println("Developer mode: " + developerMode ? "Yes" : "No");
    firmware->settings()->setIsDeveloperMode(developerMode);
}

void Core::Setup::setupCommunications()
{
    Serial.println("Setting up communications...");

    if (firmware->settings()->device.is_backend_enabled)
    {
        backendInit();
    }

    if (true == firmware->settings()->device.is_ble_enabled)
    {
        bleInit();
    }

    if (true == firmware->settings()->device.is_wifi_enabled)
    {
        wifiInit();
    }
}

void Core::Setup::backendInit()
{
    Serial.println("Setting up Backend...");

    // Add new routes to settings be request to a desired Backend service
    firmware->settings()->device.backend_routes.push_back({"status", "/status", "GET"});
    firmware->settings()->device.backend_routes.push_back({"get-node", "/node", "GET"});
    firmware->settings()->device.backend_routes.push_back({"get-sensors-by-nodeid", "/sensor", "GET"});
    firmware->settings()->device.backend_routes.push_back({"post-insight", "/insight", "POST"});

    if (firmware->settings()->device.is_developer_mode)
    {
        // Setup development origins
        firmware->setBackend(firmware->settings()->device.api_dev_origin, firmware->settings()->device.backend_routes);
    }
    else
    {
        // Setup production origins
        firmware->setBackend(firmware->settings()->device.api_prod_origin, firmware->settings()->device.backend_routes);
    }
}

void Core::Setup::bleInit()
{
    Serial.println("Setting up BLE...");

    firmware->setBle(
        firmware->settings()->device.device_name,
        firmware->settings()->device.service_uuid,
        firmware->settings()->device.characteristic_uuid,
        firmware->settings()->device.default_value);
    firmware->ble()->startService();
}

void Core::Setup::wifiInit()
{
    Serial.println("Setting up Wifi...");

    firmware->setWifi();

    enableAccessPoint();
    enableStaticIP();
    stablishNetworkConnection();
    enableServer();
}

void Core::Setup::enableAccessPoint()
{
    if (firmware->settings()->device.is_wifiap_enabled == true)
    {
        // Enable Access Point
        firmware->wifi()->enableAccessPoint(
            firmware->settings()->device.ap_ssid,
            firmware->settings()->device.ap_pass,
            firmware->settings()->device.wifi_server_ip,
            firmware->settings()->device.wifi_ap_gateway,
            firmware->settings()->device.wifi_ap_subnet);
    }
}

void Core::Setup::enableStaticIP()
{
    if (firmware->settings()->device.is_wifi_static_ip_enabled == true)
    {
        // Enable static IP
        firmware->wifi()->setStaticIp(
            firmware->settings()->device.wifi_server_ip,
            firmware->settings()->device.wifi_ap_gateway,
            firmware->settings()->device.wifi_ap_subnet,
            firmware->settings()->device.wifi_ap_primary_dns,
            firmware->settings()->device.wifi_ap_secondary_dns);
    }
}

void Core::Setup::stablishNetworkConnection()
{
    String localIp = "";

    if (firmware->settings()->device.is_developer_mode)
    {
        Serial.println("Connecting to Wifi as developer mode...");

        localIp = firmware->wifi()->connect(firmware->settings()->device.wifi_dev_ssid, firmware->settings()->device.wifi_dev_pass);
    }
    else
    {
        Serial.println("Connecting to Wifi as production mode...");

        localIp = firmware->wifi()->connect(firmware->settings()->device.wifi_prod_ssid, firmware->settings()->device.wifi_prod_pass);
    }
}

void Core::Setup::enableServer()
{
    if (firmware->settings()->device.is_server_enabled == true)
    {
        firmware->wifi()->enableServer(firmware->settings()->device.server_port);
    }
}