set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_minimum_required(VERSION 2.8.3)
project(cnbiros_telepresence)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs message_generation
										cnbiros_core
										cnbiros_bci
										cnbiros_fusion
										cnbiros_navigation)

SET(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(include
					${catkin_INCLUDE_DIRS})
add_service_files(
  FILES
  SetInputRangeSrv.srv
  SetAngleRangeSrv.srv
  SetDistanceSrv.srv
)

generate_messages(
	DEPENDENCIES
	std_msgs
)

catkin_package(
  INCLUDE_DIRS 
	include
  LIBRARIES 
	${PROJECT_NAME}
  CATKIN_DEPENDS
  	roscpp
	cnbiros_core
	cnbiros_bci
	cnbiros_fusion
	cnbiros_navigation
)


add_library(cnbiros_telepresence
			src/BciBridge.cpp)
target_link_libraries(cnbiros_telepresence
					  ${catkin_LIBRARIES})

add_executable(ros_robotino_bcibridge src/ros_robotino_bcibridge.cpp)
target_link_libraries(ros_robotino_bcibridge cnbiros_telepresence)

add_executable(ros_robotino_attractors src/ros_robotino_attractors.cpp)
target_link_libraries(ros_robotino_attractors cnbiros_telepresence)

add_executable(ros_robotino_repellors src/ros_robotino_repellors.cpp)
target_link_libraries(ros_robotino_repellors cnbiros_telepresence)

add_executable(ros_robotino_navigation src/ros_robotino_navigation.cpp)
target_link_libraries(ros_robotino_navigation cnbiros_telepresence)
#
#
#add_executable(ros_forcefield_robotino src/ros_forcefield_robotino.cpp)
#target_link_libraries(ros_forcefield_robotino cnbiros_telepresence)
