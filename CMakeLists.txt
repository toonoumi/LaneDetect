cmake_minimum_required(VERSION 3.5)
project(CAR_UI CXX)

# require a C++11 compiler
# use it for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# configure Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (CMAKE_PREFIX_PATH "C:/Qt/5.9/msvc2017_64")
find_package(Qt5 COMPONENTS Widgets core REQUIRED)

set (CMAKE_PREFIX_PATH "C:/opencv32/build")
find_package( OpenCV REQUIRED )

# EDIT: add your (non-test) source files to this list
set(src
  main.cpp
  mainwindow.cpp
  view.hpp
  thread_back.hpp
  thread_back.cpp
  thread_front.cpp
  thread_front.hpp
  LaneDetector.hpp
  LaneDetector.cpp
  )
add_executable(carui ${src})
target_link_libraries(carui Qt5::Widgets ${OpenCV_LIBS})

