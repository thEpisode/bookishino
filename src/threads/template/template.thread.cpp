/*
 * template.thread.cpp
 *
 * Author: <YOUR_NAME>
 * Company: <YOUR_COMPANY>
 * License: GNU General Public License v3.0
 * Created on: Sep 10, 2022
 * Updated on: Sep 10, 2022
 */

#include "Arduino.h"

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
}
