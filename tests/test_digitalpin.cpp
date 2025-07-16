#include "DigitalPin.hpp"
#include "Arduino.h"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("DigitalPin read/write", "[digitalpin]")
{
    DigitalPin pin(5, OUTPUT, false);
    REQUIRE(pin.getPinNumber() == 5);
    REQUIRE(pin.getMode() == OUTPUT);
    bool state = pin.read();
    REQUIRE_FALSE(state);
    int before = allocCount.load();
    pin.write(true);
    state = pin.read();
    REQUIRE(state);
    REQUIRE(allocCount.load() == before);
}
