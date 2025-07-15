#include "PWMPin.hpp"
#include "ArduinoCompat.hpp"

PWMPin::PWMPin(int number, PinMode mode, int value)
    : Pin<int>(number, mode, value), channel(0)
{
}

PWMPin::~PWMPin() = default;

void PWMPin::init()
{
    ledcSetup(channel, 5000, 8);
    ledcAttachPin(number, channel);
    ledcWrite(channel, value);
}

int PWMPin::read() const
{
    return ledcRead(channel);
}

void PWMPin::write(int value)
{
    if (mode == PinMode::Output)
    {
        ledcWrite(channel, value);
        this->value = value;
    }
}
