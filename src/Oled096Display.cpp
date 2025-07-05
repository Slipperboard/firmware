#include "Oled096Display.hpp"
#include <cstring>

Oled096Display::Oled096Display()
    : Display(128, 64), buffer(width * height, 0), initialized(false) {}

Oled096Display::~Oled096Display() = default;

void Oled096Display::init() {
    initialized = true;
}

bool Oled096Display::isInitialized() const {
    return initialized;
}

void Oled096Display::drawBytes(int x, int y, const uint8_t* data, std::size_t len) {
    if (x < 0 || y < 0 || x + static_cast<int>(len) > width || y >= height) {
        return;
    }
    std::memcpy(&buffer[y * width + x], data, len);
}

uint8_t Oled096Display::readByte(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return 0;
    }
    return buffer[y * width + x];
}

