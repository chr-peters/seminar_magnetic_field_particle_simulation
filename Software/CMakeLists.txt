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

# retrieve the test files
file(GLOB TESTS testcases/*.cpp)

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

# check if gtest and pthread is available
find_package(GTest REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

# create the shell script to run all testcases
file(WRITE ${CMAKE_BINARY_DIR}/run_all.sh "#!/bin/sh\n")

# build the testcases
foreach(CURTEST ${TESTS})
  get_filename_component(CURNAME ${CURTEST} NAME_WE)
  add_executable(${CURNAME}.exe ${CURTEST})
  set_target_properties(${CURNAME}.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY testcases)
  target_link_libraries(${CURNAME}.exe propagator ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
  target_compile_options(${CURNAME}.exe PUBLIC ${COMPILER_FLAGS})
  # add the .exe to the script executing all tests
  file(APPEND ${CMAKE_BINARY_DIR}/run_all.sh "${CMAKE_BINARY_DIR}/testcases/${CURNAME}.exe\n")
endforeach(CURTEST)

# change the permissions of the test file
file(
    COPY ${CMAKE_BINARY_DIR}/run_all.sh
    DESTINATION ${CMAKE_BINARY_DIR}/testcases/
    FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
)

# remove the old file
file(REMOVE ${CMAKE_BINARY_DIR}/run_all.sh)
