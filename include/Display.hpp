#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Peripheral.hpp"
#include <cstddef>

struct Dimensions {
    int width;
    int height;
};

struct Point {
    int x;
    int y;
};

class Display : public Peripheral
{
    public:
    // Construct a rectangular display
    explicit Display(Dimensions dims);
    // Construct a circular display
    explicit Display(int radius);
    ~Display() override;

    int getWidth() const;
    int getHeight() const;
    int getRadius() const;
    bool isCircular() const;

    // Draw a series of bytes at the given coordinate
    virtual void drawBytes(Point pos, const unsigned char *data, std::size_t length) = 0;

    protected:
    bool circular;
    int width;
    int height;
    int radius;
};

#endif // DISPLAY_HPP
