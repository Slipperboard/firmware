#define CATCH_CONFIG_RUNNER
#include "catch_amalgamated.hpp"
#include <atomic>
#include <cstdlib>

std::atomic<int> allocCount{0};

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

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}
