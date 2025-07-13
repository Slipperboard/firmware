#include "HcSr04.hpp"
#include <thread>

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
HcSr04::HcSr04(const DigitalPin &trigger, const DigitalPin &echo) : triggerPin(trigger), echoPin(echo)
{
}

void HcSr04::init()
{
    initialized = true;
}

DistanceReading HcSr04::readDistance() const
{
    if (!initialized)
    {
        return {};
    }

    // Trigger the sensor with a 10us pulse
    triggerPin.write(false);
    std::this_thread::sleep_for(std::chrono::microseconds(2));
    triggerPin.write(true);
    std::this_thread::sleep_for(std::chrono::microseconds(10));
    triggerPin.write(false);

    // Wait for echo to go HIGH with a timeout
    auto timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(60);
    while (echoPin.read() == false)
    {
        if (std::chrono::steady_clock::now() > timeout)
            return {};
    }
    auto start = std::chrono::steady_clock::now();

    // Measure how long echo stays HIGH
    while (echoPin.read() == true)
    {
        if (std::chrono::steady_clock::now() > timeout)
            return {};
    }
    auto end = std::chrono::steady_clock::now();

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    float cm = static_cast<float>(microseconds) / 58.0f;
    DistanceReading d{};
    d.centimeters = cm;
    d.meters = cm / 100.0f;
    d.inches = cm / 2.54f;
    return d;
}
