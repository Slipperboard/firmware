#include <chrono>
#include <thread>
#include "Button.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

class DummyButton : public Button
{
    public:
    DummyButton()
    {
        initialized = true;
    }
    bool initialized = false;
};

TEST_CASE("Button initializes", "[button]")
{
    DummyButton b;
    REQUIRE(b.initialized);
    int before = allocCount.load();
    static_cast<void>(before);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Button returns configured threshold", "[button]")
{
    DummyButton b;
    b.setClickThreshold(std::chrono::milliseconds(42));
    REQUIRE(b.getClickThreshold() == std::chrono::milliseconds(42));
}

TEST_CASE("Click duration threshold is configurable", "[button]")
{
    DummyButton b;
    b.setClickThreshold(std::chrono::milliseconds(30));
    b.press();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    int before = allocCount.load();
    static_cast<void>(before);
    // cppcheck-suppress comparisonOfFuncReturningBoolError
    REQUIRE(b.release());
    REQUIRE(allocCount.load() == before);

    b.setClickThreshold(std::chrono::milliseconds(10));
    b.press();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    before = allocCount.load();
    static_cast<void>(before);
    // cppcheck-suppress comparisonOfFuncReturningBoolError
    REQUIRE_FALSE(b.release());
    REQUIRE(allocCount.load() == before);
}
