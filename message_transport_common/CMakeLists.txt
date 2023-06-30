cmake_minimum_required(VERSION 2.4.6)
project(message_transport)

find_package(catkin REQUIRED COMPONENTS
	roscpp
	rospy
	# sensor_msgs
	# std_msgs
	# message_generation
	message_filters
	pluginlib
	# rosbag
	# pcl_ros
	# buffer
	)

catkin_package(
	INCLUDE_DIRS include
	LIBRARIES ${PROJECT_NAME}
	# CATKIN_DEPENDS message_runtime
	)

include_directories(
	include
	${catkin_INCLUDE_DIRS}
	)

add_definitions(-O0 -g -ggdb)

# rosbuild_add_boost_directories()
add_library(${PROJECT_NAME} 
	src/publisher.cpp
	src/subscriber.cpp)
target_link_libraries(${PROJECT_NAME}
	${catkin_LIBRARIES}
  )

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(
 TARGETS ${PROJECT_NAME}
 ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
 LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
 RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

# rosbuild_link_boost(${PROJECT_NAME} system)

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})
