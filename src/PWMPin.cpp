#include "PWMPin.hpp"
#include <Arduino.h>

PWMPin::PWMPin(int number, int mode, int value) : Pin<int>(number, mode, value)
{
    analogWrite(number, value);
}

PWMPin::~PWMPin()
{
}

int PWMPin::read() const
{
    return this->value;
}

void PWMPin::write(int value)
{
    if (mode == OUTPUT)
    {
        analogWrite(number, value);
        this->value = value;
    }
}
