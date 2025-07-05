#include "DigitalPin.hpp"

DigitalPin::DigitalPin(PinMode mode, bool value)
    : Pin<bool>(mode, value) {}

DigitalPin::~DigitalPin() = default;

bool DigitalPin::digitalRead() const {
    return this->read();
}

void DigitalPin::digitalWrite(bool value) {
    this->write(value);
}

