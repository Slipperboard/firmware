#include "MemoryTracker.hpp"
#include "Switch.hpp"
#include "catch_amalgamated.hpp"

class DummySwitch : public Switch
{
    public:
    bool initialized = false;
    void init() override
    {
        initialized = true;
    }
};

TEST_CASE("Switch initializes", "[switch]")
{
    DummySwitch sw;
    REQUIRE_FALSE(sw.initialized);
    // cppcheck-suppress unreadVariable
    int before = allocCount.load();
    static_cast<void>(before);
    sw.init();
    REQUIRE(sw.initialized);
    REQUIRE(allocCount.load() == before);
}
