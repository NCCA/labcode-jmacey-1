cmake_minimum_required(VERSION 3.20)

project(RGBA_BuildALL)

set(CMAKE_CXX_STANDARD 17)

# main executable
add_executable(RGBA)
target_include_directories(RGBA PRIVATE  include)
target_sources(RGBA PRIVATE src/main.cpp)

# tests
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()

add_executable(RGBATests)
target_sources(RGBATests PRIVATE tests/RGBATests.cpp)
target_include_directories(RGBATests PRIVATE include)
target_link_libraries(RGBATests PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(RGBATests)
