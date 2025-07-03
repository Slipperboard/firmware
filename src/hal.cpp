#include "hal/hal.hpp"
#include <array>

namespace hal {

static std::array<Device*, MAX_DEVICES> devices{};
static std::size_t device_count = 0;

esp_err_t register_device(Device* dev)
{
    if (device_count >= MAX_DEVICES) {
        return ESP_ERR_NO_MEM;
    }
    devices[device_count++] = dev;
    return ESP_OK;
}

esp_err_t init()
{
    for (std::size_t i = 0; i < device_count; ++i) {
        if (devices[i]) {
            devices[i]->init();
        }
    }
    return ESP_OK;
}

esp_err_t deinit()
{
    for (std::size_t i = 0; i < device_count; ++i) {
        if (devices[i]) {
            devices[i]->deinit();
        }
    }
    return ESP_OK;
}

void reset()
{
    for (std::size_t i = 0; i < device_count; ++i) {
        devices[i] = nullptr;
    }
    device_count = 0;
}

} // namespace hal
