#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

#include "Pin.hpp"

#ifdef ESP_PLATFORM
#include "esp_adc/adc_oneshot.h"
#include "driver/dac.h"
#endif

class AnalogPin : public Pin<int>
{
    public:
    explicit AnalogPin(int number, PinMode mode, int value = 0);
    ~AnalogPin() override;

    void init() override;

    int read() const override;
    void write(int value) override;

    private:
#ifdef ESP_PLATFORM
    adc_oneshot_unit_handle_t adc_handle{};
#endif
};

#endif // ANALOG_PIN_HPP
