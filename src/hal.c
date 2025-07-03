#include "hal/hal.h"

static hal_device_t *device_list[HAL_MAX_DEVICES];
static size_t device_count = 0;

esp_err_t hal_register_device(hal_device_t *dev)
{
    if (device_count >= HAL_MAX_DEVICES) {
        return ESP_ERR_NO_MEM;
    }
    device_list[device_count++] = dev;
    return ESP_OK;
}

esp_err_t hal_init(void)
{
    for (size_t i = 0; i < device_count; ++i) {
        hal_device_t *dev = device_list[i];
        if (dev->ops && dev->ops->init) {
            dev->ops->init(dev);
        }
    }
    return ESP_OK;
}

esp_err_t hal_deinit(void)
{
    for (size_t i = 0; i < device_count; ++i) {
        hal_device_t *dev = device_list[i];
        if (dev->ops && dev->ops->deinit) {
            dev->ops->deinit(dev);
        }
    }
    return ESP_OK;
}
