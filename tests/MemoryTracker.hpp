#ifndef MEMORY_TRACKER_HPP
#define MEMORY_TRACKER_HPP
#include <atomic>
#include <cstdlib>

extern std::atomic<int> allocCount;

void *trackAlloc(std::size_t size);
void trackFree(void *ptr);
#endif // MEMORY_TRACKER_HPP
