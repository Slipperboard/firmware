/**
 * @file Button.cpp
 * @brief Implementation of Button class with click duration support.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Button.hpp"

Button::Button() : clickThreshold(std::chrono::milliseconds(200))
{
}
Button::~Button() = default;

void Button::setClickThreshold(std::chrono::milliseconds duration)
{
    clickThreshold = duration;
}

std::chrono::milliseconds Button::getClickThreshold() const
{
    return clickThreshold;
}

void Button::press()
{
    pressTime = std::chrono::steady_clock::now();
}

bool Button::release()
{
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - pressTime);
    return diff <= clickThreshold;
}
