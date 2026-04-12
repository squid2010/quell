cmake_minimum_required(VERSION 3.16)

project(Quell LANGUAGES CXX) # Project Name

set(CMAKE_CXX_STANDARD 17) # use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/datastructs) # include work without relative paths

include(FetchContent) # fetch googletest automatically from github
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(DATASOURCE_FILES # add cpp, .tpp don't need cause in headers
    datastructs/Complex.cpp
    datastructs/Matrix.cpp
    datastructs/String.cpp
)

set(TEST_FILES # add tests
    tests/test_complex.cpp
    tests/test_dynamic_array.cpp
    tests/test_matrix.cpp
    tests/test_stack.cpp
    tests/test_string.cpp
)

add_executable(run_tests ${DATASOURCE_FILES} ${TEST_FILES}) # make an executable named run_tests

target_link_libraries(run_tests gtest_main) # link GoogleTest function + library

include(GoogleTest) # discover TEST() cases automatically
gtest_discover_tests(run_tests)
