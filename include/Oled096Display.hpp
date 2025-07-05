#ifndef OLED096_DISPLAY_HPP
#define OLED096_DISPLAY_HPP

#include "Display.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

class Oled096Display : public Display {
public:
    Oled096Display();
    ~Oled096Display() override;

    void init() override;

    void drawBytes(int x, int y, const uint8_t* data, std::size_t len);
    uint8_t readByte(int x, int y) const;

private:
    std::vector<uint8_t> buffer;
};

#endif // OLED096_DISPLAY_HPP
