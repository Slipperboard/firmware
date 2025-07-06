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
    int before = allocCount.load();
    s.init();
    REQUIRE(s.initialized);
    REQUIRE(allocCount.load() == before);
}
