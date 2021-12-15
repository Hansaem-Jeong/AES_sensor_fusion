#include "ros/ros.h"
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <vector>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include "sensor_fusion/message_types.h"

#include "tracking_msg/Tracking.h"
#include "tracking_msg/TrackingArray.h"

#include "chassis_msg/LOG_BYTE0.h"
#include "chassis_msg/LOG_BYTE1.h"
#include "chassis_msg/LOG_BYTE2.h"
#include "chassis_msg/LOG_BYTE3.h"
#include "mobileye_avante_msg/ME_Lane_Add_info_1.h"
#include "mobileye_avante_msg/ME_Lane_Additional_Data_1.h"
#include "mobileye_avante_msg/ME_Lane_Additional_Data_2.h"
#include "mobileye_avante_msg/ME_Lane_Additional_Data_3.h"
#include "mobileye_avante_msg/ME_Left_Lane_A.h"
#include "mobileye_avante_msg/ME_Left_Lane_B.h"
#include "mobileye_avante_msg/ME_Right_Lane_A.h"
#include "mobileye_avante_msg/ME_Right_Lane_B.h"
#include "mobileye_avante_msg/Obstacle_Additional_Data_1.h"
#include "mobileye_avante_msg/Obstacle_Additional_Data_2.h"
#include "mobileye_avante_msg/Obstacle_Additional_Data_3.h"
#include "mobileye_avante_msg/Obstacle_Additional_Data_4.h"
#include "mobileye_avante_msg/Obstacle_Additional_Data_5.h"
#include "mobileye_avante_msg/Obstacle_Data_1_A.h"
#include "mobileye_avante_msg/Obstacle_Data_1_B.h"
#include "mobileye_avante_msg/Obstacle_Data_1_C.h"
#include "mobileye_avante_msg/Obstacle_Data_2_A.h"
#include "mobileye_avante_msg/Obstacle_Data_2_B.h"
#include "mobileye_avante_msg/Obstacle_Data_2_C.h"
#include "mobileye_avante_msg/Obstacle_Data_3_A.h"
#include "mobileye_avante_msg/Obstacle_Data_3_B.h"
#include "mobileye_avante_msg/Obstacle_Data_3_C.h"
#include "mobileye_avante_msg/Obstacle_Data_4_A.h"
#include "mobileye_avante_msg/Obstacle_Data_4_B.h"
#include "mobileye_avante_msg/Obstacle_Data_4_C.h"
#include "mobileye_avante_msg/Obstacle_Data_5_A.h"
#include "mobileye_avante_msg/Obstacle_Data_5_B.h"
#include "mobileye_avante_msg/Obstacle_Data_5_C.h"
#include "mobileye_avante_msg/Obstacle_Data_6_A.h"
#include "mobileye_avante_msg/Obstacle_Data_6_B.h"
#include "mobileye_avante_msg/Obstacle_Data_6_C.h"
#include "mobileye_avante_msg/Obstacle_Data_7_A.h"
#include "mobileye_avante_msg/Obstacle_Data_7_B.h"
#include "mobileye_avante_msg/Obstacle_Data_7_C.h"
#include "mobileye_avante_msg/Obstacle_Data_8_A.h"
#include "mobileye_avante_msg/Obstacle_Data_8_B.h"
#include "mobileye_avante_msg/Obstacle_Data_8_C.h"
#include "mobileye_avante_msg/Obstacle_Data_9_A.h"
#include "mobileye_avante_msg/Obstacle_Data_9_B.h"
#include "mobileye_avante_msg/Obstacle_Data_9_C.h"
#include "mobileye_avante_msg/Obstacle_Data_10_A.h"
#include "mobileye_avante_msg/Obstacle_Data_10_B.h"
#include "mobileye_avante_msg/Obstacle_Data_10_C.h"
#include "radar_msg/Track1.h"
#include "radar_msg/Track2.h"
#include "radar_msg/Track3.h"
#include "radar_msg/Track4.h"
#include "radar_msg/Track5.h"
#include "radar_msg/Track6.h"
#include "radar_msg/Track7.h"
#include "radar_msg/Track8.h"
#include "radar_msg/Track9.h"
#include "radar_msg/Track10.h"
#include "radar_msg/Track11.h"
#include "radar_msg/Track12.h"
#include "radar_msg/Track13.h"
#include "radar_msg/Track14.h"
#include "radar_msg/Track15.h"
#include "radar_msg/Track16.h"
#include "radar_msg/Track17.h"
#include "radar_msg/Track18.h"
#include "radar_msg/Track19.h"
#include "radar_msg/Track20.h"
#include "radar_msg/Track21.h"
#include "radar_msg/Track22.h"
#include "radar_msg/Track23.h"
#include "radar_msg/Track24.h"
#include "radar_msg/Track25.h"
#include "radar_msg/Track26.h"
#include "radar_msg/Track27.h"
#include "radar_msg/Track28.h"
#include "radar_msg/Track29.h"
#include "radar_msg/Track30.h"
#include "radar_msg/Track31.h"
#include "radar_msg/Track32.h"

#include "coder_array.h"
#include "coder_bounded_array.h"
#include "coordinate.h"
#include "coordinate_transformation_front_radar_track.h"
#include "coordinate_transformation_front_vision_lane.h"
#include "coordinate_transformation_front_vision_track.h"
#include "correction.h"
#include "filter_in_vehicle_sensor.h"
#include "gating.h"
#include "inv.h"
#include "motion_attribute.h"
#include "pedestrian_recognition.h"
#include "prediction.h"
#include "road_curvature.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "shape_attribute.h"
#include "sort.h"
#include "sortIdx.h"
#include "tracking.h"
#include "track_management.h"
#include "unit_conversion_data.h"
#include "unit_conversion_front_radar_track.h"
#include "unit_conversion_front_vision_lane.h"
#include "unit_conversion_front_vision_track.h"
#include "unit_conversion.h"
#include "unit_conversion_initialize.h"
#include "unit_conversion_in_vehicle_sensor.h"
#include "unit_conversion_terminate.h"
#include "vehicle_recognition.h"




#define RUN_THREAD ( (1<<(11)) - 1 )

#define IVS 0x01 // 1

#define FVT1 (1<<(1)) // 2
#define FVT2 (1<<(2)) // 4
#define FVT3 (1<<(3)) // 8
#define FVT4 (1<<(4)) // 16

#define FVLR (1<<(5)) // 32
#define FVLL (1<<(6)) // 64

#define FRT1 (1<<(7)) // 128
#define FRT2 (1<<(8)) // 256
#define FRT3 (1<<(9)) // 512
#define FRT4 (1<<(10)) // 1024
