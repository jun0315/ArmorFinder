cmake_minimum_required(VERSION 2.8.3)
set(CMAKE_CXX_STANDARD 11)
project(xqj)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    cv_bridge
    image_transport
)

catkin_package(
    CATKIN_DEPENDS roscpp cv_bridge image_transport
)

find_package(OpenCV REQUIRED)

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
        include
)

link_directories(${OpenCV_LIBRARY_DIRS})

add_executable(vision_node src/main.cpp src/armor_find.cpp include/armor_find.h src/pic_porcess.cpp include/pic_porcess.h)

add_definitions(-std=c++11 -g -O3)

target_link_libraries(vision_node
    ${catkin_LIBRARIES}
    ${OpenCV_LIBRARIES}
)
