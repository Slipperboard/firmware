/**
 * @file AnalogPin.cpp
 * @brief Implementation of AnalogPin class.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "AnalogPin.hpp"
#include <Arduino.h>

/** Construct an AnalogPin with the given parameters. */
AnalogPin::AnalogPin(int number, int mode, int value, bool shared) : Pin<int>(number, mode, value, shared)
{
}

/** Destructor. */
AnalogPin::~AnalogPin()
{
}

/** Read the analog value from the pin. */
int AnalogPin::read() const
{
    if (mode == INPUT)
    {
        return analogRead(number);
    }
    return this->value;
}

/** Write an analog value to the pin. */
void AnalogPin::write(int value)
{
    if (this->mode != OUTPUT)
    {
        return;
    }
    analogWrite(number, value);
    this->value = value;
}
