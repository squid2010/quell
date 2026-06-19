cmake_minimum_required(VERSION 3.16)

project(Quell LANGUAGES CXX) # Quell is project name

set (CMAKE_CXX_STANDARD 17) # use C++17
set (CMAKE_CXX_STANDARD_REQUIRED ON) # require C++17
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent) # fetch googletest automatically from github
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(GoogleTest) # discover TEST() cases automatically

add_library(quell_vm INTERFACE)

target_include_directories(quell_vm
    INTERFACE
        ${PROJECT_SOURCE_DIR}
)

add_executable(test_instruction
    tests/backend/vm/test_instruction.cpp
)

target_link_libraries(test_instruction
    PRIVATE
        quell_vm
        GTest::gtest_main
)

gtest_discover_tests(test_instruction)
