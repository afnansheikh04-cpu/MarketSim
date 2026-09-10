cmake_minimum_required(VERSION 3.20) ## project needs at least CMake 3.20

project(MarketSim) # names the Project

set(CMAKE_CXX_STANDARD 20) # tells CMake to use C++20 to coompie with
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(MarketSim
    src/main.cpp
    src/MarketDataService.cpp
    src/CsvWriter.cpp
) # says: build an executable called MarketSim using the main.cpp

target_include_directories(MarketSim PRIVATE include) ## ensure to look inside the include folder
target_link_libraries(MarketSim PRIVATE CURL::libcurl nlohmann_json::nlohmann_json) # cmake find this library installed 
