#include "AnalogPin.hpp"

AnalogPin::AnalogPin(PinMode mode, int value) : Pin<int>(mode, value)
{
}

AnalogPin::~AnalogPin() = default;

int AnalogPin::read() const
{
    return this->value;
}

void AnalogPin::write(int value)
{
    if (this->mode == PinMode::Output)
    {
        this->value = value;
    }
}
