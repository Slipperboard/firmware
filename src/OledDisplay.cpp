#include "OledDisplay.hpp"

#include <Wire.h>

OledDisplay::OledDisplay() : Display({128, 64}), buffer(static_cast<std::size_t>(128) * 64, 0)
{
}

OledDisplay::~OledDisplay()
{
    if (lvBuffer != nullptr)
    {
        free(lvBuffer);
        lvBuffer = nullptr;
    }
}

void OledDisplay::init()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        return;
    }
    display.clearDisplay();
    lv_init();
    lvBuffer = static_cast<lv_color_t *>(malloc(static_cast<size_t>(width) * height * sizeof(lv_color_t)));
    lv_disp_draw_buf_init(&drawBuf, lvBuffer, nullptr, width * height);
    lv_disp_drv_init(&dispDrv);
    dispDrv.draw_buf = &drawBuf;
    dispDrv.hor_res = width;
    dispDrv.ver_res = height;
    dispDrv.flush_cb = flushCallback;
    lv_disp_drv_register(&dispDrv);
    initialized = true;
}

void OledDisplay::drawBytes(Point pos, const unsigned char *data, std::size_t length)
{
    if (!initialized)
        return;
    for (std::size_t i = 0; i < length; ++i)
    {
        int px = pos.x + static_cast<int>(i);
        int py = pos.y;
        if (px >= 0 && px < width && py >= 0 && py < height)
        {
            buffer[py * width + px] = data[i];
            display.drawPixel(px, py, data[i] ? WHITE : BLACK);
        }
    }
    display.display();
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

Adafruit_SSD1306 OledDisplay::display(128, 64, &Wire, -1);
lv_disp_draw_buf_t OledDisplay::drawBuf;
lv_disp_drv_t OledDisplay::dispDrv;
lv_color_t *OledDisplay::lvBuffer = nullptr;

void OledDisplay::flushCallback(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color)
{
    for (int y = area->y1; y <= area->y2; ++y)
    {
        for (int x = area->x1; x <= area->x2; ++x, ++color)
        {
            display.drawPixel(x, y, color->full ? WHITE : BLACK);
        }
    }
    display.display();
    lv_disp_flush_ready(drv);
}
