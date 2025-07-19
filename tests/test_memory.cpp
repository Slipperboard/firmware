#include <new>
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

#ifndef DISABLE_MEMORY_TRACKING
TEST_CASE("nothrow sized delete operators", "[memory]")
{
    char* p = new (std::nothrow) char;
    REQUIRE(static_cast<void*>(p) != nullptr);
    ::operator delete(p, sizeof(char), std::nothrow);

    char* q = new (std::nothrow) char;
    REQUIRE(static_cast<void*>(q) != nullptr);
    ::operator delete(q, std::nothrow);

    char* r = new char;
    ::operator delete(r, sizeof(char));

    char* arr = new (std::nothrow) char[2];
    REQUIRE(static_cast<void*>(arr) != nullptr);
    ::operator delete[](arr, 2, std::nothrow);

    char* arr2 = new char[3];
    ::operator delete[](arr2, 3);

    char* arr3 = new (std::nothrow) char[4];
    ::operator delete[](arr3, std::nothrow);

    char* arr4 = new char[5];
    ::operator delete[](arr4);
}
#endif
