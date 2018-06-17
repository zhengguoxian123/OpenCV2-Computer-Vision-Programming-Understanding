cmake_minimum_required(VERSION 2.8)
project(interestPoints)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

set(OpenCV_DIR /usr/local/opencv2/share/OpenCV )
find_package(OpenCV 2 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIR})

add_executable(interestPoints interestPoints.cpp)
target_link_libraries(interestPoints ${OpenCV_LIBS})
