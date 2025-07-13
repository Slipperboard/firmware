#include "OledDisplay.hpp"

#ifdef ESP_PLATFORM
static Adafruit_SSD1306 *oled_ptr = nullptr;

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
    if (!oled_ptr)
        return;
    for (int y = area->y1; y <= area->y2; ++y)
    {
        for (int x = area->x1; x <= area->x2; ++x, ++color_p)
        {
            oled_ptr->drawPixel(x, y, color_p->full ? WHITE : BLACK);
        }
    }
    oled_ptr->display();
    lv_disp_flush_ready(drv);
}
#endif

OledDisplay::OledDisplay() : Display({128, 64}), buffer(static_cast<std::size_t>(128) * 64, 0)
{
}

void OledDisplay::init()
{
#ifdef ESP_PLATFORM
    lv_init();
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.clearDisplay();
    oled.display();

    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t lv_buf[128 * 64 / 8];
    lv_disp_draw_buf_init(&draw_buf, lv_buf, nullptr, 128 * 64);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 128;
    disp_drv.ver_res = 64;
    disp_drv.flush_cb = lvgl_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    oled_ptr = &oled;
#endif
    // Mark the display as ready for host tests as well
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
#ifdef ESP_PLATFORM
            oled.drawPixel(px, py, data[i] ? WHITE : BLACK);
#endif
        }
    }
#ifdef ESP_PLATFORM
    oled.display();
#endif
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
