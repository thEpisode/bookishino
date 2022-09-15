/*
 * bookish.ino - Sketch for flashing ESP32 micro-node.
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 15, 2022
 */

#include <Arduino.h>
#include <ArduinoJson.h>

#include "bookish.h"

/*
 * Capture the latest value of millis()
 * this is equivalent to noting the time from a clock
 * use the same time for all LED flashes to keep them synchronized
 */
void captureTimestamp()
{
    firmware->currentMilliseconds = millis();
}

/*
 * Validate if device cycle is sync with current time to run the next tasks.
 * It provides multiple "virtual threads" inside main thread
 *
 * @return {bool} return if time is inside device cycle
 */
bool isInThreadCycle(int threadCycle)
{
    if (firmware->currentMilliseconds - firmware->previousDeviceCycleMilliseconds < threadCycle)
    {
        return false;
    }

    firmware->previousDeviceCycleMilliseconds = firmware->currentMilliseconds;

    return true;
}

void mainThread()
{
    captureTimestamp();

    if (!isInThreadCycle(firmware->settings()->device.main_thread_cycle))
    {
        return;
    }

    if (firmware->wifi()->isConnected() == false)
    {
        return;
    }

    firmware->ota()->handle();
}

void threadHandling()
{
    if (isInThreadCycle(threads._templateThread->getCycle()))
    {
        threads._templateThread->run();
    }

    // TODO: Add all your threads
}

void setupSensors()
{
    sensors._virtual32Controller = new Sensor::Virtual32();
    sensors._virtual8266Controller = new Sensor::Virtual8266();

    // TODO: Add all your sensors
}

void setupThreads()
{
    threads._templateThread = new Thread::Template();

    // TODO: Add all your threads
}

void setup()
{
    Serial.begin(9600);

    // Initialize firmware instance
    firmware = firmware->getInstance();

    // Setting up setings and setup controllers
    firmware->setSettings();
    firmware->setSetup();

    // Start setup of device
    firmware->setup()->setupDevice();

    // Setting up your sensors and threads
    setupSensors();
    setupThreads();
}

void loop()
{
    mainThread();
    threadHandling();

    delay(1);
}
