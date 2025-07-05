#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

#include "Pin.hpp"

class AnalogPin : public Pin<int> {
public:
    AnalogPin(PinMode mode, int value = 0) : Pin<int>(mode, value) {}
    ~AnalogPin() override = default;

    int analogRead() const { return this->read(); }
    void analogWrite(int value) { this->write(value); }
};

#endif // ANALOG_PIN_HPP
