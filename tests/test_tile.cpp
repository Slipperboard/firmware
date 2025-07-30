#include "MemoryTracker.hpp"
#include "Tile.hpp"
#include "catch_amalgamated.hpp"

// Unit tests for the Tile class

class LoggingDisplay : public Display
{
    public:
    LoggingDisplay() : Display({20, 20})
    {
    }
    Point lastPos{};
    std::size_t lastLen{0};
    int calls{0};
    unsigned char lastBuf[32]{};
    void drawBytes(Point pos, const unsigned char* data, std::size_t length) override
    {
        Display::drawBytes(pos, data, length);
        lastPos = pos;
        lastLen = length;
        for (std::size_t i = 0; i < length && i < sizeof(lastBuf); ++i)
        {
            lastBuf[i] = data[i];
        }
        ++calls;
    }
    const auto& state() const
    {
        return buffer;
    }
    int stackDepth() const
    {
        return static_cast<int>(stack.size());
    }
};

TEST_CASE("Tile dimensions", "[tile]")
{
    LoggingDisplay d;
    Tile t = d.createTile({0, 0}, {5, 5});
    REQUIRE(t.getWidth() == 5);
    REQUIRE(t.getHeight() == 5);
}

TEST_CASE("Display prevents overlapping tiles", "[tile]")
{
    LoggingDisplay d;
    static_cast<void>(d.createTile({0, 0}, {5, 5}));
    REQUIRE_THROWS_AS(d.createTile({3, 0}, {5, 5}), std::runtime_error);
}

TEST_CASE("Nested tile collision throws", "[tile]")
{
    LoggingDisplay d;
    Tile rootTile = d.createTile({0, 0}, {8, 8});
    static_cast<void>(rootTile.createTile({0, 0}, {4, 4}));
    REQUIRE_THROWS_AS(rootTile.createTile({2, 2}, {4, 4}), std::runtime_error);
}

TEST_CASE("Nested tiles are allowed", "[tile]")
{
    LoggingDisplay d;
    Tile t = d.createTile({0, 0}, {10, 10});
    Tile inner = t.createTile({2, 2}, {3, 3});
    REQUIRE(inner.getWidth() == 3);
    REQUIRE(inner.getHeight() == 3);
}

TEST_CASE("Nested tile must fit within parent bounds", "[tile]")
{
    LoggingDisplay d;
    Tile t = d.createTile({5, 5}, {4, 4});
    REQUIRE_THROWS_AS(t.createTile({3, 0}, {2, 2}), std::runtime_error);
    REQUIRE_THROWS_AS(t.createTile({0, 3}, {2, 2}), std::runtime_error);
    REQUIRE_THROWS_AS(t.createTile({-1, 0}, {2, 2}), std::runtime_error);
    REQUIRE_THROWS_AS(t.createTile({0, 0}, {5, 5}), std::runtime_error);
    Tile ok = t.createTile({1, 1}, {2, 2});
    REQUIRE(ok.getWidth() == 2);
}

TEST_CASE("drawBytes is clipped to tile bounds", "[tile]")
{
    LoggingDisplay d;
    Tile t = d.createTile({2, 2}, {5, 5});
    unsigned char msg[] = "hello";
    t.drawBytes({-1, 0}, msg, 5);
    REQUIRE(d.calls == 1);
    REQUIRE(d.lastPos.x == 2);
    REQUIRE(d.lastPos.y == 2);
    REQUIRE(d.lastLen == 4);
    REQUIRE(d.lastBuf[0] == 'e');
    t.drawBytes({4, 0}, msg, 2);
    REQUIRE(d.calls == 2);
    REQUIRE(d.lastLen == 1);
    t.drawBytes({5, 0}, msg, 1);
    REQUIRE(d.calls == 2); // start beyond width, ignored
    t.drawBytes({-5, 0}, msg, 2);
    REQUIRE(d.calls == 2); // offset exceeds length, ignored
    t.drawBytes({0, 0}, msg, 0);
    REQUIRE(d.calls == 2); // zero length ignored
    t.drawBytes({0, 5}, msg, 1);
    REQUIRE(d.calls == 2);
}

static int expected_focus_calls(int w, int h)
{
    int calls = w;
    if (h > 1)
    {
        calls += w;
    }
    for (int y = 1; y < h - 1; ++y)
    {
        calls += 1;
        if (w > 1)
        {
            calls += 1;
        }
    }
    return calls;
}

TEST_CASE("focus and unfocus draw border", "[tile]")
{
    LoggingDisplay d;
    Tile t = d.createTile({0, 0}, {3, 3});
    int before = d.calls;
    t.focus();
    int expected = expected_focus_calls(3, 3);
    REQUIRE(d.calls - before == expected);
    before = d.calls;
    t.unfocus();
    REQUIRE(d.calls - before == expected);
}

TEST_CASE("isOnFocus controls border drawing", "[tile]")
{
    LoggingDisplay d;
    Tile t = d.createTile({0, 0}, {4, 2});
    REQUIRE_FALSE(t.isOnFocus());
    int before = d.calls;
    t.focus();
    int expected = expected_focus_calls(4, 2);
    REQUIRE(d.calls - before == expected);
    REQUIRE(t.isOnFocus());
    before = d.calls;
    t.focus();
    REQUIRE(d.calls == before); // no redraw when already focused
    t.unfocus();
    REQUIRE_FALSE(t.isOnFocus());
    before = d.calls;
    t.unfocus();
    REQUIRE(d.calls == before); // no redraw when already unfocused
}

TEST_CASE("Tile clear fills region", "[tile]")
{
    LoggingDisplay d;
    Tile t = d.createTile({1, 1}, {3, 1});
    unsigned char msg[] = "abc";
    t.drawBytes({0, 0}, msg, 3);
    t.clear();
    const auto& state = d.state();
    for (int x = 1; x < 4; ++x)
    {
        REQUIRE(state[1][x] == ' ');
    }
}

TEST_CASE("pushState and popState delegate to root display", "[tile]")
{
    LoggingDisplay d;
    Tile t = d.createTile({0, 0}, {4, 1});
    unsigned char msg1[] = "1234";
    t.drawBytes({0, 0}, msg1, 4);
    REQUIRE(d.stackDepth() == 0);
    t.pushState();
    REQUIRE(d.stackDepth() == 1);
    unsigned char msg2[] = "abcd";
    t.drawBytes({0, 0}, msg2, 4);
    REQUIRE(d.state()[0][0] == 'a');
    t.popState();
    REQUIRE(d.stackDepth() == 0);
    REQUIRE(d.state()[0][0] == '1');
}
