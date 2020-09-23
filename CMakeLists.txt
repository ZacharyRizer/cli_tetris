cmake_minimum_required(VERSION 3.0)

project(SDL2Test)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -WALL")

find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test SDL2_test.cpp)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})


