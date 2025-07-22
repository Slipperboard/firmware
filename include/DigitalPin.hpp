#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

/**
 * @file DigitalPin.hpp
 * @brief Abstraction for digital input/output pins.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Pin.hpp"

class DigitalPin : public Pin<bool>
{
    public:
    explicit DigitalPin(int number, int mode, bool value = false, bool isShared = false);
    ~DigitalPin() override;

    bool read() const override;
    void write(bool value) override;
};

#endif // DIGITAL_PIN_HPP
