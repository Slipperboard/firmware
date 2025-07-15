#include "DigitalPin.hpp"
#include "ArduinoCompat.hpp"

DigitalPin::DigitalPin(int number, PinMode mode, bool value) : Pin<bool>(number, mode, value)
{
}

DigitalPin::~DigitalPin() = default;

void DigitalPin::init()
{
    pinMode(number, mode == PinMode::Output ? OUTPUT : INPUT);
}

bool DigitalPin::read() const
{
    return digitalRead(number);
}

void DigitalPin::write(bool value)
{
    if (this->mode == PinMode::Output)
    {
        digitalWrite(number, value ? HIGH : LOW);
        this->value = value;
    }
}
