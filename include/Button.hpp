#ifndef BUTTON_HPP
#define BUTTON_HPP

/**
 * @file Button.hpp
 * @brief Helper class representing a user input button with click detection.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include <chrono>
#include "Peripheral.hpp"

class Button : public Peripheral
{
    public:
    /** Construct a new button. */
    Button();

    /** Virtual destructor. */
    ~Button() override;

    /**
     * @brief Set the time threshold used to detect a click.
     *
     * @param duration Maximum duration of a press considered a click.
     */
    void setClickThreshold(std::chrono::milliseconds duration);

    /** @return The configured click threshold. */
    std::chrono::milliseconds getClickThreshold() const;

    /** Record the time when the button is pressed. */
    void press();

    /**
     * @brief Release the button and report if it was a click.
     *
     * @return true if the press duration was below the threshold.
     */
    bool release();

    private:
    std::chrono::milliseconds clickThreshold;
    std::chrono::steady_clock::time_point pressTime;
};

#endif // BUTTON_HPP
