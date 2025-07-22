#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

/**
 * @file AnalogPin.hpp
 * @brief Abstraction for analog input/output pins.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Pin.hpp"

#include <Arduino.h>

class AnalogPin : public Pin<int>
{
    public:
    explicit AnalogPin(int number, int mode, int value = 0, bool isShared = false);
    ~AnalogPin() override;

    int read() const override;
    void write(int value) override;
};

#endif // ANALOG_PIN_HPP
