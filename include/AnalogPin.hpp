#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

#include "Pin.hpp"

class AnalogPin : public Pin<int>
{
    public:
    explicit AnalogPin(PinMode mode, int value = 0);
    ~AnalogPin() override;

    int read() const override;
    void write(int value) const override;
};

#endif // ANALOG_PIN_HPP
