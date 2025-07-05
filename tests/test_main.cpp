#define CATCH_CONFIG_RUNNER
#include "catch_amalgamated.hpp"
#include "MemoryTracker.hpp"

void* operator new(std::size_t size) { return trackAlloc(size); }
void operator delete(void* ptr) noexcept { trackFree(ptr); }
void* operator new[](std::size_t size) { return trackAlloc(size); }
void operator delete[](void* ptr) noexcept { trackFree(ptr); }

int main(int argc, char* argv[]) {
    return Catch::Session().run(argc, argv);
}
