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

TEST_CASE("AnalogPin constructor sets hardware pin mode", "[analogpin]")
{
    pinModes[31] = -1;
    AnalogPin pin(31, OUTPUT);
    REQUIRE(pinModes[31] == OUTPUT);
    pinModes[30] = -1;
    AnalogPin inputPin(30, INPUT);
    REQUIRE(pinModes[30] == INPUT);
}

TEST_CASE("AnalogPin shared flag", "[analogpin]")
{
    AnalogPin sharedPin(22, OUTPUT, 0, true);
    REQUIRE(sharedPin.isShared());
    AnalogPin exclusivePin(23, OUTPUT);
    REQUIRE_FALSE(exclusivePin.isShared());
}
