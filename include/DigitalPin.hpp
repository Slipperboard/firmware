#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

#include "Pin.hpp"

class DigitalPin : public Pin<bool>
{
    public:
    DigitalPin(int number, PinMode mode, bool value = false);
    ~DigitalPin() override;

    void init() override;
    bool read() const override;
    void write(bool value) const override;
};

#endif // DIGITAL_PIN_HPP
