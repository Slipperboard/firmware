#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "Peripheral.hpp"
#include <cstddef>

class Display : public Peripheral {
public:
    // Construct a rectangular display
    Display(int width, int height);
    // Construct a circular display
    explicit Display(int radius);
    ~Display() override;

    int getWidth() const;
    int getHeight() const;
    int getRadius() const;
    bool isCircular() const;

    // Draw a series of bytes at the given x/y coordinate
    virtual void drawBytes(int x, int y, const unsigned char* data,
                           std::size_t length) = 0;

protected:
    bool circular;
    int width;
    int height;
    int radius;
};

#endif // DISPLAY_HPP
