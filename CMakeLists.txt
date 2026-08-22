cmake_minimum_required(VERSION 3.20)

project(Space_Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Space_Simulator
    src/simulator.cpp
    src/Vector3.cpp
    src/CelestialBody.cpp
    src/PhysicsFunctions.cpp
    src/rk4_variables.cpp
)

target_include_directories(Space_Simulator PRIVATE
    include
)