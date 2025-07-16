#include "PWMPin.hpp"
#include <Arduino.h>

PWMPin::PWMPin(int number, PinMode mode, int value) : Pin<int>(number, mode, value)
{
    pinMode(number, OUTPUT);
    analogWrite(number, value);
}

PWMPin::~PWMPin() = default;


int PWMPin::read() const
{
    return this->value;
}

void PWMPin::write(int value)
{
    if (mode == PinMode::Output)
    {
        analogWrite(number, value);
        this->value = value;
    }
}
