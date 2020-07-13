cmake_minimum_required(VERSION 3.14)

project(graphs LANGUAGES CXX)

# ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_CUDA_COMPILER_LAUNCHER "${CCACHE_PROGRAM}") # CMake 3.9+
endif()

# compiled library code is here
add_subdirectory(src)

# executable code is here
add_subdirectory(examples)
