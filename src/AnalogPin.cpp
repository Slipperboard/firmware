#include "AnalogPin.hpp"

AnalogPin::AnalogPin(PinMode mode, int value)
    : Pin(mode, value) {}

AnalogPin::~AnalogPin() = default;

int AnalogPin::analogRead() const { return value_; }

void AnalogPin::analogWrite(int value) {
    if (mode_ == PinMode::Output) {
        value_ = value;
    }
}
