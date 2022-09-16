/*
 * operations.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Sep 13, 2022
 * Updated on: Sep 13, 2022
 */

#pragma once

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <Arduino.h>

namespace Core
{
    class Operations
    {
    public:
        Operations();
        void reset();
        void enableAPServer();

    private:
        String _filename;
        String _settingsJson;
    };
} // namespace Core

#endif
