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
    currentMilliseconds = millis();
}

/*
 * Validate if device cycle is sync with current time to run the next tasks.
 * It provides multiple "virtual threads" inside main thread
 *
 * @return {bool} return if time is inside device cycle
 */
bool isInThreadCycle(int threadCycle)
{
    if (currentMilliseconds - previousDeviceCycleMilliseconds < threadCycle)
    {
        return false
    }

    previousDeviceCycleMilliseconds = currentMilliseconds;

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

    if (!isInThreadCycle(_settingsController->settings.main_thread_cycle))
    {
        return;
    }

    if (_wifiController->isConnected() == false)
    {
        return;
    }
}

void threads()
{
    if (isInThreadCycle(_templateThread->getCycle()))
    {
        _templateThread->run();
    }

    // TODO: Add all your threads
}

void reset()
{
    ESP.restart();
}

void setup()
{
    Serial.begin(9600);

    _setupController->deviceInit();
}

void loop()
{
    captureTimestamp();

    _setupController->handleOta();
    mainThread();
    threads();

    delay(1);
}
