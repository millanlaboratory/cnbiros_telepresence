set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_minimum_required(VERSION 2.8.3)
project(cnbiros_telepresence)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation
										cnbiros_core
										cnbiros_bci
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
	cnbiros_core
	cnbiros_bci
	cnbiros_navigation
)


add_library(cnbiros_telepresence
			src/BciControl.cpp)
target_link_libraries(cnbiros_telepresence
					  ${catkin_LIBRARIES})

add_executable(ros_fusion_robotino src/ros_fusion_robotino.cpp)
target_link_libraries(ros_fusion_robotino cnbiros_telepresence)

add_executable(ros_bcicontrol_robotino src/ros_bcicontrol_robotino.cpp)
target_link_libraries(ros_bcicontrol_robotino cnbiros_telepresence)
