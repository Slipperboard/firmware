#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal/hal.h"
#include "dummy_device.h"

void app_main(void)
{
    hal_register_device(&dummy_device);
    hal_init();

    while (true) {
        printf("Hello, Flipper Zero compatible ESP32!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
