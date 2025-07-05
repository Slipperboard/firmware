#include "catch_amalgamated.hpp"
#include "DigitalPin.hpp"
#include "MemoryTracker.hpp"

TEST_CASE("DigitalPin read/write", "[digitalpin]") {
    DigitalPin pin(PinMode::Output, 0);
    pin.init();
    REQUIRE(pin.digitalRead() == false);
    int before = allocCount.load();
    pin.digitalWrite(1);
    REQUIRE(pin.digitalRead() == true);
    REQUIRE(allocCount.load() == before);
}
