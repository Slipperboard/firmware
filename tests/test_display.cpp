#include "Display.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

class DummyDisplay : public Display
{
    public:
    DummyDisplay() : Display({10, 10})
    {
        initialized = true;
    }
    bool initialized = false;
    void drawBytes(Point pos, const unsigned char* data, std::size_t length) override
    {
        Display::drawBytes(pos, data, length);
    }
};

TEST_CASE("Display initializes", "[display]")
{
    DummyDisplay d;
    REQUIRE(d.initialized);
    int before = allocCount.load();
    // call the virtual function to ensure coverage
    d.drawBytes({0, 0}, nullptr, 0);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Display drawBytes default", "[display]")
{
    DummyDisplay d;
    unsigned char msg[] = "test";
    int before = allocCount.load();
    d.drawBytes({0, 0}, msg, sizeof(msg) - 1);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Display stores dimensions", "[display]")
{
    DummyDisplay d;
    REQUIRE(d.getWidth() == 10);
    REQUIRE(d.getHeight() == 10);
}

class StateDisplay : public Display
{
    public:
    StateDisplay() : Display({4, 2})
    {
    }
    void drawBytes(Point pos, const unsigned char* data, std::size_t length) override
    {
        Display::drawBytes(pos, data, length);
    }
    const auto& state() const
    {
        return buffer;
    }
};

TEST_CASE("pushState and popState restore buffer", "[display]")
{
    StateDisplay d;
    unsigned char msg1[] = "abcd";
    d.drawBytes({0, 0}, msg1, 4);
    d.pushState();
    unsigned char msg2[] = "wxyz";
    d.drawBytes({0, 0}, msg2, 4);
    REQUIRE(d.state()[0][0] == 'w');
    d.popState();
    REQUIRE(d.state()[0][0] == 'a');
}

TEST_CASE("clear fills display with spaces", "[display]")
{
    StateDisplay d;
    unsigned char msg[] = "abcd";
    d.drawBytes({0, 0}, msg, 4);
    d.clear();
    for (int y = 0; y < d.getHeight(); ++y)
    {
        for (int x = 0; x < d.getWidth(); ++x)
        {
            REQUIRE(d.state()[y][x] == ' ');
        }
    }
}

TEST_CASE("popState throws if no state saved", "[display]")
{
    StateDisplay d;
    REQUIRE_THROWS_AS(d.popState(), std::runtime_error);
}
