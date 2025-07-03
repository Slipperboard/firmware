#ifndef DUMMY_DEVICE_HPP
#define DUMMY_DEVICE_HPP

#include "hal/hal.hpp"

class DummyDevice : public hal::Device {
public:
    esp_err_t init() override;
    esp_err_t deinit() override;
};

#endif // DUMMY_DEVICE_HPP
