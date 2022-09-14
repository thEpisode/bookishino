/*
 * firmware.ino - Sketch for flashing ESP32 micro-node.
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include <Arduino.h>
#include <ArduinoJson.h>

#include "firmware.h"

/*
 * Capture the latest value of millis()
 * this is equivalent to noting the time from a clock
 * use the same time for all LED flashes to keep them synchronized
 */
void captureTimestamp()
{
    firmware_dependencies.currentMilliseconds = millis();
}

/*
 * Validate if device cycle is sync with current time to run the next tasks.
 * It provides multiple "virtual threads" inside main thread
 *
 * @return {bool} return if time is inside device cycle
 */
bool isInThreadCycle(int threadCycle)
{
    if (firmware_dependencies.currentMilliseconds - firmware_dependencies.previousDeviceCycleMilliseconds < threadCycle)
    {
        return false
    }

    firmware_dependencies.previousDeviceCycleMilliseconds = firmware_dependencies.currentMilliseconds;

    return true
}

void mainThread()
{
    captureTimestamp();

    if (!isInThreadCycle(firmware_dependencies._settingsController->settings.main_thread_cycle))
    {
        return;
    }

    if (firmware_dependencies._wifiController->isConnected() == false)
    {
        return;
    }

    firmware_dependencies._setupController->handleOta();
}

void threads()
{
    if (isInThreadCycle(firmware_dependencies._templateThread->getCycle()))
    {
        firmware_dependencies._templateThread->run();
    }

    // TODO: Add all your threads
}

void setup()
{
    Serial.begin(9600);

    firmware_dependencies._settingsController = new Settings("settings.json");

    firmware_dependencies._setupController = new Setup(firmware_dependencies);
    firmware_dependencies._setupController->setupDevice();
}

void loop()
{
    mainThread();
    threads();

    delay(1);
}
