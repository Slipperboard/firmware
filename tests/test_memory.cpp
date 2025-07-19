#include <new>
#include "MemoryTracker.hpp"
#include "catch_amalgamated.hpp"

TEST_CASE("nothrow sized delete operators", "[memory]")
{
    char* p = new (std::nothrow) char;
    REQUIRE(static_cast<void*>(p) != nullptr);
    delete p;

    char* q = new (std::nothrow) char;
    REQUIRE(static_cast<void*>(q) != nullptr);
    delete q;

    char* r = new char;
    delete r;

    char* arr = new (std::nothrow) char[2];
    REQUIRE(static_cast<void*>(arr) != nullptr);
    delete[] arr;

    char* arr2 = new char[3];
    delete[] arr2;

    char* arr3 = new (std::nothrow) char[4];
    delete[] arr3;

    char* arr4 = new char[5];
    delete[] arr4;
}
