#ifndef MEMORY_TRACKER_HPP
#define MEMORY_TRACKER_HPP
#include <atomic>
#include <cstdlib>

extern std::atomic<int> allocCount;

inline void* trackAlloc(std::size_t size) {
    allocCount.fetch_add(1, std::memory_order_relaxed);
    return std::malloc(size);
}

inline void trackFree(void* ptr) {
    allocCount.fetch_sub(1, std::memory_order_relaxed);
    std::free(ptr);
}
#endif // MEMORY_TRACKER_HPP
