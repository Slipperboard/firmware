#include "OledDisplay.hpp"
#ifdef ESP_PLATFORM
#include <Wire.h>
#endif

OledDisplay::OledDisplay() : Display({128, 64}), buffer(static_cast<std::size_t>(128) * 64, 0)
{
}

void OledDisplay::init()
{
#ifdef ESP_PLATFORM
    Wire.begin();
    ssd1306.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    ssd1306.clearDisplay();

    lv_init();
    lv_buffer.resize(static_cast<std::size_t>(width) * height);
    canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, lv_buffer.data(), width, height, LV_COLOR_FORMAT_A8);
    lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_COVER);

    lv_disp_draw_buf_init(&draw_buf, lv_buffer.data(), nullptr, width * height);
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = width;
    disp_drv.ver_res = height;
    disp_drv.flush_cb = flushCallback;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.user_data = this;
    lv_disp_drv_register(&disp_drv);
#endif
    initialized = true;
}

void OledDisplay::drawBytes(Point pos, const unsigned char* data, std::size_t length)
{
    if (!initialized)
    {
        return;
    }
    for (std::size_t i = 0; i < length; ++i)
    {
        int px = pos.x + static_cast<int>(i);
        int py = pos.y;
        if (px >= 0 && px < width && py >= 0 && py < height)
        {
            buffer[py * width + px] = data[i];
#ifdef ESP_PLATFORM
            lv_canvas_set_px(canvas, px, py, lv_color_make(data[i], data[i], data[i]), LV_OPA_COVER);
            ssd1306.drawPixel(px, py, data[i] ? WHITE : BLACK);
#endif
        }
    }
#ifdef ESP_PLATFORM
    ssd1306.display();
#endif
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

#ifdef ESP_PLATFORM
void OledDisplay::flushCallback(lv_disp_drv_t* drv, const lv_area_t* area, lv_color_t* color_p)
{
    auto* self = static_cast<OledDisplay*>(drv->user_data);
    for (int y = area->y1; y <= area->y2; ++y)
    {
        for (int x = area->x1; x <= area->x2; ++x, ++color_p)
        {
            self->ssd1306.drawPixel(x, y, color_p->full ? WHITE : BLACK);
        }
    }
    self->ssd1306.display();
    lv_disp_flush_ready(drv);
}
#endif
