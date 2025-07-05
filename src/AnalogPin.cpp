#include "AnalogPin.hpp"

AnalogPin::AnalogPin(PinMode mode, int value)
    : Pin<int>(mode, value) {}

AnalogPin::~AnalogPin() = default;

int AnalogPin::analogRead() const {
    return this->read();
}

void AnalogPin::analogWrite(int value) {
    this->write(value);
}

