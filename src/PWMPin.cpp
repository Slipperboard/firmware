#include "PWMPin.hpp"
#ifdef ARDUINO
#include <Arduino.h>
#endif

PWMPin::PWMPin(int number, PinMode mode, int value) : Pin<int>(number, mode, value)
{
}

PWMPin::~PWMPin() = default;

void PWMPin::init()
{
#ifdef ARDUINO
    pinMode(number, OUTPUT);
    analogWrite(number, value);
#endif
}

int PWMPin::read() const
{
#ifdef ARDUINO
    return this->value;
#else
    return this->value;
#endif
}

void PWMPin::write(int value)
{
    if (mode == PinMode::Output)
    {
#ifdef ARDUINO
        analogWrite(number, value);
#endif
        this->value = value;
    }
}
