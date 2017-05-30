cmake_minimum_required (VERSION 2.6)
project (LaneDetect)
find_package (OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-lwiringPi")
add_executable(LaneDetect LaneDetector.h LaneDetector.cpp main.cpp)
target_link_libraries( LaneDetect ${OpenCV_LIBS} )

