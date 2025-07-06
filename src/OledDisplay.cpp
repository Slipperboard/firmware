#include "OledDisplay.hpp"

OledDisplay::OledDisplay() : Display(128, 64), buffer(128 * 64, 0)
{
}

void OledDisplay::init()
{
    // In a real implementation this would initialize the Adafruit and lvgl
    // libraries. Here we simply mark the display as ready.
    initialized = true;
}

void OledDisplay::drawBytes(int x, int y, const unsigned char *data, std::size_t length)
{
    // Simple buffer write emulation. Each byte represents a pixel.
    if (!initialized)
        return;
    for (std::size_t i = 0; i < length; ++i)
    {
        int px = x + static_cast<int>(i);
        int py = y;
        if (px >= 0 && px < width && py >= 0 && py < height)
        {
            buffer[py * width + px] = data[i];
        }
    }
}

void OledDisplay::readBytes(int x, int y, unsigned char *out, std::size_t length) const
{
    for (std::size_t i = 0; i < length; ++i)
    {
        int px = x + static_cast<int>(i);
        int py = y;
        if (px < 0 || px >= width || py < 0 || py >= height)
        {
            out[i] = 0;
        } else
        {
            out[i] = buffer[py * width + px];
        }
    }
}
