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
    int before = allocCount.load();
    m.init();
    REQUIRE(m.initialized);
    REQUIRE(allocCount.load() == before);
}
