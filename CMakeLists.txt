# CMakeList.txt : CMake project for Space, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Space")

# Add source to this project's executable.
add_executable (Space "Main.cpp"  "Game.cpp" "Game.h" "Nodes/node.h" "Nodes/Node.cpp" "Nodes/Spaceship.h" "Nodes/Spaceship.cpp" "Components/VectorRenderer.h" "Components/VectorRenderer.cpp" "Components/Component.h" "KeyboardInputManager.cpp" "KeyboardInputManager.h" "DataTypes.h" "DataTypes.cpp")

target_include_directories (Space PRIVATE ".")

# Add SDL
add_subdirectory(external/SDL)

# Link SDL2
target_link_libraries(Space PRIVATE SDL3::SDL3)

# Include SDL
target_include_directories(Space PRIVATE external/SDL/include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Space PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
