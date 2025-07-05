#include "catch_amalgamated.hpp"
#include "Button.hpp"
#include "MemoryTracker.hpp"

class DummyButton : public Button {
public:
    bool initialized = false;
    void init() override { initialized = true; }
};

TEST_CASE("Button initializes", "[button]") {
    DummyButton b;
    REQUIRE_FALSE(b.initialized);
    int before = allocCount.load();
    b.init();
    REQUIRE(b.initialized);
    REQUIRE(allocCount.load() == before);
}
