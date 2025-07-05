#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

#include "Pin.hpp"

class DigitalPin : public Pin {
public:
    DigitalPin(PinMode mode, int value = 0);
    ~DigitalPin() override;

    bool digitalRead() const;
    void digitalWrite(int value);
};

#endif // DIGITAL_PIN_HPP
