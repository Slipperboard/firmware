#ifndef DISPLAY_HPP
#define DISPLAY_HPP

/**
 * @file Display.hpp
 * @brief Base class for graphical display devices.
 * @author Fadi Hanna Al-Kass <fadi.h.alkass@gmail.com>
 */

#include <cstddef>
#include <stdexcept>
#include <vector>
#include "Peripheral.hpp"

struct Rect;
class Tile;

struct Dimensions
{
    int width;
    int height;
};

struct Point
{
    int x;
    int y;
};

class Display : public Peripheral
{
    public:
    /**
     * @brief Construct a rectangular display.
     *
     * @param dims Physical dimensions of the display in characters.
     */
    explicit Display(Dimensions dims);

    /** Destructor. */
    ~Display() override;

    /** Save the current display buffer to an internal stack. */
    void pushState();

    /** Restore the most recently saved buffer and redraw the screen. */
    void popState();

    /** Clear the display and reset the internal buffer. */
    void clear();

    /** @return Display width in characters. */
    int getWidth() const;

    /** @return Display height in characters. */
    int getHeight() const;

    /**
     * @brief Draw a sequence of bytes on the display.
     *
     * @param pos   Top-left coordinate of the data.
     * @param data  Byte array to draw.
     * @param length Number of bytes to write.
     */
    virtual void drawBytes(Point pos, const unsigned char* data, std::size_t length) = 0;

    /**
     * @brief Create a sub-region (tile) of the display.
     *
     * @param origin Top-left coordinate of the tile.
     * @param dims   Dimensions of the tile.
     * @return A new Tile managing the region.
     */
    Tile createTile(Point origin, Dimensions dims);

    protected:
    int width;
    int height;
    std::vector<Rect> tiles;
    std::vector<std::vector<unsigned char>> buffer;
    std::vector<std::vector<std::vector<unsigned char>>> stack;
};

#endif // DISPLAY_HPP
