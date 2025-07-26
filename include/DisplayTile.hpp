#ifndef DISPLAYTILE_HPP
#define DISPLAYTILE_HPP

/**
 * @file DisplayTile.hpp
 * @brief Smaller region within a Display used for layout management.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

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

    /** Proxy to Display::pushState for this tile's root display. */
    void pushState();
    /** Proxy to Display::popState for this tile's root display. */
    void popState();
    /** Clear the contents of the tile region. */
    void clear();

    void focus();
    void unfocus();

    bool isOnFocus() const;

    private:
    Display& root;
    Point origin;
    Dimensions dims;
    std::vector<Rect>& siblings;
    std::vector<Rect> children;
    bool focused{false};
};

#endif // DISPLAYTILE_HPP
