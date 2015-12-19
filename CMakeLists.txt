cmake_minimum_required(VERSION 3.3)
project(videostitch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")





#set(CMAKE_CXX_FLAGS "-lboost_program_options")

find_package( OpenCV REQUIRED )
FIND_PACKAGE(Boost COMPONENTS program_options REQUIRED)

set(SOURCE_FILES main.cpp helpers/drawer.h OpticalFlow.cpp OpticalFlow.h helpers/VideoHelper.h PanoModule.cpp PanoModule.h)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
add_executable(videostitch ${SOURCE_FILES})

target_link_libraries( videostitch ${OpenCV_LIBS} ${Boost_LIBRARIES})