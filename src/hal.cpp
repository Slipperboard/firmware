#include "hal/hal.hpp"
#include <vector>

namespace hal {

static std::vector<Device*> devices;

esp_err_t register_device(Device* dev)
{
    if (devices.size() >= MAX_DEVICES) {
        return ESP_ERR_NO_MEM;
    }
    devices.push_back(dev);
    return ESP_OK;
}

esp_err_t init()
{
    for (auto* dev : devices) {
        if (dev) {
            dev->init();
        }
    }
    return ESP_OK;
}

esp_err_t deinit()
{
    for (auto* dev : devices) {
        if (dev) {
            dev->deinit();
        }
    }
    return ESP_OK;
}

void reset()
{
    devices.clear();
}

} // namespace hal
