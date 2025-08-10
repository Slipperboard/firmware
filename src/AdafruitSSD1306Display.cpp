#include "AdafruitSSD1306Display.hpp"

#ifdef ARDUINO
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static Adafruit_SSD1306 oled(128, 64, &Wire);
#endif

AdafruitSSD1306Display::AdafruitSSD1306Display(Dimensions dims) : Display(dims)
{
#ifdef ARDUINO
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.clearDisplay();
#endif
}

void AdafruitSSD1306Display::writeBytes(Point pos, const unsigned char* data, std::size_t length)
{
#ifdef ARDUINO
    oled.setCursor(pos.x, pos.y);
    for (std::size_t i = 0; i < length; ++i)
    {
        oled.write(data[i]);
    }
    oled.display();
#else
    (void) pos;
    (void) data;
    (void) length;
#endif
}
