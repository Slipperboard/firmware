#include <string>
#include "MemoryTracker.hpp"
#include "Peripheral.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("Peripheral uuid can be set and retrieved", "[peripheral]")
{
    Peripheral p;
    REQUIRE(p.getUuid().empty());
    p.setUuid("abc-123");
    REQUIRE(p.getUuid() == std::string("abc-123"));
}
