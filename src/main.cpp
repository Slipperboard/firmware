#include <cstdio>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

extern "C" void app_main()
{
    while (true) {
        printf("Hello, Flipper Zero compatible ESP32!\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
