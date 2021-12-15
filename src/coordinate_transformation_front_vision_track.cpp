//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: coordinate_transformation_front_vision_track.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "coordinate_transformation_front_vision_track.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include <algorithm>
#include <cmath>

// Function Declarations
static double rt_atan2d_snf(double u0, double u1);

// Function Definitions
//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int b_u0;
    int b_u1;
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }
    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }
    y = std::atan2(static_cast<double>(b_u0), static_cast<double>(b_u1));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }
  return y;
}

//
// Arguments    : const double Front_Vision_Track[360]
//                const double In_Vehicle_Sensor[19]
//                double Front_Vision_Track_out[360]
// Return Type  : void
//
void coordinate_transformation_front_vision_track(
    const double Front_Vision_Track[360], const double In_Vehicle_Sensor[19],
    double Front_Vision_Track_out[360])
{
  // --------------------------------------------------------------------------
  //  Front_Vision_Track : [39 X 10]     Input
  // --------------------------------------------------------------------------
  //  1  : Classification
  //  2  : Rel_POS_X
  //  3  : Motion Category
  //  4  : Rel_POS_Y
  //  5  : Absolute Velocity X
  //  6  : Absolute Velocity Y
  //  7  : ID
  //  8  : Predicted Object
  //  9  : Angle Right
  //  10 : Motion Status
  //  11 : Angle Left
  //  12 : Motion Orientation
  //  13 : Angle Rate
  //  14 : Rel_ACC_X
  //  15 : Lane Assign
  //  16 : Length
  //  17 : Brake Light
  //  18 : Width
  //  19 : Alive Age
  //  20 : Turn Signal Left
  //  21 : Turn Signal Right
  //  22 : Heading Angle
  //  23 : Height
  //  24 : Side
  //  25 : Preprocessing(Coordinate Transform) Rel_POS_Y
  //  26 : Preprocessing(Coordinate Transform) Rel_POS_X
  //  27 : Absolute Velocity Y
  //  28 : Absolute Velocity X
  //  29 : Preprocessing Rel_ACC_X
  //  30 : Preprocessing(Unit Conversion) Heading Anlge
  //  31 : -
  //  32 : -
  //  33 : -
  //  34 : -
  //  35 : -
  //  36 : -
  //  37 : -
  //  38 : -
  //  39 : -
  // --------------------------------------------------------------------------
  //  In_Vehicle_Sensor_out : [19 X 1]     Input
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
  //  Front_Vision_Track_out : [36 X 10]     Output
  // --------------------------------------------------------------------------
  //  1  : Classification
  //  2  : Rel_POS_X
  //  3  : Motion Category
  //  4  : Rel_POS_Y
  //  5  : Absolute Velocity X
  //  6  : Absolute Velocity Y
  //  7  : ID
  //  8  : Predicted Object
  //  9  : Angle Right
  //  10 : Motion Status
  //  11 : Angle Left
  //  12 : Motion Orientation
  //  13 : Angle Rate
  //  14 : Rel_ACC_X
  //  15 : Lane Assign
  //  16 : Length
  //  17 : Brake Light
  //  18 : Width
  //  19 : Alive Age
  //  20 : Turn Signal Left
  //  21 : Turn Signal Right
  //  22 : Heading Angle
  //  23 : Height
  //  24 : Side
  //  25 : Preprocessing(Coordinate Transform) Rel_POS_Y
  //  26 : Preprocessing(Coordinate Transform) Rel_POS_X
  //  27 : Preprocessing Relative Velocity Y
  //  28 : Preprocessing Relative Velocity X
  //  29 : Preprocessing Rel_ACC_X
  //  30 : Preprocessing(Unit Conversion) Heading Anlge
  //  31 : Range
  //  32 : Angle
  //  33 : -
  //  34 : -
  //  35 : -
  //  36 : -
  // --------------------------------------------------------------------------
  //  Coordinate Transform
  // --------------------------------------------------------------------------
  std::copy(&Front_Vision_Track[0], &Front_Vision_Track[360],
            &Front_Vision_Track_out[0]);
  for (int index_FVT{0}; index_FVT < 10; index_FVT++) {
    if (Front_Vision_Track[6] != 0.0) {
      double d_Front_Vision_Track_out_tmp;
      double e_Front_Vision_Track_out_tmp;
      int Front_Vision_Track_out_tmp;
      int b_Front_Vision_Track_out_tmp;
      int c_Front_Vision_Track_out_tmp;
      Front_Vision_Track_out_tmp = 36 * index_FVT + 25;
      Front_Vision_Track_out[Front_Vision_Track_out_tmp] =
          Front_Vision_Track[36 * index_FVT + 1] + 0.8;
      b_Front_Vision_Track_out_tmp = 36 * index_FVT + 24;
      Front_Vision_Track_out[b_Front_Vision_Track_out_tmp] =
          -Front_Vision_Track[36 * index_FVT + 3];
      Front_Vision_Track_out[36 * index_FVT + 27] =
          Front_Vision_Track[36 * index_FVT + 4] - In_Vehicle_Sensor[18];
      Front_Vision_Track_out[36 * index_FVT + 26] =
          -Front_Vision_Track[36 * index_FVT + 5];
      Front_Vision_Track_out[36 * index_FVT + 28] =
          Front_Vision_Track[36 * index_FVT + 13];
      c_Front_Vision_Track_out_tmp = 36 * index_FVT + 29;
      Front_Vision_Track_out[c_Front_Vision_Track_out_tmp] =
          Front_Vision_Track[c_Front_Vision_Track_out_tmp];
      d_Front_Vision_Track_out_tmp =
          Front_Vision_Track_out[Front_Vision_Track_out_tmp];
      e_Front_Vision_Track_out_tmp =
          Front_Vision_Track_out[b_Front_Vision_Track_out_tmp];
      Front_Vision_Track_out[36 * index_FVT + 30] = std::sqrt(
          d_Front_Vision_Track_out_tmp * d_Front_Vision_Track_out_tmp +
          e_Front_Vision_Track_out_tmp * e_Front_Vision_Track_out_tmp);
      Front_Vision_Track_out[36 * index_FVT + 31] =
          rt_atan2d_snf(Front_Vision_Track_out[b_Front_Vision_Track_out_tmp],
                        Front_Vision_Track_out[Front_Vision_Track_out_tmp]);
    }
  }
}

//
// File trailer for coordinate_transformation_front_vision_track.cpp
//
// [EOF]
//
