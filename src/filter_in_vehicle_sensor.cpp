//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: filter_in_vehicle_sensor.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "filter_in_vehicle_sensor.h"
#include "rt_nonfinite.h"

// Variable Definitions
static double Old_Lat_Acc;

static double Old_Long_Acc;

static double Old_Yaw_Rate;

static double Old_Steering_Angle;

static double Old_Steering_Speed;

static double Old_Vehicle_Speed;

// Function Definitions
//
// Arguments    : double In_Vehicle_Sensor[19]
// Return Type  : void
//
void filter_in_vehicle_sensor(double In_Vehicle_Sensor[19])
{
  // --------------------------------------------------------------------------
  //  In_Vehicle_Sensor_out : [19 X 1]     Input, Output
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
  //  Low Pass Filter
  Old_Lat_Acc = 0.7 * In_Vehicle_Sensor[9] + 0.3 * Old_Lat_Acc;
  Old_Long_Acc = 0.7 * In_Vehicle_Sensor[10] + 0.3 * Old_Long_Acc;
  Old_Yaw_Rate = In_Vehicle_Sensor[17] + 0.0 * Old_Yaw_Rate;
  //  실제 동작
  Old_Steering_Angle = In_Vehicle_Sensor[11] + 0.0 * Old_Steering_Angle;
  //  실제 동작
  Old_Steering_Speed = In_Vehicle_Sensor[12] + 0.0 * Old_Steering_Speed;
  Old_Vehicle_Speed = In_Vehicle_Sensor[18] + 0.0 * Old_Vehicle_Speed;
  //  Offset
  In_Vehicle_Sensor[9] = Old_Lat_Acc;
  In_Vehicle_Sensor[10] = Old_Long_Acc;
  In_Vehicle_Sensor[17] = Old_Yaw_Rate;
  In_Vehicle_Sensor[11] = Old_Steering_Angle;
  In_Vehicle_Sensor[12] = Old_Steering_Speed;
  In_Vehicle_Sensor[18] = Old_Vehicle_Speed;
}

//
// Arguments    : void
// Return Type  : void
//
void filter_in_vehicle_sensor_init()
{
  Old_Lat_Acc = 0.0;
  Old_Long_Acc = 0.0;
  Old_Yaw_Rate = 0.0;
  Old_Steering_Angle = 0.0;
  Old_Steering_Speed = 0.0;
  Old_Vehicle_Speed = 0.0;
}

//
// File trailer for filter_in_vehicle_sensor.cpp
//
// [EOF]
//
