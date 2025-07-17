#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>
#include "Peripheral.hpp"

struct Rect;
class DisplayTile;

struct Dimensions
{
    int width;
    int height;
};

struct Point
{
    int x;
    int y;
};

class Display : public Peripheral
{
    public:
    // Construct a rectangular display
    explicit Display(Dimensions dims);
    ~Display() override;

    int getWidth() const;
    int getHeight() const;

    // Draw a series of bytes at the given coordinate using the underlying display
    virtual void drawBytes(Point pos, const unsigned char* data, std::size_t length) = 0;

    DisplayTile createTile(Point origin, Dimensions dims);

    protected:
    int width;
    int height;
    std::vector<Rect> tiles;
};

#endif // DISPLAY_HPP
