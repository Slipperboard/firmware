#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

/**
 * @file AnalogPin.hpp
 * @brief Abstraction for analog input/output pins.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Pin.hpp"

#include <Arduino.h>

class AnalogPin : public Pin<int>
{
    public:
    /**
     * @brief Construct an AnalogPin with the given configuration.
     *
     * @param number GPIO pin number.
     * @param mode   Pin mode (INPUT or OUTPUT).
     * @param value  Initial analog value.
     * @param shared Whether the pin is shared with other peripherals.
     */
    explicit AnalogPin(int number, int mode, int value = 0, bool shared = false);

    /** Destructor. */
    ~AnalogPin() override;

    /**
     * @brief Read the current value of the pin.
     *
     * @return The analog value currently present on the pin.
     */
    int read() const override;

    /**
     * @brief Write a new value to the pin.
     *
     * @param value Analog value to output.
     */
    void write(int value) override;
};

#endif // ANALOG_PIN_HPP
