#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

#include "Pin.hpp"

class DigitalPin : public Pin<bool> {
public:
    DigitalPin(PinMode mode, bool value = false);
    ~DigitalPin() override;

    bool digitalRead() const;
    void digitalWrite(bool value);
};

#endif // DIGITAL_PIN_HPP
