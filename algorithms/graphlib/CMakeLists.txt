cmake_minimum_required(VERSION 3.14)

project(graphlib LANGUAGES CXX)

# If this is the main project, set default build type to Debug.
# Otherwise use Release.
set(default_build_type "Release")
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(default_build_type "Debug")
endif()
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Retain possible values of build type for cmake-gui.
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# If this is the main project, enable ccache
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  find_program(CCACHE_PROGRAM ccache)
  if(CCACHE_PROGRAM)
      set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
      set(CMAKE_CUDA_COMPILER_LAUNCHER "${CCACHE_PROGRAM}") # CMake 3.9+
  endif()
endif()

# compiled library code is here
add_subdirectory(src/graphlib)

# executable code is here
add_subdirectory(examples)
