#include "DigitalPin.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("DigitalPin read/write", "[digitalpin]")
{
    DigitalPin pin(PinMode::Output, false);
    pin.init();
    bool state = pin.read();
    REQUIRE_FALSE(state);
    int before = allocCount.load();
    pin.write(true);
    state = pin.read();
    REQUIRE(state);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("DigitalPin reports mode", "[digitalpin]")
{
    DigitalPin pin(PinMode::Input, true);
    REQUIRE(pin.getMode() == PinMode::Input);
    // write should not change value in Input mode
    pin.write(false);
    REQUIRE(pin.read() == true);
}
