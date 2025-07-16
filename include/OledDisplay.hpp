#ifndef OLED_DISPLAY_HPP
#define OLED_DISPLAY_HPP

#include <vector>
#include "Display.hpp"

class OledDisplay : public Display
{
    public:
    OledDisplay();
    ~OledDisplay() override = default;
    void drawBytes(Point pos, const unsigned char* data, std::size_t length) override;

    // helper for tests
    void readBytes(Point pos, unsigned char* out, std::size_t length) const;

    private:
    std::vector<unsigned char> buffer;
    bool initialized = false;
};

#endif // OLED_DISPLAY_HPP
