#ifndef ESP_PLATFORM
#define ESP_PLATFORM 0
#endif
// cppcheck-suppress toomanyconfigs
#include "OledDisplay.hpp"
#ifdef ESP_PLATFORM
#include <Wire.h>
#endif

OledDisplay::OledDisplay()
    : Display({128, 64}), display(128, 64, &Wire, -1), buffer(static_cast<std::size_t>(128) * 64, 0)
{
}

void OledDisplay::init()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
    lv_init();
    // mark the display as ready.
    initialized = true;
}

void OledDisplay::drawBytes(Point pos, const unsigned char *data, std::size_t length)
{
    // Simple buffer write emulation. Each byte represents a pixel.
    if (!initialized)
        return;
    for (std::size_t i = 0; i < length; ++i)
    {
        int px = pos.x + static_cast<int>(i);
        int py = pos.y;
        if (px >= 0 && px < width && py >= 0 && py < height)
        {
            display.drawPixel(px, py, data[i] ? SSD1306_WHITE : SSD1306_BLACK);
        }
    }
    display.display();
    for (std::size_t i = 0; i < length; ++i)
    {
        int px = pos.x + static_cast<int>(i);
        int py = pos.y;
        if (px >= 0 && px < width && py >= 0 && py < height)
        {
            buffer[py * width + px] = data[i];
        }
    }
}

void OledDisplay::readBytes(Point pos, unsigned char *out, std::size_t length) const
{
    for (std::size_t i = 0; i < length; ++i)
    {
        int px = pos.x + static_cast<int>(i);
        int py = pos.y;
        if (px < 0 || px >= width || py < 0 || py >= height)
        {
            out[i] = 0;
            continue;
        }
        out[i] = buffer[py * width + px];
    }
}
