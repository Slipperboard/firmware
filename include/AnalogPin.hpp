#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

#include "Pin.hpp"

class AnalogPin : public Pin<int>
{
    public:
    explicit AnalogPin(int pinNumber, PinMode mode, int value = 0);
    ~AnalogPin() override;

    void init() override;

    int read() const override;
    void write(int value) override;
};

#endif // ANALOG_PIN_HPP
