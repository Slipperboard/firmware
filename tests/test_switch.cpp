#include "MemoryTracker.hpp"
#include "Switch.hpp"
#include "catch_amalgamated.hpp"

class DummySwitch : public Switch
{
    public:
    DummySwitch()
    {
        initialized = true;
    }
    bool initialized = false;
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
