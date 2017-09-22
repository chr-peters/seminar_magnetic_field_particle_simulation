# the current version installed
cmake_minimum_required(VERSION 3.4.1)

set(PROJECT_NAME "Seminararbeit")
set(PROJECT_MAIN_FILE src/main.cpp)
set(COMPILER_FLAGS -std=c++11 -Wall)

# get the compile options for root necessary to build the examples
execute_process(COMMAND root-config --libs OUTPUT_VARIABLE
EXAMPLE_LIBS)
execute_process(COMMAND root-config --cflags OUTPUT_VARIABLE
EXAMPLE_FLAGS)
string(STRIP ${EXAMPLE_FLAGS} EXAMPLE_FLAGS)
string(STRIP ${EXAMPLE_LIBS} EXAMPLE_LIBS)

# create lists from the strings
string(REPLACE " " ";" EXAMPLE_FLAGS ${EXAMPLE_FLAGS})
string(REPLACE " " ";" EXAMPLE_LIBS ${EXAMPLE_LIBS})

project(${PROJECT_NAME})

# specify the include directory
include_directories(include)

# retrieve the source files
file(GLOB SOURCES src/*.cpp)

# retrieve the example files
file(GLOB EXAMPLES examples/*.cpp)

# remove the .cpp file that contains the main method from the source files
list(REMOVE_ITEM SOURCES ${CMAKE_SOURCE_DIR}/${PROJECT_MAIN_FILE})

# create a static library from the source files
add_library(propagator STATIC ${SOURCES})
target_compile_options(propagator PUBLIC ${COMPILER_FLAGS})

# build the main-executable
add_executable(run.exe ${PROJECT_MAIN_FILE})
target_link_libraries(run.exe propagator)
target_compile_options(run.exe PUBLIC ${COMPILER_FLAGS})

# build the examples
foreach(CUREXAMPLE ${EXAMPLES})
  get_filename_component(CURNAME ${CUREXAMPLE} NAME_WE)
  add_executable(${CURNAME}.exe ${CUREXAMPLE})
  set_target_properties(${CURNAME}.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY examples)
  target_link_libraries(${CURNAME}.exe propagator ${EXAMPLE_LIBS})
  # target_compile_options(${CURNAME}.exe PUBLIC ${EXAMPLE_FLAGS})
endforeach(CUREXAMPLE)
