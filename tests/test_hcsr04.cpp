#include "DigitalPin.hpp"
#include "HcSr04.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"
#include <thread>

TEST_CASE("HcSr04 measures pulse duration", "[hcsr04]")
{
    DigitalPin trig(5, PinMode::Output, false);
    DigitalPin echo(18, PinMode::Input, false);
    HcSr04 sensor(trig, echo);
    sensor.init();

    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::microseconds(50));
        echo.write(true);
        std::this_thread::sleep_for(std::chrono::microseconds(5800));
        echo.write(false);
    });

    int before = allocCount.load();
    auto dist = sensor.readDistance();
    t.join();
    REQUIRE(dist.centimeters == Approx(100.0f).margin(5.0f));
    REQUIRE(dist.meters == Approx(1.0f).margin(0.05f));
    REQUIRE(dist.inches == Approx(39.3701f).margin(0.2f));
    REQUIRE(allocCount.load() == before);
}
