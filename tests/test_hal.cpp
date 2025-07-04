#include "catch_amalgamated.hpp"
#include <atomic>
#include <cstdlib>

// Simple allocation counter to ensure init() does not allocate memory
static std::atomic<int> allocCount{0};

void* operator new(std::size_t size) {
    allocCount.fetch_add(1, std::memory_order_relaxed);
    return std::malloc(size);
}

void operator delete(void* ptr) noexcept {
    allocCount.fetch_sub(1, std::memory_order_relaxed);
    std::free(ptr);
}

void* operator new[](std::size_t size) {
    allocCount.fetch_add(1, std::memory_order_relaxed);
    return std::malloc(size);
}

void operator delete[](void* ptr) noexcept {
    allocCount.fetch_sub(1, std::memory_order_relaxed);
    std::free(ptr);
}
#include "HAL.hpp"

class DummyModule : public Module {
public:
    bool initialized = false;
    void init() override { initialized = true; }
};

class DummySensor : public Sensor {
public:
    bool initialized = false;
    void init() override { initialized = true; }
};

class DummySwitch : public Switch {
public:
    bool initialized = false;
    void init() override { initialized = true; }
};

class DummyButton : public Button {
public:
    bool initialized = false;
    void init() override { initialized = true; }
};

class DummyDisplay : public Display {
public:
    bool initialized = false;
    void init() override { initialized = true; }
};

TEST_CASE("Module initializes", "[module]") {
    DummyModule m;
    REQUIRE_FALSE(m.initialized);
    int before = allocCount.load();
    m.init();
    REQUIRE(m.initialized);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Sensor initializes", "[sensor]") {
    DummySensor s;
    REQUIRE_FALSE(s.initialized);
    int before = allocCount.load();
    s.init();
    REQUIRE(s.initialized);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Switch initializes", "[switch]") {
    DummySwitch sw;
    REQUIRE_FALSE(sw.initialized);
    int before = allocCount.load();
    sw.init();
    REQUIRE(sw.initialized);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Button initializes", "[button]") {
    DummyButton b;
    REQUIRE_FALSE(b.initialized);
    int before = allocCount.load();
    b.init();
    REQUIRE(b.initialized);
    REQUIRE(allocCount.load() == before);
}

TEST_CASE("Display initializes", "[display]") {
    DummyDisplay d;
    REQUIRE_FALSE(d.initialized);
    int before = allocCount.load();
    d.init();
    REQUIRE(d.initialized);
    REQUIRE(allocCount.load() == before);
}

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}
