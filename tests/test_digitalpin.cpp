#include "Arduino.h"
#include "DigitalPin.hpp"
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

TEST_CASE("DigitalPin digitalWrite", "[digitalpin]")
{
    DigitalPin pin(6, OUTPUT);
    pin.digitalWrite(true);
    REQUIRE(pin.read());
    pin.digitalWrite(false);
    REQUIRE_FALSE(pin.read());
}
