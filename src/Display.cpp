/**
 * @file Display.cpp
 * @brief Implementation of Display interface and tile management.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include "Display.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>
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
    buffer.resize(height, std::vector<unsigned char>(width, ' '));
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
    for (std::size_t i = 0; i < length; ++i)
    {
        int x = pos.x + static_cast<int>(i);
        int y = pos.y;
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            buffer[y][x] = data[i];
        }
    }
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

/** Save the current buffer to the stack for later restoration. */
void Display::pushState()
{
    stack.push_back(buffer);
}

/** Restore the last saved buffer from the stack and redraw it. */
void Display::popState()
{
    if (stack.empty())
    {
        throw std::runtime_error("No saved state");
    }
    buffer = stack.back();
    stack.pop_back();
    for (int y = 0; y < height; ++y)
    {
        drawBytes({0, y}, buffer[y].data(), buffer[y].size());
    }
}

/** Clear the display to spaces and reset the buffer. */
void Display::clear()
{
    unsigned char space = ' ';
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            buffer[y][x] = space;
        }
        drawBytes({0, y}, buffer[y].data(), buffer[y].size());
    }
}
