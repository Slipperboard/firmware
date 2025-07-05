#include "catch_amalgamated.hpp"
#include "Switch.hpp"
#include "MemoryTracker.hpp"

class DummySwitch : public Switch {
public:
    bool initialized = false;
    void init() override { initialized = true; }
};

TEST_CASE("Switch initializes", "[switch]") {
    DummySwitch sw;
    REQUIRE_FALSE(sw.initialized);
    int before = allocCount.load();
    sw.init();
    REQUIRE(sw.initialized);
    REQUIRE(allocCount.load() == before);
}
