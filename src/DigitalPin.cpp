#include "DigitalPin.hpp"
#ifdef ESP_PLATFORM
#include "driver/gpio.h"
#endif

DigitalPin::DigitalPin(int pinNumber, PinMode mode, bool value) : Pin<bool>(pinNumber, mode, value)
{
}

DigitalPin::~DigitalPin() = default;

void DigitalPin::init()
{
#ifdef ESP_PLATFORM
    gpio_reset_pin(static_cast<gpio_num_t>(pinNumber));
    gpio_set_direction(static_cast<gpio_num_t>(pinNumber),
                       mode == PinMode::Output ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT);
#endif
}

bool DigitalPin::read() const
{
#ifdef ESP_PLATFORM
    return gpio_get_level(static_cast<gpio_num_t>(pinNumber));
#else
    return this->value;
#endif
}

void DigitalPin::write(bool value)
{
    if (this->mode == PinMode::Output)
    {
#ifdef ESP_PLATFORM
        gpio_set_level(static_cast<gpio_num_t>(pinNumber), value ? 1 : 0);
#endif
        this->value = value;
    }
}
