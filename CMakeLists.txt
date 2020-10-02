cmake_minimum_required(VERSION 3.0)

# Tell CMake what our project is called
project(MyGame)

# Add compiler errors/warnings flags
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Where to place lib and binaries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Find version 2.5.0 of the SFML library on this computer,
# If the package can't be found, terminate the script
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

# Add all cpp source files under the src directory
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add the following SFML module to the application:
target_link_libraries(${PROJECT_NAME} sfml-graphics)
