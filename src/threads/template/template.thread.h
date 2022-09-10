/*
 * template.thread.h
 *
 * Author: <YOUR_NAME>
 * Company: <YOUR_COMPANY>
 * License: GNU General Public License v3.0
 * Created on: Sep 10, 2022
 * Updated on: Sep 10, 2022
 */

#pragma once

#ifndef TEMPLATE_THREAD_H
#define TEMPLATE_THREAD_H

#include "Arduino.h"

namespace Thread
{
    class Template
    {
    public:
        Template(int threadCycle, String threadName);
        void run();

    private:
        String _threadName = "template";
        int _threadCycle = 10000;
    };
} // namespace Thread

#endif
