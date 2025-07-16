#include "DigitalPin.hpp"
#include <Arduino.h>

DigitalPin::DigitalPin(int number, int mode, bool value) : Pin<bool>(number, mode, value)
{
}

DigitalPin::~DigitalPin()
{
}

bool DigitalPin::read() const
{
    return digitalRead(number);
}

void DigitalPin::write(bool value)
{
    this->digitalWrite(value);
}

void DigitalPin::digitalWrite(bool state)
{
    if (this->mode == OUTPUT)
    {
        ::digitalWrite(number, state ? HIGH : LOW);
        this->value = state;
    }
}
