cmake_minimum_required(VERSION 3.3)
project(videostitch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( OpenCV REQUIRED )

set(SOURCE_FILES main.cpp helpers/drawer.h OpticalFlow.cpp OpticalFlow.h helpers/VideoHelper.h PanoModule.cpp PanoModule.h)
add_executable(videostitch ${SOURCE_FILES})

target_link_libraries( videostitch ${OpenCV_LIBS} )