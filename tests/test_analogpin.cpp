#include "AnalogPin.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("AnalogPin read/write", "[analogpin]")
{
    AnalogPin pin(PinMode::Output, 128);
    pin.init();
    REQUIRE(pin.read() == 128);
    int before = allocCount.load();
    static_cast<void>(before);
    pin.write(64);
    REQUIRE(pin.read() == 64);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("AnalogPin reports mode", "[analogpin]")
{
    AnalogPin pin(PinMode::Input, 0);
    REQUIRE(pin.getMode() == PinMode::Input);
    // write should have no effect in Input mode
    pin.write(10);
    REQUIRE(pin.read() == 0);
}
