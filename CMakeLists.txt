cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(NotReallyPhysics VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL3 (requires SDL3 to be installed on your system)
find_package(SDL3 REQUIRED CONFIG)

# Add executable (replace main.cpp with your source files)
add_executable(NotReallyPhysics main.cpp)

# Link against SDL3 (dynamic by default)
target_link_libraries(NotReallyPhysics PRIVATE SDL3::SDL3)
