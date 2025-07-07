#include "MemoryTracker.hpp"
#include "Sensor.hpp"
#include "catch_amalgamated.hpp"

class DummySensor : public Sensor
{
    public:
    bool initialized = false;
    void init() override
    {
        initialized = true;
    }
};

TEST_CASE("Sensor initializes", "[sensor]")
{
    DummySensor s;
    REQUIRE_FALSE(s.initialized);
    // cppcheck-suppress unreadVariable
    int before = allocCount.load();
    static_cast<void>(before);
    s.init();
    REQUIRE(s.initialized);
    REQUIRE(allocCount.load() == before);
}
