#include "DisplayTile.hpp"

static bool collides(const Rect& a, const Rect& b)
{
    return !(a.x + a.width <= b.x || b.x + b.width <= a.x ||
             a.y + a.height <= b.y || b.y + b.height <= a.y);
}

DisplayTile::DisplayTile(Display& rootDisplay, Point orig, Dimensions d,
                         std::vector<Rect>& sib)
    : root(rootDisplay), origin(orig), dims(d), siblings(sib)
{
    Rect r{origin.x, origin.y, dims.width, dims.height};
    for (const auto& s : siblings)
    {
        if (collides(r, s))
        {
            throw std::runtime_error("Tile collision");
        }
    }
    siblings.push_back(r);
}

int DisplayTile::getWidth() const
{
    return dims.width;
}
int DisplayTile::getHeight() const
{
    return dims.height;
}

DisplayTile DisplayTile::createTile(Point orig, Dimensions d)
{
    Point abs{origin.x + orig.x, origin.y + orig.y};
    return DisplayTile(root, abs, d, children);
}

void DisplayTile::drawBytes(Point pos, const unsigned char* data,
                            std::size_t length)
{
    if (pos.y < 0 || pos.y >= dims.height)
    {
        return;
    }
    int start = pos.x;
    int offset = 0;
    if (start < 0)
    {
        offset = -start;
        start = 0;
    }
    if (start >= dims.width)
    {
        return;
    }
    if (static_cast<int>(length) - offset > dims.width - start)
    {
        length = dims.width - start;
    }
    Point abs{origin.x + start, origin.y + pos.y};
    root.drawBytes(abs, data + offset, length);
}

void DisplayTile::focus()
{
    unsigned char dot = '.';
    for (int x = 0; x < dims.width; ++x)
    {
        drawBytes({x, 0}, &dot, 1);
        if (dims.height > 1)
        {
            drawBytes({x, dims.height - 1}, &dot, 1);
        }
    }
    for (int y = 1; y < dims.height - 1; ++y)
    {
        drawBytes({0, y}, &dot, 1);
        if (dims.width > 1)
        {
            drawBytes({dims.width - 1, y}, &dot, 1);
        }
    }
}

void DisplayTile::unfocus()
{
    unsigned char space = ' ';
    for (int x = 0; x < dims.width; ++x)
    {
        drawBytes({x, 0}, &space, 1);
        if (dims.height > 1)
        {
            drawBytes({x, dims.height - 1}, &space, 1);
        }
    }
    for (int y = 1; y < dims.height - 1; ++y)
    {
        drawBytes({0, y}, &space, 1);
        if (dims.width > 1)
        {
            drawBytes({dims.width - 1, y}, &space, 1);
        }
    }
}

