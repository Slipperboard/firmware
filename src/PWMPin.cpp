/**
 * @file PWMPin.cpp
 * @brief Implementation of PWMPin class.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "PWMPin.hpp"
#include <Arduino.h>

PWMPin::PWMPin(int number, int mode, int value) : Pin<int>(number, mode, value)
{
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
