#include "OledDisplay.hpp"
#include "LvglStub.hpp"

OledDisplay::OledDisplay() : Display({128, 64}), buffer(static_cast<std::size_t>(128) * 64, 0), hw(128, 64)
{
}

void OledDisplay::init()
{
    // Initialize the display hardware and lvgl. In this stub implementation the
    // calls are no-ops but mimic the real libraries.
    lv_init();
    hw.begin();
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
            buffer[py * width + px] = data[i];
            lv_draw_pixel(static_cast<int16_t>(px), static_cast<int16_t>(py), data[i]);
            hw.drawPixel(static_cast<int16_t>(px), static_cast<int16_t>(py), data[i]);
        }
    }
    hw.display();
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
