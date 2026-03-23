cmake_minimum_required(VERSION 3.14)
project(DataStructTests)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

include_directories(datastructs)

add_executable(tests
    tests/test_complex.cpp
    tests/test_string.cpp
    tests/test_dynamic_array.cpp
    datastructs/Complex.cpp
    datastructs/String.cpp
)

target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
