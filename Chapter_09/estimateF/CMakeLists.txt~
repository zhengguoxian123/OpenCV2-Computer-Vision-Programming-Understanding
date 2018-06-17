cmake_minimum_required(VERSION 2.8)
project(estimateF)

SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

set(OpenCV_DIR "/usr/local/opencv2/share/OpenCV")
find_package(OpenCV 2 REQUIRED)
#头文件
include_directories(${OpenCV_INCLUDE_DIR})


#
add_executable(estimateF estimateF.cpp)
#链接动态库
target_link_libraries(estimateF ${OpenCV_LIBS})
