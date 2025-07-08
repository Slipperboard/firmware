#ifndef OLED_DISPLAY_HPP
#define OLED_DISPLAY_HPP

#include "Display.hpp"
#include <vector>

#include <Adafruit_SSD1306.h>
#include <lvgl.h>

class OledDisplay : public Display
{
    public:
    OledDisplay();
    ~OledDisplay() override;

    void init() override;
    void drawBytes(Point pos, const unsigned char *data, std::size_t length) override;

    // helper for tests
    void readBytes(Point pos, unsigned char *out, std::size_t length) const;

    private:
    std::vector<unsigned char> buffer;
    bool initialized = false;

    static void flushCallback(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color);
    static Adafruit_SSD1306 display;
    static lv_disp_draw_buf_t drawBuf;
    static lv_disp_drv_t dispDrv;
    static lv_color_t *lvBuffer;
};

#endif // OLED_DISPLAY_HPP
