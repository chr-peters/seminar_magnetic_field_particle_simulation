# the current version installed
cmake_minimum_required(VERSION 3.4.1)

set(PROJECT_NAME "Seminararbeit")
set(COMPILER_FLAGS -std=c++11 -Wall)

project(${PROJECT_NAME})

# specify the include directory
include_directories(include)

# retrieve the source files
file(GLOB SOURCES src/*.cpp)

# retrieve the example files
file(GLOB EXAMPLES examples/*.cpp)

# remove the .cpp file that contains the main method from the source files

# create a static library from the source files
add_library(propagator STATIC ${SOURCES})
target_compile_options(propagator PUBLIC ${COMPILER_FLAGS})

# build the examples
foreach(CUREXAMPLE ${EXAMPLES})
  get_filename_component(CURNAME ${CUREXAMPLE} NAME_WE)
  add_executable(${CURNAME}.exe ${CUREXAMPLE})
  set_target_properties(${CURNAME}.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY examples)
  target_link_libraries(${CURNAME}.exe propagator)
  target_compile_options(${CURNAME}.exe PUBLIC ${COMPILER_FLAGS})
endforeach(CUREXAMPLE)
