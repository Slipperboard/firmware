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
