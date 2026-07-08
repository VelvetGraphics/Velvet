cmake_minimum_required(VERSION 4.2)
project(Velvet)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE VELVET_SOURCE CONFIGURE_DEPENDS
        Velvet/Source/Velvet/*.cpp
)

add_library(Velvet STATIC ${VELVET_SOURCE} Velvet/Include/Velvet/Velvet.hpp)
add_subdirectory(Velvet/Vendor/GLFW)

target_compile_options(Velvet PUBLIC
        "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
)
add_subdirectory(Velvet/Vendor/spdlog)

target_include_directories(Velvet PUBLIC
        Velvet/Include
        Velvet/Source

        Velvet/Vendor/GLFW/include
        Velvet/Vendor/entt/single_include
        Velvet/Vendor/spdlog/include
)

target_link_libraries(Velvet PUBLIC
        glfw
)

if (WIN32)
    target_compile_definitions(Velvet PUBLIC
            VELVET_PLATFORM_WINDOWS=1
            VELVET_PLATFORM_USE_GLFW=1
            VELVET_PLATFORM_USE_VULKAN=1
    )
else ()
    message(FATAL_ERROR "Velvet does NOT support this platform")
endif ()

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
