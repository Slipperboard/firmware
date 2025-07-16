#include "AnalogPin.hpp"
#include <Arduino.h>

AnalogPin::AnalogPin(int number, PinMode mode, int value) : Pin<int>(number, mode, value)
{
    pinMode(number, mode == PinMode::Output ? OUTPUT : INPUT);
}

AnalogPin::~AnalogPin() = default;


int AnalogPin::read() const
{
    if (mode == PinMode::Input)
    {
        return analogRead(number);
    }
    return this->value;
}

void AnalogPin::write(int value)
{
    if (this->mode != PinMode::Output)
    {
        return;
    }
    analogWrite(number, value);
    this->value = value;
}
