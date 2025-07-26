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
    /**
     * @brief Construct a DigitalPin.
     *
     * @param number GPIO pin number.
     * @param mode   Pin mode (INPUT or OUTPUT).
     * @param value  Initial logic level.
     * @param shared Whether the pin is shared with other peripherals.
     */
    explicit DigitalPin(int number, int mode, bool value = false, bool shared = false);

    /** Destructor. */
    ~DigitalPin() override;

    /**
     * @brief Read the digital value from the pin.
     *
     * @return true if HIGH, false if LOW.
     */
    bool read() const override;

    /**
     * @brief Write a logic level to the pin.
     *
     * @param value Logic level to set.
     */
    void write(bool value) override;
};

#endif // DIGITAL_PIN_HPP
