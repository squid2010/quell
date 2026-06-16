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

