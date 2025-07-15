#include "MemoryTracker.hpp"
#include "OledDisplay.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("OledDisplay draws bytes", "[oled]")
{
    OledDisplay disp;
    const unsigned char bytes[3] = {1, 2, 3};
    // cppcheck-suppress unreadVariable
    int before = allocCount.load();
    static_cast<void>(before);
    disp.drawBytes({5, 0}, bytes, 3);
    unsigned char read[3];
    disp.readBytes({5, 0}, read, 3);
    REQUIRE(read[0] == 1);
    REQUIRE(read[1] == 2);
    REQUIRE(read[2] == 3);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("OledDisplay draws without explicit init", "[oled]")
{
    OledDisplay disp;
    const unsigned char bytes[1] = {42};
    disp.drawBytes({0, 0}, bytes, 1);
    unsigned char read[1];
    disp.readBytes({0, 0}, read, 1);
    REQUIRE(read[0] == 42);
}

TEST_CASE("OledDisplay reads zero out of bounds", "[oled]")
{
    OledDisplay disp;
    unsigned char bytes[1] = {9};
    disp.drawBytes({0, 0}, bytes, 1);
    unsigned char out[2];
    disp.readBytes({-1, 0}, out, 1);
    disp.readBytes({0, 64}, out + 1, 1);
    REQUIRE(out[0] == 0);
    REQUIRE(out[1] == 0);
}
