cmake_minimum_required(VERSION 3.0.2)
project(sensor_fusion)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  chassis_msg
  mobileye_avante_msg
  tracking_msg
  radar_msg
  jsk_recognition_msgs
  message_filters
  message_generation
)

find_package(Boost REQUIRED COMPONENTS thread)
find_package(Threads REQUIRED)

generate_messages(
  DEPENDENCIES
  std_msgs
  chassis_msg
  jsk_recognition_msgs
)

catkin_package(
  INCLUDE_DIRS 
    include
    src
  LIBRARIES 
    ${PROJECT_NAME}_lib
  CATKIN_DEPENDS 
    roscpp 
    rospy 
    std_msgs
    chassis_msg
    mobileye_avante_msg
    tracking_msg
    radar_msg
    jsk_recognition_msgs
    message_filters
    message_generation
  DEPENDS 
    Boost
    system_lib
)

include_directories(
  include
  src
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

set(PROJECT_LIB_FILES
  src/coordinate.cpp
  src/coordinate_transformation_front_radar_track.cpp
  src/coordinate_transformation_front_vision_lane.cpp
  src/coordinate_transformation_front_vision_track.cpp
  src/correction.cpp
  src/filter_in_vehicle_sensor.cpp
  src/gating.cpp
  src/inv.cpp
  src/motion_attribute.cpp
  src/pedestrian_recognition.cpp
  src/prediction.cpp
  src/road_curvature.cpp
  src/rtGetInf.cpp
  src/rtGetNaN.cpp
  src/rt_nonfinite.cpp
  src/shape_attribute.cpp
  src/sort.cpp
  src/sortIdx.cpp
  src/tracking.cpp
  src/track_management.cpp
  src/unit_conversion.cpp
  src/unit_conversion_data.cpp
  src/unit_conversion_front_radar_track.cpp
  src/unit_conversion_front_vision_lane.cpp
  src/unit_conversion_front_vision_track.cpp
  src/unit_conversion_initialize.cpp
  src/unit_conversion_in_vehicle_sensor.cpp
  src/unit_conversion_terminate.cpp
  src/vehicle_recognition.cpp
)

add_library(${PROJECT_NAME}_lib
  ${PROJECT_LIB_FILES}
)

add_executable(${PROJECT_NAME}
  node/fusion_node.cpp
)

target_link_libraries(${PROJECT_NAME}_lib
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
  ${PROJECT_NAME}_lib
)

add_dependencies(${PROJECT_NAME}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

