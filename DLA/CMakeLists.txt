cmake_minimum_required(VERSION 3.20)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(DLABuild)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenImageIO CONFIG REQUIRED)
set(Boost_NO_WARN_NEW_VERSIONS 1)
find_package(Boost COMPONENTS filesystem thread)

add_executable(DLA)
target_include_directories(DLA PRIVATE include)
target_sources(DLA PRIVATE src/main.cpp
        src/Image.cpp
        include/Image.h
        include/RGBA.h
        src/Walker.cpp
        include/Walker.h
)
target_link_libraries(DLA PRIVATE OpenImageIO::OpenImageIO Boost::filesystem Boost::thread)
