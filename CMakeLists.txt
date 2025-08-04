cmake_minimum_required(VERSION 3.16)
project(TheReverseWorld LANGUAGES CXX)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add raylib (assumes raylib/ has CMakeLists.txt)
add_subdirectory(raylib)

# Source and header files (manually listed)
set(SOURCES
    src/main.cpp
    src/player.cpp
    src/app.cpp
    src/Level1.cpp
)

set(HEADERS
    src/main.h
    src/player.h
    src/Level1.h
)

# Create executable
add_executable(TheReverseWorld ${SOURCES} ${HEADERS})

# Include project headers
target_include_directories(TheReverseWorld PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link raylib and required system libs for Linux
target_link_libraries(TheReverseWorld PRIVATE raylib pthread dl m)
