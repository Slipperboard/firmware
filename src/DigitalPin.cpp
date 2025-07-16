#include "DigitalPin.hpp"
#include <Arduino.h>

DigitalPin::DigitalPin(int number, PinMode mode, bool value) : Pin<bool>(number, mode, value)
{
    pinMode(number, mode == PinMode::Output ? OUTPUT : INPUT);
}

DigitalPin::~DigitalPin() = default;

bool DigitalPin::read() const
{
    return digitalRead(number);
}

void DigitalPin::write(bool value)
{
    if (this->mode == PinMode::Output)
    {
        digitalWrite(number, value ? HIGH : LOW);
        this->value = value;
    }
}
