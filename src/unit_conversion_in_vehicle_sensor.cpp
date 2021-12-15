//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unit_conversion_in_vehicle_sensor.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "unit_conversion_in_vehicle_sensor.h"
#include "rt_nonfinite.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : const double In_Vehicle_Sensor[9]
//                double In_Vehicle_Sensor_out[19]
// Return Type  : void
//
void unit_conversion_in_vehicle_sensor(const double In_Vehicle_Sensor[9],
                                       double In_Vehicle_Sensor_out[19])
{
  // --------------------------------------------------------------------------
  //  In_Vehicle_Sensor : [9 X 1]     Input
  // --------------------------------------------------------------------------
  //  1  : Lateral Acceleration
  //  2  : Longitudinal Acceleration
  //  3  : Steering Angle
  //  4  : Steering Speed
  //  5  : Wheel Speed FL
  //  6  : Wheel Speed FR
  //  7  : Wheel Speed RL
  //  8  : Wheel Speed RR
  //  9  : Yawrate
  // --------------------------------------------------------------------------
  //  In_Vehicle_Sensor_out : [19 X 1]     Output
  // --------------------------------------------------------------------------
  //  1  : Lateral Acceleration
  //  2  : Longitudinal Acceleration
  //  3  : Steering Angle
  //  4  : Steering Speed
  //  5  : Wheel Speed FL
  //  6  : Wheel Speed FR
  //  7  : Wheel Speed RL
  //  8  : Wheel Speed RR
  //  9  : Yawrate
  //  10 : Preprocessing Lateral Acceleration
  //  11 : Preprocessing Longitudinal Acceleration
  //  12 : Preprocessing(Unit conversion) Steering Angle
  //  13 : Preprocessing(Unit conversion) Steering Speed
  //  14 : Preprocessing(Unit conversion) Wheel Speed FL
  //  15 : Preprocessing(Unit conversion) Wheel Speed FR
  //  16 : Preprocessing(Unit conversion) Wheel Speed RL
  //  17 : Preprocessing(Unit conversion) Wheel Speed RR
  //  18 : Preprocessing(Unit conversion) Yawrate
  //  19 : Preprocessing Vehicle Speed
  // --------------------------------------------------------------------------
  //  initialization
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Unit Conversion
  // --------------------------------------------------------------------------
  std::copy(&In_Vehicle_Sensor[0], &In_Vehicle_Sensor[9],
            &In_Vehicle_Sensor_out[0]);
  In_Vehicle_Sensor_out[9] = In_Vehicle_Sensor[0];
  In_Vehicle_Sensor_out[10] = In_Vehicle_Sensor[1];
  In_Vehicle_Sensor_out[11] = In_Vehicle_Sensor[2] * 0.017453292519943295;
  In_Vehicle_Sensor_out[12] = In_Vehicle_Sensor[3] * 0.017453292519943295;
  In_Vehicle_Sensor_out[13] = In_Vehicle_Sensor[4] * 0.27777777777777779;
  In_Vehicle_Sensor_out[14] = In_Vehicle_Sensor[5] * 0.27777777777777779;
  In_Vehicle_Sensor_out[15] = In_Vehicle_Sensor[6] * 0.27777777777777779;
  In_Vehicle_Sensor_out[16] = In_Vehicle_Sensor[7] * 0.27777777777777779;
  In_Vehicle_Sensor_out[17] = In_Vehicle_Sensor[8] * 0.017453292519943295;
  In_Vehicle_Sensor_out[18] =
      (In_Vehicle_Sensor_out[15] + In_Vehicle_Sensor_out[16]) / 2.0;
}

//
// File trailer for unit_conversion_in_vehicle_sensor.cpp
//
// [EOF]
//
