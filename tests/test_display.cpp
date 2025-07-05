#include "catch_amalgamated.hpp"
#include "Display.hpp"
#include "MemoryTracker.hpp"

class DummyDisplay : public Display {
public:
    bool initialized = false;
    void init() override { initialized = true; }
};

TEST_CASE("Display initializes", "[display]") {
    DummyDisplay d;
    REQUIRE_FALSE(d.initialized);
    int before = allocCount.load();
    d.init();
    REQUIRE(d.initialized);
    REQUIRE(allocCount.load() == before);
}
