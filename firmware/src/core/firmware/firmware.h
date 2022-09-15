/*
 * firmware.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Sep 15, 2022
 * Updated on: Sep 15, 2022
 */

#include "../connectivity/backend/backend.h"
#include "../connectivity/ble/ble.h"
#include "../connectivity/ota/ota.h"
#include "../connectivity/wifi/wifi.h"
#include "../device/localstorage/localstorage.h"
#include "../device/operations/operations.h"
#include "../device/settings/settings.h"
#include "../device/setup/setup.h"

namespace Core
{
    class Firmware
    {
    public:
        /* Static access method. */
        static Firmware *getInstance();
        /* Backend */
        Core::Backend backend();
        void setBackend(String origin, std::vector<Core::route> routes);

        /* BLE */
        Core::Ble ble();
        void setBle(std::string deviceName, std::string serviceUuid, std::string characteristicUuid, std::string defaultvalue);

        /* OTA */
        Core::Ota ota();
        void setOta();

        /* WiFi */
        Core::Wifi wifi();
        void setWifi();

        /* Local Storage */
        Core::LocalStorage localStorage();
        void setLocalStorage();

        /* Operations */
        Core::Operations operations();
        void setOperations();

        /* Settings */
        Core::Settings settings();
        void setSettings();

        /* Setup */
        Core::Setup setup();
        void setSetup();

        /* data */
        unsigned long currentMilliseconds = 0; // stores the value of millis() in each iteration of loop()
        unsigned long previousDeviceCycleMilliseconds = 0;

    private:
        /* Here will be the instance stored. */
        static Firmware *instance;

        /* Connectivity */
        Core::Backend *_backend;
        Core::Ble *_ble;
        Core::Ota *_ota;
        Core::Wifi *_wifi;

        /* Device */
        Core::LocalStorage *_localStorage;
        Core::Operations *_operations;
        Core::Settings *_settings;
        Core::Setup *_setup;

        /* Private constructor to prevent instancing. */
        Firmware();
    };
} // namespace Core
