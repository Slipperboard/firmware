#include "AnalogPin.hpp"
#include <Arduino.h>

AnalogPin::AnalogPin(int number, int mode, int value) : Pin<int>(number, mode, value)
{
}

AnalogPin::~AnalogPin()
{
}

int AnalogPin::read() const
{
    if (mode == INPUT)
    {
        return analogRead(number);
    }
    return this->value;
}

void AnalogPin::write(int value)
{
    if (this->mode != OUTPUT)
    {
        return;
    }
    analogWrite(number, value);
    this->value = value;
}
