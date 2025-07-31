cmake_minimum_required(VERSION 3.16)
project(TheReverseWorld LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add raylib (assumes raylib has its own CMakeLists.txt)
add_subdirectory(raylib)

# Get all .cpp files in src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable
add_executable(TheReverseWorld ${SOURCES})

# Link with raylib and system libraries
target_link_libraries(TheReverseWorld raylib m pthread dl rt X11)
