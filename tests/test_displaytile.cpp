#include "DisplayTile.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

class LoggingDisplay : public Display
{
    public:
    LoggingDisplay() : Display({20, 20}) {}
    Point lastPos{};
    std::size_t lastLen{0};
    int calls{0};
    unsigned char lastBuf[32]{};
    void drawBytes(Point pos, const unsigned char* data, std::size_t length) override
    {
        lastPos = pos;
        lastLen = length;
        for (std::size_t i = 0; i < length && i < sizeof(lastBuf); ++i)
        {
            lastBuf[i] = data[i];
        }
        ++calls;
    }
};

TEST_CASE("DisplayTile dimensions", "[displaytile]")
{
    LoggingDisplay d;
    DisplayTile t = d.createTile({0, 0}, {5, 5});
    REQUIRE(t.getWidth() == 5);
    REQUIRE(t.getHeight() == 5);
}

TEST_CASE("Display prevents overlapping tiles", "[displaytile]")
{
    LoggingDisplay d;
    static_cast<void>(d.createTile({0, 0}, {5, 5}));
    REQUIRE_THROWS_AS(d.createTile({3, 0}, {5, 5}), std::runtime_error);
}

TEST_CASE("Nested tiles are allowed", "[displaytile]")
{
    LoggingDisplay d;
    DisplayTile t = d.createTile({0, 0}, {10, 10});
    DisplayTile inner = t.createTile({2, 2}, {3, 3});
    REQUIRE(inner.getWidth() == 3);
    REQUIRE(inner.getHeight() == 3);
}

TEST_CASE("drawBytes is clipped to tile bounds", "[displaytile]")
{
    LoggingDisplay d;
    DisplayTile t = d.createTile({2, 2}, {5, 5});
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

TEST_CASE("focus and unfocus draw border", "[displaytile]")
{
    LoggingDisplay d;
    DisplayTile t = d.createTile({0, 0}, {3, 3});
    int before = d.calls;
    t.focus();
    int expected = expected_focus_calls(3, 3);
    REQUIRE(d.calls - before == expected);
    before = d.calls;
    t.unfocus();
    REQUIRE(d.calls - before == expected);
}

