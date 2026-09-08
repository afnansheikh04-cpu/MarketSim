cmake_minimum_required(VERSION 3.20) ## project needs at least CMake 3.20

project(MarketSim) # names the Project

set(CMAKE_CXX_STANDARD 20) # tells CMake to use C++20 to co

add_executable(MarketSim
    src/main.cpp
) # says: build an executable called MarketSim using the main.cpp

target_include_directories(MarketSim PRIVATE include) ## ensure to look inside the include folder