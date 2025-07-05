#include "catch_amalgamated.hpp"
#include "DigitalPin.hpp"
#include "MemoryTracker.hpp"

TEST_CASE("DigitalPin read/write", "[digitalpin]") {
    DigitalPin pin(PinMode::Output, false);
    pin.init();
    REQUIRE(pin.digitalRead() == false);
    int before = allocCount.load();
    pin.digitalWrite(true);
    REQUIRE(pin.digitalRead() == true);
    REQUIRE(allocCount.load() == before);
}
