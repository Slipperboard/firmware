#include "AnalogPin.hpp"
#ifdef ESP_PLATFORM
#include <driver/dac_oneshot.h>
#include <esp_adc/adc_oneshot.h>
#endif

AnalogPin::AnalogPin(int number, PinMode mode, int value) : Pin<int>(number, mode, value)
{
}

AnalogPin::~AnalogPin()
{
#ifdef ESP_PLATFORM
    if (mode == PinMode::Input && adc_handle != nullptr) {
        adc_oneshot_del_unit(adc_handle);
    }
    if (mode == PinMode::Output && dac_handle != nullptr) {
        dac_oneshot_del_channel(dac_handle);
    }
#endif
}

void AnalogPin::init()
{
#ifdef ESP_PLATFORM
    if (mode == PinMode::Input) {
        adc_oneshot_unit_init_cfg_t unit_cfg{};
        unit_cfg.unit_id = ADC_UNIT_1;
        adc_oneshot_new_unit(&unit_cfg, &adc_handle);

        adc_oneshot_chan_cfg_t chan_cfg{};
        chan_cfg.atten = ADC_ATTEN_DB_12;
        chan_cfg.bitwidth = ADC_BITWIDTH_12;
        adc_oneshot_config_channel(adc_handle, static_cast<adc_channel_t>(number), &chan_cfg);
        return;
    }

    dac_oneshot_config_t dac_cfg{};
    if (number == 25) {
        dac_cfg.chan_id = DAC_CHAN_0;
    } else if (number == 26) {
        dac_cfg.chan_id = DAC_CHAN_1;
    } else {
        return;
    }
    dac_oneshot_new_channel(&dac_cfg, &dac_handle);
#endif
}

int AnalogPin::read() const
{
#ifdef ESP_PLATFORM
    if (mode == PinMode::Input) {
        int result = 0;
        adc_oneshot_read(adc_handle, static_cast<adc_channel_t>(number), &result);
        return result;
    }
#endif
    return this->value;
}

void AnalogPin::write(int value)
{
    if (this->mode != PinMode::Output) {
        return;
    }
#ifdef ESP_PLATFORM
    if (number == 25 || number == 26) {
        dac_oneshot_output_voltage(dac_handle, static_cast<uint8_t>(value));
    }
#endif
    this->value = value;
}
