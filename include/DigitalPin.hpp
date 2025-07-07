#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

#include "Pin.hpp"

class DigitalPin : public Pin<bool>
{
    public:
    explicit DigitalPin(PinMode mode, bool value = false);
    ~DigitalPin() override;

    bool read() const override;
    void write(bool value) override;
};

#endif // DIGITAL_PIN_HPP
