/**
 * @file PWMPin.cpp
 * @brief Implementation of PWMPin class.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "PWMPin.hpp"
#include <Arduino.h>

/** Construct a PWMPin with the given parameters. */
PWMPin::PWMPin(int number, int mode, int value, bool shared) : Pin<int>(number, mode, value, shared)
{
}

/** Destructor. */
PWMPin::~PWMPin()
{
}

/** Read the last written PWM value. */
int PWMPin::read() const
{
    return this->value;
}

/** Write a PWM value to the pin. */
void PWMPin::write(int value)
{
    if (mode == OUTPUT)
    {
        analogWrite(number, value);
        this->value = value;
    }
}
