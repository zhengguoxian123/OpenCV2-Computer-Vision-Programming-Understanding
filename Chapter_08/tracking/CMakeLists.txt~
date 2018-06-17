cmake_minimum_required(VERSION 2.8)
project(tracking)

set(CMAKE_BUILD_TYPE Release)
set(CMKAE_CXX_FLAGS "-std=c++11 -O3")

set(OpenCV_DIR /usr/local/opencv2/share/OpenCV )
find_package(OpenCV 2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

add_executable(tracking tracking.cpp)
target_link_libraries(tracking ${OpenCV_LIBS})
