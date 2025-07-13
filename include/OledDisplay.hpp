#ifndef OLED_DISPLAY_HPP
#define OLED_DISPLAY_HPP

#include "Display.hpp"
#include <vector>
#ifndef ESP_PLATFORM
#define ESP_PLATFORM 0
#endif
#include <Wire.h>

#if ESP_PLATFORM
#include <Adafruit_SSD1306.h>
#include <lvgl.h>
#else
class Adafruit_SSD1306
{
    public:
    Adafruit_SSD1306(int, int, void *, int)
    {
    }
    // cppcheck-suppress functionStatic
    bool begin(int, int)
    {
        return true;
    }
    // cppcheck-suppress functionStatic
    void clearDisplay()
    {
    }
    // cppcheck-suppress functionStatic
    void display()
    {
    }
    // cppcheck-suppress functionStatic
    void drawPixel(int, int, int)
    {
    }
};
inline void lv_init()
{
}
#define SSD1306_SWITCHCAPVCC 0
#define SSD1306_WHITE 1
#define SSD1306_BLACK 0
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
    Adafruit_SSD1306 display;
    std::vector<unsigned char> buffer;
    bool initialized = false;
};

#endif // OLED_DISPLAY_HPP
