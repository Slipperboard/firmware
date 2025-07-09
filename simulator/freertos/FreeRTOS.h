#ifndef FREERTOS_STUB_H
#define FREERTOS_STUB_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void vTaskDelay(uint32_t ms);

#ifdef __cplusplus
}
#endif

#define pdMS_TO_TICKS(ms) (ms)

#endif // FREERTOS_STUB_H
