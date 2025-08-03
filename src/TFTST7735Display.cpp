/**
 * @file TFTST7735Display.cpp
 * @brief Implementation of the ST7735 TFT display driver.
 */

#include "TFTST7735Display.hpp"

#ifdef ARDUINO
#include <SPI.h>
#include <Adafruit_ST7735.h>
#endif

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
TFTST7735Display::TFTST7735Display(Dimensions dims, int8_t cs, int8_t dc, int8_t rst)
    : Display(dims)
#ifdef ARDUINO
      ,
      tft(cs, dc, rst)
#endif
{
#ifdef ARDUINO
    tft.initR(INITR_BLACKTAB);
    tft.setRotation(1);
    tft.fillScreen(ST77XX_BLACK);
#else
    (void) cs;
    (void) dc;
    (void) rst;
#endif
}

void TFTST7735Display::drawBytes(Point pos, const unsigned char* data, std::size_t length)
{
#ifdef ARDUINO
    tft.setCursor(pos.x, pos.y);
    for (std::size_t i = 0; i < length; ++i)
    {
        tft.write(data[i]);
    }
#endif
    Display::drawBytes(pos, data, length);
}
