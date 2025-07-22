/**
 * @file PWMPin.cpp
 * @brief Implementation of PWMPin class.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "PWMPin.hpp"
#include <Arduino.h>

PWMPin::PWMPin(int number, int mode, int value, bool isShared) : Pin<int>(number, mode, value, isShared)
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
