#include "AnalogPin.hpp"
#ifdef ESP_PLATFORM
#include "driver/adc.h"
#include "driver/dac.h"
#endif

AnalogPin::AnalogPin(int pinNumber, PinMode mode, int value) : Pin<int>(pinNumber, mode, value)
{
}

AnalogPin::~AnalogPin() = default;

void AnalogPin::init()
{
#ifdef ESP_PLATFORM
    if (mode == PinMode::Input)
    {
        adc1_config_width(ADC_WIDTH_BIT_12);
        adc1_config_channel_atten(static_cast<adc1_channel_t>(pinNumber), ADC_ATTEN_DB_11);
    } else // NOLINT(readability/braces)
    {
        if (pinNumber == 25)
        {
            dac_output_enable(DAC_CHANNEL_1);
        } else if (pinNumber == 26) // NOLINT(readability/braces)
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
        return adc1_get_raw(static_cast<adc1_channel_t>(pinNumber));
    }
#endif
    return this->value;
}

void AnalogPin::write(int value)
{
    if (this->mode == PinMode::Output)
    {
#ifdef ESP_PLATFORM
        if (pinNumber == 25)
        {
            dac_output_voltage(DAC_CHANNEL_1, static_cast<uint8_t>(value));
        } else if (pinNumber == 26) // NOLINT(readability/braces)
        {
            dac_output_voltage(DAC_CHANNEL_2, static_cast<uint8_t>(value));
        }
#endif
        this->value = value;
    }
}
