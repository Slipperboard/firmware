#include "catch_amalgamated.hpp"
#include "AnalogPin.hpp"
#include "MemoryTracker.hpp"

TEST_CASE("AnalogPin read/write", "[analogpin]") {
    AnalogPin pin(PinMode::Output, 128);
    pin.init();
    REQUIRE(pin.analogRead() == 128);
    int before = allocCount.load();
    pin.analogWrite(64);
    REQUIRE(pin.analogRead() == 64);
    REQUIRE(allocCount.load() == before);
}
