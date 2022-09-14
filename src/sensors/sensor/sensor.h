/*
 * sensor.h
 *
 * Author: Camilo Rodriguez Cuaran
 * Company: Virtual capital of America
 * License: GNU General Public License v3.0
 * Created on: Jan 15, 2020
 * Updated on: Sep 09, 2022
 */

#pragma once

#ifndef SENSOR_H
#define SENSOR_H

#include "Arduino.h"

typedef struct Sensor
{
    String name;
    String node_id;
    String technical_name;
    String title;
    String description;
    int interval;
    int analog_0;
    int analog_1;
    int analog_2;
    int analog_3;
    int analog_4;
    int analog_5;
    int digital_0;
    int digital_1;
    int digital_2;
    int digital_3;
    int digital_4;
    int digital_5;
    int tx_0;
    int rx_0;
    int dio_0;
    int dio_1;
    int dio_2;
    int dio_3;
    int dio_4;
    int dio_5;
    int nss_0;
    int sck_0;
    int mosi_0;
    int miso_0;
};

#endif