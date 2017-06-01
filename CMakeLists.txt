cmake_minimum_required (VERSION 2.6)
project (LaneDetect)
set (CMAKE_PREFIX_PATH "/usr/local/Cellar/opencv3/3.2.0")
find_package (OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(LaneDetect LaneDetector.h LaneDetector.cpp main.cpp)
target_link_libraries( LaneDetect ${OpenCV_LIBS} )

