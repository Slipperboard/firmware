#include <cstdio>
#include "ArduinoCompat.hpp"

extern "C" void app_main(void)
{
#ifdef ESP_PLATFORM
    initArduino();
#endif
    while (true)
    {
        printf("Hello, Flipper Zero compatible ESP32!\n");
        delay(1000);
    }
}
