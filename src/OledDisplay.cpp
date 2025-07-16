#include "OledDisplay.hpp"

OledDisplay::OledDisplay() : Display({128, 64}), buffer(static_cast<std::size_t>(width) * height, 0)
{
    // In a real implementation this would initialize the Adafruit and lvgl
    // libraries. Here we simply mark the display as ready.
    initialized = true;
}

void OledDisplay::drawBytes(Point pos, const unsigned char* data, std::size_t length)
{
    // Simple buffer write emulation. Each byte represents a pixel.
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

void OledDisplay::readBytes(Point pos, unsigned char* out, std::size_t length) const
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
