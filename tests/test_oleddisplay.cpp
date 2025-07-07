#include "MemoryTracker.hpp"
#include "OledDisplay.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("OledDisplay draws bytes", "[oled]")
{
    OledDisplay disp;
    disp.init();
    const unsigned char bytes[3] = {1, 2, 3};
    // cppcheck-suppress unreadVariable
    int before = allocCount.load();
    static_cast<void>(before);
    disp.drawBytes(5, 0, bytes, 3);
    unsigned char read[3];
    disp.readBytes(5, 0, read, 3);
    REQUIRE(read[0] == 1);
    REQUIRE(read[1] == 2);
    REQUIRE(read[2] == 3);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("OledDisplay ignores draws before init", "[oled]")
{
    OledDisplay disp;
    const unsigned char bytes[2] = {1, 2};
    disp.drawBytes(0, 0, bytes, 2);
    unsigned char out[2];
    disp.readBytes(0, 0, out, 2);
    REQUIRE(out[0] == 0);
    REQUIRE(out[1] == 0);
}

TEST_CASE("OledDisplay out-of-bounds reads return zero", "[oled]")
{
    OledDisplay disp;
    disp.init();
    const unsigned char value[1] = {5};
    disp.drawBytes(0, 0, value, 1);
    unsigned char out[2];
    disp.readBytes(-1, 0, out, 2);
    REQUIRE(out[0] == 0);
    REQUIRE(out[1] == 5);
}
