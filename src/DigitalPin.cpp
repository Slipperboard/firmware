#include "DigitalPin.hpp"

DigitalPin::DigitalPin(PinMode mode, bool value) : Pin<bool>(mode, value)
{
}

DigitalPin::~DigitalPin() = default;

bool DigitalPin::read() const
{
    return this->value;
}

void DigitalPin::write(bool value)
{
    if (this->mode == PinMode::Output)
    {
        this->value = value;
    }
}
