cmake_minimum_required(VERSION 3.16)
project(RpgGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output compile commands for IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# If SDL2 wasn't found automatically, try pkg-config
if(NOT SDL2_FOUND)
    include(FindPkgConfig)
    pkg_check_modules(SDL2 REQUIRED sdl2)
endif()

message(STATUS "SDL2 include directories: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")

# Set up ImGui sources
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer2.cpp
)

# Check if all ImGui files exist
foreach(SOURCE_FILE ${IMGUI_SOURCES})
    if(NOT EXISTS "${SOURCE_FILE}")
        message(FATAL_ERROR "ImGui source file not found: ${SOURCE_FILE}")
    endif()
endforeach()

# Create the executable target
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/player.cpp
  src/world.cpp
  ${IMGUI_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}  # For imconfig.h
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} GL)

# Add compile definitions for ImGui
target_compile_definitions(${PROJECT_NAME} PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLAD
)

# Print executable path for debugging
get_target_property(EXECUTABLE_PATH ${PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)
message(STATUS "Executable will be built at: ${EXECUTABLE_PATH}")
