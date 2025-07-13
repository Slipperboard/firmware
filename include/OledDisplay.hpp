#ifndef OLED_DISPLAY_HPP
#define OLED_DISPLAY_HPP

#include "Display.hpp"
#include <vector>

#ifdef ESP_PLATFORM
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <lvgl.h>
#endif

class OledDisplay : public Display
{
    public:
    OledDisplay();
    ~OledDisplay() override = default;

    void init() override;
    void drawBytes(Point pos, const unsigned char *data, std::size_t length) override;

    // helper for tests
    void readBytes(Point pos, unsigned char *out, std::size_t length) const;

    private:
    std::vector<unsigned char> buffer;
    bool initialized = false;
#ifdef ESP_PLATFORM
    Adafruit_SSD1306 oled{128, 64, &Wire, -1};
#endif
};

#endif // OLED_DISPLAY_HPP
