#include "catch_amalgamated.hpp"
#include "Oled096Display.hpp"
#include "MemoryTracker.hpp"

TEST_CASE("Oled096Display initializes", "[oled096display]") {
    Oled096Display d;
    REQUIRE_FALSE(d.isInitialized());
    int before = allocCount.load();
    d.init();
    REQUIRE(d.isInitialized());
    REQUIRE(d.getWidth() == 128);
    REQUIRE(d.getHeight() == 64);
    REQUIRE(d.getLvglDisplay() != nullptr);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Oled096Display draws bytes", "[oled096display]") {
    Oled096Display d;
    d.init();
    uint8_t data[] = {0xAA, 0xBB, 0xCC};
    int before = allocCount.load();
    d.drawBytes(1, 2, data, 3);
    REQUIRE(d.readByte(1, 2) == 0xAA);
    REQUIRE(d.readByte(2, 2) == 0xBB);
    REQUIRE(d.readByte(3, 2) == 0xCC);
    REQUIRE(allocCount.load() == before);
}
