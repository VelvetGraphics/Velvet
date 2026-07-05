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
)

# TODO: Remove
add_executable(Sandbox Sandbox/Source/Sandbox.cpp)
target_link_libraries(Sandbox PUBLIC
        Velvet
)
target_include_directories(Sandbox PUBLIC
        Velvet/Include
        Velvet/Source
)
