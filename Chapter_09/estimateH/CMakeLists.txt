cmake_minimum_required(VERSION 2.8)
project(estimateH)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

set(OpenCV_DIR "/usr/local/opencv2/share/OpenCV")
find_package(OpenCV 2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})

add_executable(estimateH estimateH.cpp)
target_link_libraries(estimateH ${OpenCV_LIBS})


