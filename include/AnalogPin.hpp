#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

#include "Pin.hpp"

#include <Arduino.h>

class AnalogPin : public Pin<int>
{
    public:
    explicit AnalogPin(int number, int mode, int value = 0);
    ~AnalogPin() override;

    int read() const override;
    void write(int value) override;
};

#endif // ANALOG_PIN_HPP
