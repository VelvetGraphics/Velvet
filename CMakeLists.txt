cmake_minimum_required(VERSION 4.2)
project(Velvet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE VELVET_SOURCE CONFIGURE_DEPENDS
        Velvet/Source/Velvet/*.cpp
)

add_library(Velvet STATIC ${VELVET_SOURCE} Velvet/Include/Velvet/Velvet.hpp)

target_include_directories(Velvet PUBLIC
        Velvet/Include
        Velvet/Source

        Velvet/Vendor/entt/single_include
)

# Tests
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

#file(GLOB_RECURSE VELVET_TEST_SOURCE CONFIGURE_DEPENDS
#        Velvet/Tests/*.cpp
#)
#add_executable(_Test_Velvet_ ${VELVET_TEST_SOURCE})
#
#target_link_libraries(_Test_Velvet_ PRIVATE
#        GTest::gtest_main
#        Velvet
#)
#
#include(GoogleTest)
#gtest_discover_tests(_Test_Velvet_)


# TODO: Remove
add_executable(Sandbox Sandbox/Source/Sandbox.cpp)
target_link_libraries(Sandbox PUBLIC
        Velvet
)
target_include_directories(Sandbox PUBLIC
        Velvet/Include
        Velvet/Source
)
