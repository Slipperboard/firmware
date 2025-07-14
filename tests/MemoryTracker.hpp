#ifndef MEMORY_TRACKER_HPP
#define MEMORY_TRACKER_HPP
#include <atomic>
#include <cstdlib>

extern std::atomic<int> allocCount;

void* trackAlloc(std::size_t size);
void trackFree(void* ptr);

void operator delete(void* ptr, std::size_t) noexcept;
void operator delete(void* ptr, const std::nothrow_t&) noexcept;
void operator delete(void* ptr, std::size_t, const std::nothrow_t&) noexcept;
void operator delete[](void* ptr, std::size_t) noexcept;
void operator delete[](void* ptr, const std::nothrow_t&) noexcept;
void operator delete[](void* ptr, std::size_t, const std::nothrow_t&) noexcept;
#endif // MEMORY_TRACKER_HPP
