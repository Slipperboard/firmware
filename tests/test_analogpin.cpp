#include "AnalogPin.hpp"
#include "Arduino.h"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("AnalogPin read/write", "[analogpin]")
{
    AnalogPin pin(36, OUTPUT, 128);
    REQUIRE(pin.getPinNumber() == 36);
    REQUIRE(pin.getMode() == OUTPUT);
    REQUIRE(pin.read() == 128);
    int before = allocCount.load();
    static_cast<void>(before);
    pin.write(64);
    REQUIRE(pin.read() == 64);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("AnalogPin write ignored in input mode", "[analogpin]")
{
    AnalogPin pin(34, INPUT);
    REQUIRE(pin.getPinNumber() == 34);
    REQUIRE(pin.getMode() == INPUT);
    pin.write(42);
    REQUIRE(pin.read() == 0);
}

TEST_CASE("AnalogPin dynamic alloc", "[analogpin]")
{
    int before = allocCount.load();
    auto* pin = new AnalogPin(32, OUTPUT);
    delete pin;
    REQUIRE(allocCount.load() == before);
}
