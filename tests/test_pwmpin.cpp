#include "MemoryTracker.hpp"
#include "PWMPin.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("PWMPin read/write", "[pwmpin]")
{
    PWMPin pin(4, PinMode::Output, 10);
    REQUIRE(pin.getPinNumber() == 4);
    REQUIRE(pin.getMode() == PinMode::Output);
    REQUIRE(pin.read() == 10);
    int before = allocCount.load();
    pin.write(20);
    REQUIRE(pin.read() == 20);
    REQUIRE(allocCount.load() == before);
}
