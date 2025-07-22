/**
 * @file AnalogPin.cpp
 * @brief Implementation of AnalogPin class.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "AnalogPin.hpp"
#include <Arduino.h>

AnalogPin::AnalogPin(int number, int mode, int value, bool isShared) : Pin<int>(number, mode, value, isShared)
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
