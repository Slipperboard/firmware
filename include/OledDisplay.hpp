#ifndef OLED_DISPLAY_HPP
#define OLED_DISPLAY_HPP

#include <vector>
#include "Display.hpp"
#ifdef ESP_PLATFORM
#include <Adafruit_SSD1306.h>
#include <lvgl.h>
#endif

class OledDisplay : public Display
{
    public:
    OledDisplay();
    ~OledDisplay() override = default;

    void init() override;
    void drawBytes(Point pos, const unsigned char* data, std::size_t length) override;

    // helper for tests
    void readBytes(Point pos, unsigned char* out, std::size_t length) const;

    private:
    std::vector<unsigned char> buffer;
#ifdef ESP_PLATFORM
    Adafruit_SSD1306 ssd1306{128, 64, &Wire, -1};
    lv_obj_t* canvas = nullptr;
    std::vector<lv_color_t> lv_buffer;
    lv_disp_draw_buf_t draw_buf;
    lv_disp_drv_t disp_drv;
    static void flushCallback(lv_disp_drv_t* drv, const lv_area_t* area, lv_color_t* color_p);
#endif
    bool initialized = false;
};

#endif // OLED_DISPLAY_HPP
