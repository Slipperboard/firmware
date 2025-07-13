#include "AnalogPin.hpp"

#ifdef ESP_PLATFORM
#include "driver/adc.h"
#include "driver/dac.h"
#include "driver/gpio.h"
#endif

AnalogPin::AnalogPin(int number, PinMode mode, int value) : Pin<int>(number, mode, value)
{
}

AnalogPin::~AnalogPin() = default;

void AnalogPin::init()
{
#ifdef ESP_PLATFORM
    gpio_set_direction(static_cast<gpio_num_t>(number), mode == PinMode::Output ? GPIO_MODE_OUTPUT : GPIO_MODE_INPUT);
    if (mode == PinMode::Output)
    {
        if (number == 25)
        {
            dac_output_enable(DAC_CHANNEL_1);
        } else if (number == 26)
        {
            dac_output_enable(DAC_CHANNEL_2);
        }
    }
#endif
}

int AnalogPin::read() const
{
#ifdef ESP_PLATFORM
    if (mode == PinMode::Input)
    {
        return adc1_get_raw(static_cast<adc1_channel_t>(number));
    }
#endif
    return this->value;
}

void AnalogPin::write(int value) const
{
    if (this->mode == PinMode::Output)
    {
#ifdef ESP_PLATFORM
        if (number == 25)
        {
            dac_output_voltage(DAC_CHANNEL_1, value);
        } else if (number == 26)
        {
            dac_output_voltage(DAC_CHANNEL_2, value);
        }
#endif
        this->value = value;
    }
}
