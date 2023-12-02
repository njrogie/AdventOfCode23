cmake_minimum_required(VERSION 3.2)

project(Day1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(src)

set(SOURCES main.cpp src/day1.cpp src/day1.h)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

