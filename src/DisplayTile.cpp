#include "DisplayTile.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>

static bool collides(const Rect& a, const Rect& b)
{
    return !(a.x + a.width <= b.x || b.x + b.width <= a.x || a.y + a.height <= b.y || b.y + b.height <= a.y);
}

DisplayTile::DisplayTile(Display& root, Point origin, Dimensions dims, std::vector<Rect>& siblings)
    : root(root), origin(origin), dims(dims), siblings(siblings)
{
    Rect r{origin.x, origin.y, dims.width, dims.height};
    auto collide = [&r](const Rect& s) { return collides(r, s); };
    if (std::any_of(siblings.begin(), siblings.end(), collide))
    {
        throw std::runtime_error("Tile collision");
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

DisplayTile DisplayTile::createTile(Point origin, Dimensions dims)
{
    Point abs{this->origin.x + origin.x, this->origin.y + origin.y};
    return DisplayTile(root, abs, dims, children);
}

void DisplayTile::drawBytes(Point pos, const unsigned char* data, std::size_t length)
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
    int available = dims.width - start;
    int remaining = static_cast<int>(length) - offset;
    if (remaining <= 0)
    {
        return;
    }
    length = remaining > available ? available : remaining;
    Point abs{origin.x + start, origin.y + pos.y};
    root.drawBytes(abs, data + offset, length);
}

void DisplayTile::focus()
{
    if (isOnFocus())
    {
        return;
    }
    focused = true;
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
    if (!isOnFocus())
    {
        return;
    }
    focused = false;
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

bool DisplayTile::isOnFocus() const
{
    return focused;
}
