cmake_minimum_required(VERSION 3.13)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(lab2 main.cpp  Map.h List.h unit_tests/test_char.cpp unit_tests/test_double.cpp)
target_link_libraries(lab2 gtest gtest_main)