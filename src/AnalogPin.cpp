#include "AnalogPin.hpp"

AnalogPin::AnalogPin(PinMode mode, int value)
    : Pin<int>(mode, value) {}

AnalogPin::~AnalogPin() = default;

int AnalogPin::read() const {
    return this->value_;
}

void AnalogPin::write(int value) {
    if (this->mode_ == PinMode::Output) {
        this->value_ = value;
    }
}

