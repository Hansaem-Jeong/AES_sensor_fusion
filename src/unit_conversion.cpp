//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unit_conversion.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "unit_conversion.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_front_radar_track.h"
#include "unit_conversion_front_vision_lane.h"
#include "unit_conversion_front_vision_track.h"
#include "unit_conversion_in_vehicle_sensor.h"
#include "unit_conversion_initialize.h"

// Function Definitions
//
// Arguments    : const double In_Vehicle_Sensor[9]
//                const double Front_Vision_Track[240]
//                const double Front_Vision_Lane[52]
//                const double Front_Radar_Track[192]
//                double In_Vehicle_Sensor_out[19]
//                double Front_Vision_Track_out[360]
//                double Front_Vision_Lane_out[68]
//                double Front_Radar_Track_out[544]
// Return Type  : void
//
void unit_conversion(
    const double In_Vehicle_Sensor[9], const double Front_Vision_Track[240],
    const double Front_Vision_Lane[52], const double Front_Radar_Track[192],
    double In_Vehicle_Sensor_out[19], double Front_Vision_Track_out[360],
    double Front_Vision_Lane_out[68], double Front_Radar_Track_out[544])
{
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  unit_conversion_in_vehicle_sensor(In_Vehicle_Sensor, In_Vehicle_Sensor_out);
  unit_conversion_front_vision_track(Front_Vision_Track,
                                     Front_Vision_Track_out);
  unit_conversion_front_vision_lane(Front_Vision_Lane, Front_Vision_Lane_out);
  unit_conversion_front_radar_track(Front_Radar_Track, Front_Radar_Track_out);
}

//
// File trailer for unit_conversion.cpp
//
// [EOF]
//
