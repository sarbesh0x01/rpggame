cmake_minimum_required(VERSION 3.16)
project(TheReverseWorld LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add raylib (assumes raylib has its own CMakeLists.txt)
add_subdirectory(raylib)

# Include your project's headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Automatically gather all .cpp and .h files from src/ and include/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS src/*.h)

# Create executable
add_executable(TheReverseWorld ${SOURCES} ${HEADERS})

target_link_libraries(TheReverseWorld raylib pthread dl m)


