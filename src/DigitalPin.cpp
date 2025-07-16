#include "DigitalPin.hpp"
#ifdef ARDUINO
#include <Arduino.h>
#endif

DigitalPin::DigitalPin(int number, PinMode mode, bool value) : Pin<bool>(number, mode, value)
{
}

DigitalPin::~DigitalPin() = default;

void DigitalPin::init()
{
#ifdef ARDUINO
    pinMode(number, mode == PinMode::Output ? OUTPUT : INPUT);
#endif
}

bool DigitalPin::read() const
{
#ifdef ARDUINO
    return digitalRead(number);
#else
    return this->value;
#endif
}

void DigitalPin::write(bool value)
{
    if (this->mode == PinMode::Output)
    {
#ifdef ARDUINO
        digitalWrite(number, value ? HIGH : LOW);
#endif
        this->value = value;
    }
}
