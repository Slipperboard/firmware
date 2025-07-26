/**
 * @file DigitalPin.cpp
 * @brief Implementation of DigitalPin class.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "DigitalPin.hpp"
#include <Arduino.h>

/** Construct a DigitalPin with the given parameters. */
DigitalPin::DigitalPin(int number, int mode, bool value, bool shared) : Pin<bool>(number, mode, value, shared)
{
}

/** Destructor. */
DigitalPin::~DigitalPin()
{
}

/** Read the logic level from the pin. */
bool DigitalPin::read() const
{
    if (mode == INPUT)
    {
        return digitalRead(number);
    }
    return this->value;
}

/** Write a logic level to the pin. */
void DigitalPin::write(bool value)
{
    if (this->mode == OUTPUT)
    {
        ::digitalWrite(number, value ? HIGH : LOW);
        this->value = value;
    }
}
