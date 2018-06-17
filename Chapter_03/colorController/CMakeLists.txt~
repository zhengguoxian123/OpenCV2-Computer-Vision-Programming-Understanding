cmake_minimum_required(VERSION 2.8)
project(colorController)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

set(OpenCV_DIR "/usr/local/opencv3/share/OpenCV")

find_package(OpenCV 3.2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

add_executable(colorController
colorDetection.cpp
colordetector.cpp
colorDetectController.cpp)

target_link_libraries(colorController ${OpenCV_LIBS})
