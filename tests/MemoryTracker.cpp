#include "MemoryTracker.hpp"

std::atomic<int> allocCount{0};

void* trackAlloc(std::size_t size) {
    allocCount.fetch_add(1, std::memory_order_relaxed);
    return std::malloc(size);
}

void trackFree(void* ptr) {
    allocCount.fetch_sub(1, std::memory_order_relaxed);
    std::free(ptr);
}
