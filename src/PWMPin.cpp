#include "PWMPin.hpp"
#ifdef ESP_PLATFORM
#include "driver/ledc.h"
#endif

PWMPin::PWMPin(int number, PinMode mode, int value) : Pin<int>(number, mode, value)
{
#ifdef ESP_PLATFORM
    channel = LEDC_CHANNEL_0;
#endif
}

PWMPin::~PWMPin() = default;

void PWMPin::init()
{
#ifdef ESP_PLATFORM
    ledc_timer_config_t timer_conf{};
    timer_conf.speed_mode = LEDC_LOW_SPEED_MODE;
    timer_conf.timer_num = LEDC_TIMER_0;
    timer_conf.duty_resolution = LEDC_TIMER_8_BIT;
    timer_conf.freq_hz = 5000;
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t ch_conf{};
    ch_conf.gpio_num = number;
    ch_conf.speed_mode = LEDC_LOW_SPEED_MODE;
    ch_conf.channel = static_cast<ledc_channel_t>(channel);
    ch_conf.timer_sel = LEDC_TIMER_0;
    ch_conf.duty = value;
    ledc_channel_config(&ch_conf);
#endif
}

int PWMPin::read() const
{
#ifdef ESP_PLATFORM
    return ledc_get_duty(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(channel));
#else
    return this->value;
#endif
}

void PWMPin::write(int value)
{
    if (mode == PinMode::Output)
    {
#ifdef ESP_PLATFORM
        ledc_set_duty(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(channel), value);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, static_cast<ledc_channel_t>(channel));
#endif
        this->value = value;
    }
}
