#include <Arduino.h>
#include "MemoryTracker.hpp"
#include "PWMPin.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("PWMPin read/write", "[pwmpin]")
{
    PWMPin pin(4, OUTPUT, 10);
    REQUIRE(pin.getPinNumber() == 4);
    REQUIRE(pin.getMode() == OUTPUT);
    REQUIRE(pin.read() == 10);
    int before = allocCount.load();
    pin.write(20);
    REQUIRE(pin.read() == 20);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("PWMPin constructor sets hardware pin mode", "[pwmpin]")
{
    pinModes[11] = -1;
    PWMPin pin(11, OUTPUT);
    REQUIRE(pinModes[11] == OUTPUT);
    pinModes[12] = -1;
    PWMPin inputPin(12, INPUT);
    REQUIRE(pinModes[12] == INPUT);
}
