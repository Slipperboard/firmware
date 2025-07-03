#ifndef HAL_HAL_HPP
#define HAL_HAL_HPP

#include <esp_err.h>
#include <array>
#include <cstddef>

namespace hal {

constexpr std::size_t MAX_DEVICES = 8;

class Device {
public:
    virtual ~Device() = default;
    virtual esp_err_t init() { return ESP_OK; }
    virtual esp_err_t deinit() { return ESP_OK; }
};

esp_err_t register_device(Device* dev);
esp_err_t init();
esp_err_t deinit();
void reset();

} // namespace hal

#endif // HAL_HAL_HPP
