#include "Oled096Display.hpp"
#include <cstring>

Oled096Display::Oled096Display()
    : Display(128, 64),
      buffer(width * height, 0),
      driver(width, height),
      lvDisp(nullptr),
      lvBuffer(width * height, 0),
      initialized(false) {}

Oled096Display::~Oled096Display() = default;

void Oled096Display::init() {
    driver.begin(0, 0x3C);
    driver.clearDisplay();

    lv_init();
    lv_disp_draw_buf_init(&drawBuf, lvBuffer.data(), nullptr, width * height);
    lv_disp_drv_init(&dispDrv);
    dispDrv.hor_res = width;
    dispDrv.ver_res = height;
    dispDrv.flush_cb = lvglFlush;
    dispDrv.draw_buf = &drawBuf;
    dispDrv.user_data = this;
    lvDisp = lv_disp_drv_register(&dispDrv);

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

lv_disp_t* Oled096Display::getLvglDisplay() {
    return lvDisp;
}

void Oled096Display::lvglFlush(lv_disp_drv_t* drv, const lv_area_t* area, lv_color_t* color_p) {
    auto* self = static_cast<Oled096Display*>(drv->user_data);
    for (int y = area->y1; y <= area->y2; ++y) {
        std::memcpy(&self->buffer[y * self->width + area->x1],
                    color_p + (y - area->y1) * (area->x2 - area->x1 + 1),
                    area->x2 - area->x1 + 1);
    }
    self->driver.display();
}

