#include "MemoryTracker.hpp"
#include "OledDisplay.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("OledDisplay draws bytes", "[oled]")
{
    OledDisplay disp;
    disp.init();
    unsigned char bytes[3] = {1, 2, 3};
    int before = allocCount.load();
    disp.drawBytes(5, 0, bytes, 3);
    unsigned char read[3];
    disp.readBytes(5, 0, read, 3);
    REQUIRE(read[0] == 1);
    REQUIRE(read[1] == 2);
    REQUIRE(read[2] == 3);
    REQUIRE(allocCount.load() == before);
}
