/**
 * @file Button.cpp
 * @brief Implementation of Button class with click duration support.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Button.hpp"

/** Construct a button with a default click threshold. */
Button::Button() : clickThreshold(std::chrono::milliseconds(200))
{
}
Button::~Button() = default;

/** Set the maximum duration for a click. */
void Button::setClickThreshold(std::chrono::milliseconds duration)
{
    clickThreshold = duration;
}

/** Retrieve the configured click threshold. */
std::chrono::milliseconds Button::getClickThreshold() const
{
    return clickThreshold;
}

/** Record the press time. */
void Button::press()
{
    pressTime = std::chrono::steady_clock::now();
}

/** Release the button and check if it was a click. */
bool Button::release()
{
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - pressTime);
    return diff <= clickThreshold;
}
