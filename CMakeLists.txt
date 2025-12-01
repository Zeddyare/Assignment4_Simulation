cmake_minimum_required(VERSION 4.0)
project(Simulation)

set(CMAKE_CXX_STANDARD 20)

add_executable(Simulation main.cpp
        City.cpp
        GameSpecs.cpp
        Organism.cpp
        Human.cpp
        Zombie.cpp)
