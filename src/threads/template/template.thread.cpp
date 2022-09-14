/*
 * template.thread.cpp
 *
 * Author: <YOUR_NAME>
 * Company: <YOUR_COMPANY>
 * License: GNU General Public License v3.0
 * Created on: Sep 10, 2022
 * Updated on: Sep 10, 2022
 */

#include <Arduino.h>

#include "template.thread.h"

using namespace Thread;

Template::Template(int threadCycle, String threadName)
{
    _threadCycle = threadCycle;
    _threadName = threadName;
}

void Template::run()
{
    Serial.println("Running thread...");

    /* _ds18b20Controller = new Ds18b20(2, "sns-1234-2");

    Serial.println("Reading sen0193...");
    String payloadSen0193 = _sen0193Controller->response();
    _wifiController->sendMessage(requestOrigin, requestRoute, payloadSen0193, requestMethod);
    delay(1000); */
}

int Template::getCycle()
{
    return _threadCycle;
}