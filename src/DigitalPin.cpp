#include "DigitalPin.hpp"

#ifdef ESP_PLATFORM
#include "driver/gpio.h"
#endif

DigitalPin::DigitalPin(int number, PinMode mode, bool value) : Pin<bool>(number, mode, value)
{
}

DigitalPin::~DigitalPin() = default;

void DigitalPin::init()
{
#ifdef ESP_PLATFORM
    gpio_config_t io_conf{};
    io_conf.pin_bit_mask = 1ULL << number;
    io_conf.mode = mode == PinMode::Output ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);
#endif
}

bool DigitalPin::read() const
{
#ifdef ESP_PLATFORM
    this->value = gpio_get_level(static_cast<gpio_num_t>(number));
#endif
    return this->value;
}

void DigitalPin::write(bool value) const
{
    if (this->mode == PinMode::Output)
    {
#ifdef ESP_PLATFORM
        gpio_set_level(static_cast<gpio_num_t>(number), value ? 1 : 0);
#endif
        this->value = value;
    }
}
