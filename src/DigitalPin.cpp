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
    if (mode == INPUT)
    {
        return digitalRead(number);
    }
    return this->value;
}

void DigitalPin::write(bool value)
{
    if (this->mode == OUTPUT)
    {
        ::digitalWrite(number, value ? HIGH : LOW);
        this->value = value;
    }
}
