# CMakeList.txt : CMake project for Space, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

project(Space)

find_package(sdl3 REQUIRED)
find_package(sdl3_ttf REQUIRED)

# Add source to this project's executable.
add_executable(Space WIN32 "src/Main.cpp" "src/Game.cpp" "src/Game.h" "src/Nodes/Node.h" "src/Nodes/Node.cpp" "src/Nodes/Spaceship.h" "src/Nodes/Spaceship.cpp" "src/Components/VectorRenderer.h" "src/Components/VectorRenderer.cpp" "src/DataTypes.h" "src/DataTypes.cpp" "src/Components/ParticleEmitter.h" "src/Components/ParticleEmitter.cpp" "src/Profiler.cpp" "src/Profiler.h" "src/Components/Editor.h" "src/Components/Editor.cpp" "src/Registry.h" "src/Registry.cpp" "src/Components/SoundPlayer.cpp" "src/Components/SoundPlayer.h"  "src/Components/Component.cpp" "src/Renderer.cpp" "src/Renderer.h" "src/Nodes/Camera.cpp" "src/Nodes/Camera.h")

# Include base source
target_include_directories(Space PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(Space PRIVATE SDL3::SDL3)
target_link_libraries(Space PRIVATE SDL3_ttf::SDL3_ttf)

# Copy game data
add_custom_command(TARGET Space POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/data"
    "${CMAKE_BINARY_DIR}/$<CONFIGURATION>/data"
)

set_property(TARGET Space PROPERTY CXX_STANDARD 20)
