#include "AnalogPin.hpp"
#ifdef ARDUINO
#include <Arduino.h>
#endif

AnalogPin::AnalogPin(int number, PinMode mode, int value) : Pin<int>(number, mode, value)
{
}

AnalogPin::~AnalogPin() = default;

void AnalogPin::init()
{
#ifdef ARDUINO
    pinMode(number, mode == PinMode::Output ? OUTPUT : INPUT);
#endif
}

int AnalogPin::read() const
{
#ifdef ARDUINO
    if (mode == PinMode::Input)
    {
        return analogRead(number);
    }
#endif
    return this->value;
}

void AnalogPin::write(int value)
{
    if (this->mode != PinMode::Output)
    {
        return;
    }
#ifdef ARDUINO
    analogWrite(number, value);
#endif
    this->value = value;
}
