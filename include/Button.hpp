#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <chrono>
#include "Peripheral.hpp"

class Button : public Peripheral
{
    public:
    Button();
    ~Button() override;

    void setClickThreshold(std::chrono::milliseconds duration);
    std::chrono::milliseconds getClickThreshold() const;

    void press();
    bool release();

    private:
    std::chrono::milliseconds clickThreshold;
    std::chrono::steady_clock::time_point pressTime;
};

#endif // BUTTON_HPP
