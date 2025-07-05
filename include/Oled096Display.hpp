#ifndef OLED096_DISPLAY_HPP
#define OLED096_DISPLAY_HPP

#include "Display.hpp"
#include "Adafruit_SSD1306.h"
#include "lvgl.h"
#include <cstddef>
#include <cstdint>
#include <vector>

class Oled096Display : public Display {
public:
    Oled096Display();
    ~Oled096Display() override;

    void init() override;
    bool isInitialized() const override;

    void drawBytes(int x, int y, const uint8_t* data, std::size_t len);
    uint8_t readByte(int x, int y) const;

    lv_disp_t* getLvglDisplay();

private:
    static void lvglFlush(lv_disp_drv_t* drv, const lv_area_t* area, lv_color_t* color_p);
    std::vector<uint8_t> buffer;
    Adafruit_SSD1306 driver;
    lv_disp_draw_buf_t drawBuf;
    lv_disp_drv_t dispDrv;
    lv_disp_t* lvDisp;
    std::vector<lv_color_t> lvBuffer;
    bool initialized;
};

#endif // OLED096_DISPLAY_HPP
