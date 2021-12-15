//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: coordinate.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "coordinate.h"
#include "coordinate_transformation_front_radar_track.h"
#include "coordinate_transformation_front_vision_lane.h"
#include "coordinate_transformation_front_vision_track.h"
#include "filter_in_vehicle_sensor.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : const double In_Vehicle_Sensor[19]
//                const double Front_Vision_Track[360]
//                const double Front_Vision_Lane[68]
//                const double Front_Radar_Track[544]
//                double In_Vehicle_Sensor_out[19]
//                double Front_Vision_Track_out[360]
//                double Front_Vision_Lane_out[68]
//                double Front_Radar_Track_out[544]
// Return Type  : void
//
void coordinate(
    const double In_Vehicle_Sensor[19], const double Front_Vision_Track[360],
    const double Front_Vision_Lane[68], const double Front_Radar_Track[544],
    double In_Vehicle_Sensor_out[19], double Front_Vision_Track_out[360],
    double Front_Vision_Lane_out[68], double Front_Radar_Track_out[544])
{
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  std::copy(&In_Vehicle_Sensor[0], &In_Vehicle_Sensor[19],
            &In_Vehicle_Sensor_out[0]);
  filter_in_vehicle_sensor(In_Vehicle_Sensor_out);
  coordinate_transformation_front_vision_track(
      Front_Vision_Track, In_Vehicle_Sensor, Front_Vision_Track_out);
  coordinate_transformation_front_vision_lane(Front_Vision_Lane,
                                              Front_Vision_Lane_out);
  std::copy(&Front_Radar_Track[0], &Front_Radar_Track[544],
            &Front_Radar_Track_out[0]);
  coordinate_transformation_front_radar_track(Front_Radar_Track_out);
}

//
// File trailer for coordinate.cpp
//
// [EOF]
//
