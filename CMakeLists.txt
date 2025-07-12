cmake_minimum_required(VERSION 3.13)
project(slipperboard LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather all source files in src/ excluding the main entrypoint
file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(slipperboard_lib ${SRC_FILES})

target_include_directories(slipperboard_lib PUBLIC include)

# Main firmware executable
add_executable(slipperboard
    src/main.cpp
)

target_link_libraries(slipperboard PRIVATE slipperboard_lib)

# Optionally build unit tests with Catch2
option(ENABLE_TESTS "Build unit tests" OFF)
if(ENABLE_TESTS)
    enable_testing()
    file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")
    add_executable(slipperboard_tests
        lib/Catch2/catch_amalgamated.cpp
        ${TEST_SOURCES}
    )
    target_link_libraries(slipperboard_tests PRIVATE slipperboard_lib)
    target_include_directories(slipperboard_tests PRIVATE tests)
    add_test(NAME slipperboard_tests COMMAND slipperboard_tests)
endif()
