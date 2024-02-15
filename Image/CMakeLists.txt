cmake_minimum_required(VERSION 3.20)

project(Image_BuildALL)
set(CMAKE_CXX_STANDARD 17)

# main executable
add_executable(Image)
target_include_directories(Image PRIVATE  include)
target_sources(Image PRIVATE src/main.cpp)

# tests
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()

add_executable(ImageTests)
target_sources(ImageTests PRIVATE tests/RGBATests.cpp
                                  tests/ImageTests.cpp
                                    src/Image.cpp
                                    include/Image.h
)
target_include_directories(ImageTests PRIVATE include)
target_link_libraries(ImageTests PRIVATE GTest::gtest GTest::gtest_main)

gtest_discover_tests(ImageTests)
