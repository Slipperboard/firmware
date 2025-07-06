#include "catch_amalgamated.hpp"
#include "OledDisplay.hpp"
#include "MemoryTracker.hpp"

TEST_CASE("OledDisplay draws bytes", "[oled]") {
    OledDisplay disp;
    disp.init();
    unsigned char bytes[3] = {1, 2, 3};
    int before = allocCount.load();
    disp.drawBytes(5, 0, bytes, 3);
    REQUIRE(disp.getPixel(5, 0) == 1);
    REQUIRE(disp.getPixel(6, 0) == 2);
    REQUIRE(disp.getPixel(7, 0) == 3);
    REQUIRE(allocCount.load() == before);
}
