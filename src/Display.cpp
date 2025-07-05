#include "Display.hpp"

Display::Display(int width, int height)
    : width(width), height(height) {}

Display::~Display() = default;

int Display::getWidth() const { return width; }
int Display::getHeight() const { return height; }
