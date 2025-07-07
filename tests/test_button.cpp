#include "Button.hpp"
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"
#include <chrono>
#include <thread>

class DummyButton : public Button
{
    public:
    bool initialized = false;
    void init() override
    {
        initialized = true;
    }
};

TEST_CASE("Button initializes", "[button]")
{
    DummyButton b;
    REQUIRE_FALSE(b.initialized);
    int before = allocCount.load();
    static_cast<void>(before);
    b.init();
    REQUIRE(b.initialized);
    REQUIRE(allocCount.load() == before);
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
