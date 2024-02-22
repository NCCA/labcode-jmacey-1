cmake_minimum_required(VERSION 3.20)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(Image_BuildALL)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenImageIO CONFIG REQUIRED)
find_package(Boost COMPONENTS filesystem thread)
# main executable
add_executable(Image)
target_include_directories(Image PRIVATE  include)
target_sources(Image PRIVATE src/main.cpp src/Image.cpp)
target_link_libraries(Image PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread)

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
target_link_libraries(ImageTests PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread)


gtest_discover_tests(ImageTests)
