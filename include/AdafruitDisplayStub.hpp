#ifndef ADAFRUIT_DISPLAY_STUB_HPP
#define ADAFRUIT_DISPLAY_STUB_HPP

#include <cstdint>

class AdafruitDisplayStub {
public:
    AdafruitDisplayStub(int16_t width, int16_t height) {
        static_cast<void>(width);
        static_cast<void>(height);
    }
    bool begin() { return true; }
    void drawPixel(int16_t, int16_t, uint8_t) {}
    void display() {}
};

#endif // ADAFRUIT_DISPLAY_STUB_HPP
