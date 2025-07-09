#include "catch_amalgamated.hpp"
extern "C" {
#include "freertos/FreeRTOS.h"
}

TEST_CASE("FreeRTOS stub delay", "[simulator]")
{
    REQUIRE_NOTHROW(vTaskDelay(1));
}
