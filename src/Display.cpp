#include "Display.hpp"

Display::Display(int width, int height)
    : initialized(false), width(width), height(height) {}

Display::~Display() = default;

int Display::getWidth() const { return width; }
int Display::getHeight() const { return height; }
bool Display::isInitialized() const { return initialized; }
