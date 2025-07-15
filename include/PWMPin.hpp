#ifndef PWM_PIN_HPP
#define PWM_PIN_HPP

#include "Pin.hpp"

class PWMPin : public Pin<int>
{
    public:
    explicit PWMPin(int number, PinMode mode, int value = 0);
    ~PWMPin() override;
    int read() const override;
    void write(int value) override;

    private:
    int channel;
};

#endif // PWM_PIN_HPP
