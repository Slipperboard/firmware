#include "Display.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

class DummyDisplay : public Display
{
    public:
    DummyDisplay() : Display(10, 10)
    {
    }
    explicit DummyDisplay(int radius) : Display(radius)
    {
    }
    bool initialized = false;
    void init() override
    {
        initialized = true;
    }
    void drawBytes(int, int, const unsigned char *, std::size_t) override
    {
    }
};

TEST_CASE("Display initializes", "[display]")
{
    DummyDisplay d;
    REQUIRE_FALSE(d.initialized);
    int before = allocCount.load();
    d.init();
    // call the virtual function to ensure coverage
    d.drawBytes(0, 0, nullptr, 0);
    REQUIRE(d.initialized);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Display stores dimensions", "[display]")
{
    DummyDisplay d;
    REQUIRE(d.getWidth() == 10);
    REQUIRE(d.getHeight() == 10);
    bool circ = d.isCircular();
    REQUIRE_FALSE(circ);
}

TEST_CASE("Circular display stores radius", "[display]")
{
    DummyDisplay d(5);
    REQUIRE(d.isCircular());
    REQUIRE(d.getRadius() == 5);
    REQUIRE(d.getWidth() == 0);
    REQUIRE(d.getHeight() == 0);
}
