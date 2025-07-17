#ifndef DISPLAYTILE_HPP
#define DISPLAYTILE_HPP

#include <vector>
#include "Display.hpp"

struct Rect
{
    int x;
    int y;
    int width;
    int height;
};

class DisplayTile
{
    public:
    DisplayTile(Display& root, Point origin, Dimensions dims, std::vector<Rect>& siblings);

    int getWidth() const;
    int getHeight() const;

    DisplayTile createTile(Point origin, Dimensions dims);

    void drawBytes(Point pos, const unsigned char* data, std::size_t length);

    void focus();
    void unfocus();

    private:
    Display& root;
    Point origin;
    Dimensions dims;
    std::vector<Rect>& siblings;
    std::vector<Rect> children;
};

#endif // DISPLAYTILE_HPP
