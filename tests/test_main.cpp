#define CATCH_CONFIG_RUNNER
#include <new>
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

void* operator new(std::size_t size)
{
    return trackAlloc(size);
}
void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    return trackAlloc(size);
}
void operator delete(void* ptr) noexcept
{
    trackFree(ptr);
}
void operator delete(void* ptr, std::size_t) noexcept
{
    trackFree(ptr);
}
void operator delete(void* ptr, const std::nothrow_t&) noexcept
{
    trackFree(ptr);
}
void operator delete(void* ptr, std::size_t, const std::nothrow_t&) noexcept
{
    trackFree(ptr);
}
void* operator new[](std::size_t size)
{
    return trackAlloc(size);
}
void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return trackAlloc(size);
}
void operator delete[](void* ptr) noexcept
{
    trackFree(ptr);
}
void operator delete[](void* ptr, std::size_t) noexcept
{
    trackFree(ptr);
}
void operator delete[](void* ptr, const std::nothrow_t&) noexcept
{
    trackFree(ptr);
}
void operator delete[](void* ptr, std::size_t, const std::nothrow_t&) noexcept
{
    trackFree(ptr);
}

int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}
