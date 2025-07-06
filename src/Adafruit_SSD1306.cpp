#include "Adafruit_SSD1306.h"
#include <algorithm>

Adafruit_SSD1306::Adafruit_SSD1306(int16_t w, int16_t h)
    : width(w), height(h), buffer(w * h, 0) {}

bool Adafruit_SSD1306::begin(int, uint8_t) { return true; }

void Adafruit_SSD1306::clearDisplay() {
    std::fill(buffer.begin(), buffer.end(), 0);
}

void Adafruit_SSD1306::display() {}

uint8_t* Adafruit_SSD1306::getBuffer() { return buffer.data(); }
