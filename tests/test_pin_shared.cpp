#include "DigitalPin.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("Pin shared flag", "[pin]")
{
    DigitalPin pin(13, OUTPUT, false); // default not shared
    REQUIRE_FALSE(pin.getIsShared());
    pin.setShared(true);
    REQUIRE(pin.getIsShared());
}
