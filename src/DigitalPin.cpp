#include "DigitalPin.hpp"

DigitalPin::DigitalPin(PinMode mode, bool value)
    : Pin<bool>(mode, value) {}

DigitalPin::~DigitalPin() = default;

bool DigitalPin::read() const {
    return this->value_;
}

void DigitalPin::write(bool value) {
    if (this->mode_ == PinMode::Output) {
        this->value_ = value;
    }
}

