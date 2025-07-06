#include "Display.hpp"

Display::Display(int width, int height) : circular(false), width(width), height(height), radius(0)
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
