cmake_minimum_required(VERSION 2.4.6)
project(bz2_transport)


## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
set(${PROJECT_NAME}_CATKIN_DEPS
  roscpp
  rospy
  sensor_msgs
  std_msgs
  message_transport
  # templated_transports
)

find_package(catkin REQUIRED COMPONENTS
  ${${PROJECT_NAME}_CATKIN_DEPS}
	message_generation
  # bzip2
  # libbz2
	# buffer
	)
  

find_package(Boost REQUIRED COMPONENTS)
# find_package(libbz2 REQUIRED)

## Find pcl lib
# find_package(PCL REQUIRED)

#uncomment if you have defined messages
add_message_files(FILES
    BZ2Packet.msg
    )

generate_messages(DEPENDENCIES
	std_msgs
	# buffer
	)
#uncomment if you have defined services
# rosbuild_gensrv()

catkin_package(
  CATKIN_DEPENDS ${${PROJECT_NAME}_CATKIN_DEPS}
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS message_runtime
)

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} 
	src/bz2_codec.cpp
	) 
add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
  ${PROJECT_NAME}_generate_messages_cpp
)
target_link_libraries(${PROJECT_NAME}
  # libbz2-dev  
  ${catkin_LIBRARIES}
)

# add_library(test-manifest test/manifest.cpp)
# add_dependencies(test-manifest
#   ${catkin_EXPORTED_TARGETS}
#   ${PROJECT_NAME}_generate_messages_cpp
# )
# target_link_libraries(test-manifest 
# 	${PROJECT_NAME} 
# 	bz2
# 	${catkin_LIBRARIES}
# )

install(DIRECTORY include/${PROJECT_NAME}/
   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

# install(DIRECTORY include/${PROJECT_NAME}/
# DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
# )

# install(
# TARGETS ${PROJECT_NAME}
# ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
# LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
# RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
# )


# install(DIRECTORY include/${PROJECT_NAME}/
#    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
# )
# rosbuild_add_executable(test-instantiate test/instantiate.cpp)
# target_link_libraries(test-instantiate ${PROJECT_NAME})
# 
