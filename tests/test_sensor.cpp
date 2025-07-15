#include "MemoryTracker.hpp"
#include "Sensor.hpp"
#include "catch_amalgamated.hpp"

class DummySensor : public Sensor
{
    public:
    bool initialized = false;
    DummySensor() { initialized = true; }
};

TEST_CASE("Sensor initializes", "[sensor]")
{
    DummySensor s;
    REQUIRE(s.initialized);
    // cppcheck-suppress unreadVariable
    int before = allocCount.load();
    static_cast<void>(before);
    REQUIRE(allocCount.load() == before);
}
