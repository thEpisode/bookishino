
// Sensors
#include "src/sensors/sensor/sensor.h"
#include "src/sensors/virtual32/virtual32.h"
#include "src/sensors/virtual8266/virtual8266.h"

// Threads
#include "src/threads/template/template.thread.h"

namespace Core
{
    // Memory-layout declarations
    class Backend;
    class Ble;
    class Ota;
    class Wifi;
    class LocalStorage;
    class Operations;
    class Settings;
    class Setup;
    class Firmware;
}

typedef struct sensors_typo
{
    /* My Sensors */
    Sensor::Virtual32 *_virtual32Controller;
    Sensor::Virtual8266 *_virtual8266Controller;
};

typedef struct threads_typo
{
    /* My Threads */
    Thread::Template *_templateThread;
};