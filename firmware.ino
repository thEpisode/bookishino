/*
 * firmware.ino - Sketch for flashing ESP32 micro-node.
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#include "Arduino.h"
#include <ArduinoJson.h>

#include "firmware.h"

/*
 * Capture the latest value of millis()
 * this is equivalent to noting the time from a clock
 * use the same time for all LED flashes to keep them synchronized
 */
void captureTimestamp()
{
    firmware.currentMilliseconds = millis();
}

/*
 * Validate if device cycle is sync with current time to run the next tasks.
 * It provides multiple "virtual threads" inside main thread
 *
 * @return {bool} return if time is inside device cycle
 */
bool isInThreadCycle(int threadCycle)
{
    if (firmware.currentMilliseconds - firmware.previousDeviceCycleMilliseconds < threadCycle)
    {
        return false
    }

    firmware.previousDeviceCycleMilliseconds = firmware.currentMilliseconds;

    return true
}

void mainThread()
{
    String requestRoute = "";
    String requestMethod = "";
    String requestOrigin = "";

    requestOrigin = _apiController->getOrigin();
    requestRoute = _apiController->getRoute("post-insight");
    requestMethod = _apiController->getMethod("post-insight");

    captureTimestamp();

    if (!isInThreadCycle(firmware._settingsController->settings.main_thread_cycle))
    {
        return;
    }

    if (firmware._wifiController->isConnected() == false)
    {
        return;
    }

    firmware._setupController->handleOta();
}

void threads()
{
    if (isInThreadCycle(firmware._templateThread->getCycle()))
    {
        firmware._templateThread->run();
    }

    // TODO: Add all your threads
}

void setup()
{
    Serial.begin(9600);

    firmware._settingsController = new Settings("settings.json");
    firmware._setupController = new Setup();
    firmware._setupController->setupDevice(firmware._settingsController);
}

void loop()
{
    mainThread();
    threads();

    delay(1);
}
