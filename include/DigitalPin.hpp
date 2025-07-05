#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

#include "Pin.hpp"

class DigitalPin : public Pin<bool> {
public:
    DigitalPin(PinMode mode, bool value = false) : Pin<bool>(mode, value) {}
    ~DigitalPin() override = default;

    bool digitalRead() const { return this->read(); }
    void digitalWrite(bool value) { this->write(value); }
};

#endif // DIGITAL_PIN_HPP
