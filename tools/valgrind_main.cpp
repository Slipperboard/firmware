/**
 * @file valgrind_main.cpp
 * @brief Minimal host application used for Valgrind checks.
 */

#include <vector>
#include "AnalogPin.hpp"
#include "DigitalPin.hpp"
#include "Display.hpp"
#include "Tile.hpp"

class DummyDisplay : public Display
{
    public:
    DummyDisplay() : Display({4, 4})
    {
    }
    void drawBytes(Point pos, const unsigned char* data, std::size_t length) override
    {
        Display::drawBytes(pos, data, length);
    }

    protected:
    void writeBytes(Point pos, const unsigned char* data, std::size_t length) override
    {
        (void) pos;
        (void) data;
        (void) length;
    }
};
#include "Arduino.h"
#include "Button.hpp"
#include "PWMPin.hpp"
#include "Sensor.hpp"
#include "Switch.hpp"

int main()
{
    AnalogPin a(0, INPUT);
    a.read();
    a.write(1);

    DigitalPin d(1, OUTPUT);
    d.write(1);
    d.read();

    PWMPin p(2, OUTPUT);
    p.write(true);

    Button b;
    b.press();
    b.release();

    Sensor s;
    Switch sw;

    DummyDisplay display;
    auto tile = display.createTile({0, 0}, {2, 2});
    tile.focus();
    tile.unfocus();
    display.clear();

    return 0;
}
