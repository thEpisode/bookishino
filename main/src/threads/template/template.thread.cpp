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

Thread::Template::Template(int threadCycle, String threadName)
{
    _threadCycle = threadCycle;
    _threadName = threadName;
}

void Thread::Template::run()
{
    Serial.println("Running thread...");

    /* _ds18b20Controller = new Ds18b20(2, "sns-1234-2");

    Serial.println("Reading sen0193...");
    String requestRoute = "";
    String requestMethod = "";
    String requestOrigin = "";

    requestOrigin = _backendController->getOrigin();
    requestRoute = _backendController->getRoute("post-insight");
    requestMethod = _backendController->getMethod("post-insight");
    String payloadSen0193 = _sen0193Controller->response();
    _wifiController->sendMessage(requestOrigin, requestRoute, payloadSen0193, requestMethod);
    delay(1000); */
}

int Thread::Template::getCycle()
{
    return _threadCycle;
}