#include "AnalogPin.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("AnalogPin read/write", "[analogpin]")
{
    AnalogPin pin(36, PinMode::Output, 128);
    pin.init();
    REQUIRE(pin.getPinNumber() == 36);
    REQUIRE(pin.getMode() == PinMode::Output);
    REQUIRE(pin.read() == 128);
    int before = allocCount.load();
    static_cast<void>(before);
    pin.write(64);
    REQUIRE(pin.read() == 64);
    REQUIRE(allocCount.load() == before);
}
