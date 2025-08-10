#ifndef ADAFRUIT_SSD1306_DISPLAY_HPP
#define ADAFRUIT_SSD1306_DISPLAY_HPP

#include "Display.hpp"

/**
 * @brief Display implementation backed by the Adafruit SSD1306 library.
 */
class AdafruitSSD1306Display : public Display
{
    public:
    explicit AdafruitSSD1306Display(Dimensions dims);
    ~AdafruitSSD1306Display() override = default;

    protected:
    void writeBytes(Point pos, const unsigned char* data, std::size_t length) override;
};

#endif // ADAFRUIT_SSD1306_DISPLAY_HPP
