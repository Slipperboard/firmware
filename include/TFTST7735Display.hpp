#ifndef TFTST7735DISPLAY_HPP
#define TFTST7735DISPLAY_HPP

#include <cstdint>
#include "Display.hpp"

#ifdef ARDUINO
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#endif

/**
 * @brief Display driver for 1.8" TFT ST7735 screens.
 */
class TFTST7735Display : public Display
{
    public:
    /**
     * @brief Construct a ST7735 display.
     *
     * @param dims Physical dimensions of the display in characters.
     * @param cs   Chip select pin.
     * @param dc   Data/command pin.
     * @param rst  Reset pin.
     */
    TFTST7735Display(Dimensions dims, int8_t cs, int8_t dc, int8_t rst);

    /**
     * @brief Draw bytes on the TFT display.
     */
    void drawBytes(Point pos, const unsigned char* data, std::size_t length) override;

    private:
#ifdef ARDUINO
    Adafruit_ST7735 tft;
#endif
};

#endif // TFTST7735DISPLAY_HPP
