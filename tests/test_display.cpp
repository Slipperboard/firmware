#include "Display.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

class DummyDisplay : public Display
{
    public:
    DummyDisplay() : Display({10, 10}) { initialized = true; }
    bool initialized = false;
    void drawBytes(Point, const unsigned char*, std::size_t) override {}
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

TEST_CASE("Display stores dimensions", "[display]")
{
    DummyDisplay d;
    REQUIRE(d.getWidth() == 10);
    REQUIRE(d.getHeight() == 10);
}
