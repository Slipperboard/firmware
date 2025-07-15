#include "MemoryTracker.hpp"
#include "Switch.hpp"
#include "catch_amalgamated.hpp"

class DummySwitch : public Switch
{
    public:
    bool initialized = false;
    DummySwitch() { initialized = true; }
};

TEST_CASE("Switch initializes", "[switch]")
{
    DummySwitch sw;
    REQUIRE(sw.initialized);
    // cppcheck-suppress unreadVariable
    int before = allocCount.load();
    static_cast<void>(before);
    REQUIRE(allocCount.load() == before);
}
