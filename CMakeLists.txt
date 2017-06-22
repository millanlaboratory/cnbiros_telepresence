set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_minimum_required(VERSION 2.8.3)
project(cnbiros_telepresence)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation
										cnbiros_navigation)

SET(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(include
					${catkin_INCLUDE_DIRS})

catkin_package(
  INCLUDE_DIRS 
	include
  LIBRARIES 
	${PROJECT_NAME}
  CATKIN_DEPENDS
  	roscpp
	cnbiros_navigation
)

add_executable(ros_fusion_robotino src/ros_fusion_robotino.cpp)
target_link_libraries(ros_fusion_robotino ${catkin_LIBRARIES})

