#include "MemoryTracker.hpp"
#include "Module.hpp"
#include "catch_amalgamated.hpp"

class DummyModule : public Module
{
    public:
    bool initialized = false;
    void init() override
    {
        initialized = true;
    }
};

TEST_CASE("Module initializes", "[module]")
{
    DummyModule m;
    REQUIRE_FALSE(m.initialized);
    // cppcheck-suppress unreadVariable
    int before = allocCount.load();
    static_cast<void>(before);
    m.init();
    REQUIRE(m.initialized);
    REQUIRE(allocCount.load() == before);
}
