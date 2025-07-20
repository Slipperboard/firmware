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
    explicit PWMPin(int number, int mode, int value = 0);
    ~PWMPin() override;
    int read() const override;
    void write(int value) override;
};

#endif // PWM_PIN_HPP
