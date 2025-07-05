#include "catch_amalgamated.hpp"
#include "AnalogPin.hpp"
#include "MemoryTracker.hpp"

TEST_CASE("AnalogPin read/write", "[analogpin]") {
    AnalogPin pin(PinMode::Output, 128);
    pin.init();
    REQUIRE(pin.read() == 128);
    int before = allocCount.load();
    pin.write(64);
    REQUIRE(pin.read() == 64);
    REQUIRE(allocCount.load() == before);
}
