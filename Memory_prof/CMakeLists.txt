cmake_minimum_required (VERSION 3.8)

project ("Memory_profiling")

add_executable (Memory_profiling  "src/main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Memory_profiling PROPERTY CXX_STANDARD 20)
endif()
