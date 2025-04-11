
cmake_minimum_required(VERSION 3.16)
project(RpgGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output compile commands for IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# If SDL2 or its extensions weren't found automatically, try pkg-config
if(NOT SDL2_FOUND OR NOT SDL2_IMAGE_FOUND OR NOT SDL2_TTF_FOUND OR NOT SDL2_MIXER_FOUND)
    include(FindPkgConfig)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
endif()

# Log found packages
message(STATUS "SDL2 include directories: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")
message(STATUS "SDL2_image include directories: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_image libraries: ${SDL2_IMAGE_LIBRARIES}")
message(STATUS "SDL2_ttf include directories: ${SDL2_TTF_INCLUDE_DIRS}")
message(STATUS "SDL2_ttf libraries: ${SDL2_TTF_LIBRARIES}")
message(STATUS "SDL2_mixer include directories: ${SDL2_MIXER_INCLUDE_DIRS}")
message(STATUS "SDL2_mixer libraries: ${SDL2_MIXER_LIBRARIES}")

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
  src/core/Game.cpp
  ${IMGUI_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}  # For imconfig.h
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    GL
)

# Add compile definitions for ImGui
target_compile_definitions(${PROJECT_NAME} PRIVATE
    IMGUI_IMPL_OPENGL_LOADER_GLAD
)

# Print executable path for debugging
get_target_property(EXECUTABLE_PATH ${PROJECT_NAME} RUNTIME_OUTPUT_DIRECTORY)
message(STATUS "Executable will be built at: ${EXECUTABLE_PATH}")
