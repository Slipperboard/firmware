#include "MemoryTracker.hpp"
#include "Module.hpp"
#include "catch_amalgamated.hpp"

class DummyModule : public Module
{
    public:
    bool initialized = false;
    DummyModule() { initialized = true; }
};

TEST_CASE("Module initializes", "[module]")
{
    DummyModule m;
    REQUIRE(m.initialized);
    // cppcheck-suppress unreadVariable
    int before = allocCount.load();
    static_cast<void>(before);
    REQUIRE(allocCount.load() == before);
}
