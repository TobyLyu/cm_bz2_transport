cmake_minimum_required(VERSION 2.8.3)
project(cm_transport)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

set(${PROJECT_NAME}_CATKIN_DEPS
    image_transport
    roscpp 
    std_msgs 
    std_srvs 
    sensor_msgs 
    message_filters
    message_transport
    templated_transports
)
find_package(catkin REQUIRED COMPONENTS 
  ${${PROJECT_NAME}_CATKIN_DEPS}
  message_generation
  )
  
find_package(PkgConfig)
find_package(Boost REQUIRED COMPONENTS)

###################################################
## Declare things to be passed to other projects ##
###################################################

## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need

# catkin_python_setup()

add_message_files(FILES
  Packet.msg
	)


# add_service_files(
#   FILES
# )


generate_messages(
    DEPENDENCIES
    std_msgs
    sensor_msgs
    bz2_transport
  )


catkin_package(
    CATKIN_DEPENDS ${${PROJECT_NAME}_CATKIN_DEPS}
    # INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS message_runtime
  )


# catkin_install_python(PROGRAMS 
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )



###########
## Build ##
###########
include_directories(
  ${catkin_INCLUDE_DIRS}
  )

## Declare a cpp executable
add_library(${PROJECT_NAME} 
  src/manifest.cpp
)
add_dependencies(${PROJECT_NAME}
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(${PROJECT_NAME}
	${catkin_LIBRARIES}
  bz2
)

add_executable(${PROJECT_NAME}_list_transports src/list_transports.cpp)
add_dependencies(${PROJECT_NAME}_list_transports
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(${PROJECT_NAME}_list_transports ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME}_publisher src/publisher.cpp)
add_dependencies(${PROJECT_NAME}_publisher
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(${PROJECT_NAME}_publisher
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(${PROJECT_NAME}_subscriber src/subscriber.cpp)
add_dependencies(${PROJECT_NAME}_subscriber
  ${catkin_EXPORTED_TARGETS}
)
target_link_libraries(${PROJECT_NAME}_subscriber
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

#############
## Install ##
#############
install(TARGETS ${PROJECT_NAME}_list_transports
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}_publisher
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(TARGETS ${PROJECT_NAME}_subscriber
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(FILES cm_plugins.xml
        DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
