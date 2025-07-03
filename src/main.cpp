#include <cstdio>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/hal.hpp"
#include "dummy_device.hpp"

extern "C" void app_main(void)
{
    hal::register_device(&dummy_device);
    hal::init();

    while (true) {
        printf("Hello, Flipper Zero compatible ESP32!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
