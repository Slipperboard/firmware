#include "Display.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

class DummyDisplay : public Display
{
    public:
    DummyDisplay() : Display(10, 10)
    {
    }
    bool initialized = false;
    void init() override
    {
        initialized = true;
    }
    void drawBytes(int, int, const unsigned char *, std::size_t) override
    {
        // called in tests to exercise virtual method
    }
};

TEST_CASE("Display initializes", "[display]")
{
    DummyDisplay d;
    REQUIRE_FALSE(d.initialized);
    int before = allocCount.load();
    d.init();
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
    // call drawBytes to hit coverage for override
    const unsigned char data[1] = {0};
    d.drawBytes(0, 0, data, 1);
}

TEST_CASE("Circular display reports radius", "[display]")
{
    class CircleDisplay : public Display
    {
        public:
        CircleDisplay() : Display(5) {}
        void init() override {}
        void drawBytes(int, int, const unsigned char *, std::size_t) override {}
    };

    CircleDisplay c;
    c.init();
    const unsigned char b[1] = {0};
    c.drawBytes(0, 0, b, 1);
    REQUIRE(c.isCircular());
    REQUIRE(c.getRadius() == 5);
}
