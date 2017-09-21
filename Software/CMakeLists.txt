# the current version installed
cmake_minimum_required(VERSION 3.4.1)

set(PROJECT_NAME "Seminararbeit")
set(PROJECT_MAIN_FILE src/main.cpp)
set(COMPILER_FLAGS -std=c++11 -Wall)

project(${PROJECT_NAME})

# specify the include directory
include_directories(include)

# retrieve the source files
file(GLOB SOURCES src/*.cpp)

# remove the .cpp file that contains the main method from the source files
list(REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/${PROJECT_MAIN_FILE})

# create a static library from the source files
add_library(propagator STATIC ${SOURCES})

# build the main-executable
add_executable(run.exe ${PROJECT_MAIN_FILE})
target_link_libraries(run.exe propagator)
target_compile_options(run.exe PUBLIC ${COMPILER_FLAGS})
