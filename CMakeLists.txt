# CMakeList.txt : CMake project for Space, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(Space)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Add source to this project's executable.
add_executable(Space WIN32 "src/Main.cpp" "src/Game.cpp" "src/Game.h" "src/Nodes/node.h" "src/Nodes/Node.cpp" "src/Nodes/Spaceship.h" "src/Nodes/Spaceship.cpp" "src/Components/VectorRenderer.h" "src/Components/VectorRenderer.cpp"  "src/KeyboardInputManager.cpp" "src/KeyboardInputManager.h" "src/DataTypes.h" "src/DataTypes.cpp" "src/TextRenderer.h" "src/TextRenderer.cpp" "src/Components/ParticleEmitter.h" "src/Components/ParticleEmitter.cpp" "src/Profiler.cpp" "src/Profiler.h" "src/Components/Editor.h" "src/Components/Editor.cpp" "src/Registry.h" "src/Registry.cpp" "src/Components/SoundPlayer.cpp" "src/Components/SoundPlayer.h"  "src/Components/Component.cpp")

# Include base source
target_include_directories(Space PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Use vendored libs
set(SDLTTF_VENDORED ON)

# This assumes the SDL source is available in external/SDL
add_subdirectory(external/SDL EXCLUDE_FROM_ALL)

# This assumes the SDL_ttf source is available in external/SDL_ttf
add_subdirectory(external/SDL_ttf EXCLUDE_FROM_ALL)

# Link to the actual SDL3 library.
target_link_libraries(Space PRIVATE SDL3_ttf::SDL3_ttf SDL3::SDL3)

add_custom_command(TARGET Space POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/data"
    "${CMAKE_BINARY_DIR}/$<CONFIGURATION>/data"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Space PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
