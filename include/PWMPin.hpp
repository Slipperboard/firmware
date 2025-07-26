#ifndef PWM_PIN_HPP
#define PWM_PIN_HPP

/**
 * @file PWMPin.hpp
 * @brief Abstraction for pins supporting PWM output.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Pin.hpp"

class PWMPin : public Pin<int>
{
    public:
    /**
     * @brief Construct a PWM-capable pin.
     *
     * @param number GPIO pin number.
     * @param mode   Pin mode (typically OUTPUT).
     * @param value  Initial PWM value.
     * @param shared Whether the pin is shared with other peripherals.
     */
    explicit PWMPin(int number, int mode, int value = 0, bool shared = false);

    /** Destructor. */
    ~PWMPin() override;

    /** @return Current PWM value of the pin. */
    int read() const override;

    /**
     * @brief Output a PWM value on the pin.
     *
     * @param value PWM value to write.
     */
    void write(int value) override;
};

#endif // PWM_PIN_HPP
