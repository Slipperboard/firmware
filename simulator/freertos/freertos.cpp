#include "FreeRTOS.h"
#include <chrono>
#include <thread>

extern "C" void vTaskDelay(uint32_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
