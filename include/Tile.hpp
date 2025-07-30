#ifndef TILE_HPP
#define TILE_HPP

/**
 * @file Tile.hpp
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

class Tile
{
    public:
    /**
     * @brief Create a tile inside an existing display.
     *
     * @param root     Root display that owns the tile.
     * @param origin   Top-left coordinate of the tile.
     * @param dims     Dimensions of the tile.
     * @param siblings Container tracking sibling rectangles for collision detection.
     */
    Tile(Display& root, Point origin, Dimensions dims, std::vector<Rect>& siblings);

    /** @return Width of the tile in characters. */
    int getWidth() const;

    /** @return Height of the tile in characters. */
    int getHeight() const;

    /**
     * @brief Create a child tile relative to this tile.
     *
     * @param origin Relative coordinate within this tile.
     * @param dims   Dimensions of the new tile.
     * @return A new Tile instance.
     */
    Tile createTile(Point origin, Dimensions dims);

    /**
     * @brief Draw bytes relative to the tile origin.
     *
     * @param pos    Tile-relative coordinate.
     * @param data   Bytes to draw.
     * @param length Number of bytes to draw.
     */
    void drawBytes(Point pos, const unsigned char* data, std::size_t length);

    /** Proxy to Display::pushState for this tile's root display. */
    void pushState();

    /** Proxy to Display::popState for this tile's root display. */
    void popState();

    /** Clear the contents of the tile region. */
    void clear();

    /** Show a focus rectangle around the tile. */
    void focus();

    /** Remove the focus rectangle from the tile. */
    void unfocus();

    /** @return true if the tile currently has focus. */
    bool isOnFocus() const;

    private:
    Display& root;
    Point origin;
    Dimensions dims;
    std::vector<Rect>& siblings;
    std::vector<Rect> children;
    bool focused{false};
};

#endif // TILE_HPP
