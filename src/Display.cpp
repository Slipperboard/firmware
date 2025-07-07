#include "Display.hpp"

Display::Display(Dimensions dims) : circular(false), width(dims.width), height(dims.height), radius(0)
{
}

Display::Display(int radius) : circular(true), width(0), height(0), radius(radius)
{
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
int Display::getRadius() const
{
    return radius;
}
bool Display::isCircular() const
{
    return circular;
}
