#include "Display.hpp"
#include <algorithm>
#include <stdexcept>
#include "DisplayTile.hpp"

#ifdef ARDUINO
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static Adafruit_SSD1306 oled(128, 64, &Wire);
#endif

Display::Display(Dimensions dims) : width(dims.width), height(dims.height)
{
#ifdef ARDUINO
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.clearDisplay();
#endif
}

Display::~Display() = default;

int Display::getWidth() const
{
    return width;
}
int Display::getHeight() const
{
    return height;
}

void Display::drawBytes(Point pos, const unsigned char* data, std::size_t length)
{
#ifdef ARDUINO
    oled.setCursor(pos.x, pos.y);
    for (std::size_t i = 0; i < length; ++i)
    {
        oled.write(data[i]);
    }
    oled.display();
#else
    (void) pos;
    (void) data;
    (void) length;
#endif
}

DisplayTile Display::createTile(Point origin, Dimensions dims)
{
    Rect r{origin.x, origin.y, dims.width, dims.height};
    auto collide = [&r](const Rect& t) {
        return !(r.x + r.width <= t.x || t.x + t.width <= r.x || r.y + r.height <= t.y || t.y + t.height <= r.y);
    };
    if (std::any_of(tiles.begin(), tiles.end(), collide))
    {
        throw std::runtime_error("Tile collision");
    }
    return DisplayTile(*this, origin, dims, tiles);
}
