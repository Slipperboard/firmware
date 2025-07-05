#include "DigitalPin.hpp"

DigitalPin::DigitalPin(PinMode mode, int value)
    : Pin(mode, value) {}

DigitalPin::~DigitalPin() = default;

bool DigitalPin::digitalRead() const { return value_ != 0; }

void DigitalPin::digitalWrite(int value) {
    if (mode_ == PinMode::Output) {
        value_ = value ? 1 : 0;
    }
}
