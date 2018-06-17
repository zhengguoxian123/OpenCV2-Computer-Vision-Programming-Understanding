cmake_minimum_required(VERSION 2.8)
project(addImage)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++11 -O3")

set(OpenCV_DIR "/usr/local/opencv3/share/Opencv")

find_package(OpenCV 3.2 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIR})

add_executable(addImage addImage.cpp)
target_link_libraries(addImage ${OpenCV_LIBS})
