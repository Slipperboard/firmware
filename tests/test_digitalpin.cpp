#include "catch_amalgamated.hpp"
#include "DigitalPin.hpp"
#include "MemoryTracker.hpp"

TEST_CASE("DigitalPin read/write", "[digitalpin]") {
    DigitalPin pin(PinMode::Output, false);
    pin.init();
    REQUIRE(pin.read() == false);
    int before = allocCount.load();
    pin.write(true);
    REQUIRE(pin.read() == true);
    REQUIRE(allocCount.load() == before);
}
