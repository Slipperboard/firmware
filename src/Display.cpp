#include "Display.hpp"

Display::Display(Dimensions dims) : width(dims.width), height(dims.height)
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
