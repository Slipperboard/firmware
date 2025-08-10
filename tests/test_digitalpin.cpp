#include <Arduino.h>
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

TEST_CASE("DigitalPin write", "[digitalpin]")
{
    DigitalPin pin(6, OUTPUT);
    pin.write(true);
    REQUIRE(pin.read());
    pin.write(false);
    REQUIRE_FALSE(pin.read());
}

TEST_CASE("DigitalPin read respects mode", "[digitalpin]")
{
    digitalPinStates[7] = HIGH;
    DigitalPin inputPin(7, INPUT);
    REQUIRE(inputPin.read());

    digitalPinStates[8] = HIGH;
    DigitalPin outputPin(8, OUTPUT, false);
    REQUIRE_FALSE(outputPin.read());
}

TEST_CASE("DigitalPin constructor sets hardware pin mode", "[digitalpin]")
{
    pinModes[9] = -1;
    DigitalPin pin(9, OUTPUT);
    REQUIRE(pinModes[9] == OUTPUT);
    pinModes[10] = -1;
    DigitalPin inputPin(10, INPUT);
    REQUIRE(pinModes[10] == INPUT);
}

TEST_CASE("DigitalPin shared flag", "[digitalpin]")
{
    DigitalPin sharedPin(20, OUTPUT, false, true);
    REQUIRE(sharedPin.isShared());
    DigitalPin exclusivePin(21, OUTPUT);
    REQUIRE_FALSE(exclusivePin.isShared());
}

TEST_CASE("DigitalPin dynamic alloc", "[digitalpin]")
{
    int before = allocCount.load();
    auto* pin = new DigitalPin(22, OUTPUT);
    delete pin; // This should trigger the destructor for coverage
    REQUIRE(allocCount.load() == before);
}
