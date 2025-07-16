#include "PWMPin.hpp"
#include <Arduino.h>

PWMPin::PWMPin(int number, PinMode mode, int value) : Pin<int>(number, mode, value)
{
}

PWMPin::~PWMPin() = default;

void PWMPin::init()
{
    pinMode(number, OUTPUT);
    analogWrite(number, value);
}

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
