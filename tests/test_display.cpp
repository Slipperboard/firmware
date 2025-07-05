#include "catch_amalgamated.hpp"
#include "Display.hpp"
#include "MemoryTracker.hpp"

class DummyDisplay : public Display {
public:
    DummyDisplay() : Display(10, 10) {}
    void init() override { initialized = true; }
    bool isInitialized() const override { return initialized; }

private:
    bool initialized = false;
};

TEST_CASE("Display initializes", "[display]") {
    DummyDisplay d;
    REQUIRE_FALSE(d.isInitialized());
    int before = allocCount.load();
    d.init();
    REQUIRE(d.isInitialized());
    REQUIRE(d.getWidth() == 10);
    REQUIRE(d.getHeight() == 10);
    REQUIRE(allocCount.load() == before);
}
