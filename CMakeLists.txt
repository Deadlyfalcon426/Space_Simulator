cmake_minimum_required(VERSION 3.20)

project(Space_Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(Space_Simulator
    src/main.cpp
    src/PhysicsVector3.cpp
    src/CelestialBody.cpp
    src/PhysicsFunctions.cpp
    src/rk4_variables.cpp
    src/renderer.cpp
)

target_include_directories(Space_Simulator PRIVATE
    include
)

target_link_libraries(Space_Simulator PRIVATE raylib)