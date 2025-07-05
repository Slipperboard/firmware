#ifndef ADAFRUIT_SSD1306_H
#define ADAFRUIT_SSD1306_H

#include <stdint.h>
#include <vector>

class Adafruit_SSD1306 {
public:
    Adafruit_SSD1306(int16_t w, int16_t h)
        : width(w), height(h), buffer(w * h, 0) {}

    bool begin(int, uint8_t) { return true; }
    void clearDisplay() { std::fill(buffer.begin(), buffer.end(), 0); }
    void display() {}
    uint8_t* getBuffer() { return buffer.data(); }

private:
    int16_t width;
    int16_t height;
    std::vector<uint8_t> buffer;
};

#endif // ADAFRUIT_SSD1306_H
