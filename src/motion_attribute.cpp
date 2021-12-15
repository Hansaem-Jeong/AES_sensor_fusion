//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: motion_attribute.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "motion_attribute.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// Arguments    : const double In_Vehicle_Sensor[19]
//                const double Front_Vision_Track[360]
//                const double Front_Radar_Track[544]
//                float Road_Curvature
//                float Road_Slope
//                double Front_Vision_Track_out[360]
//                double Front_Radar_Track_out[544]
// Return Type  : void
//
void motion_attribute(const double In_Vehicle_Sensor[19],
                      const double Front_Vision_Track[360],
                      const double Front_Radar_Track[544], float Road_Curvature,
                      float, double Front_Vision_Track_out[360],
                      double Front_Radar_Track_out[544])
{
  double VELOCITY_THRESHOLD;
  double Vehicle_Speed;
  double Yaw_Rate;
  double d;
  double d1;
  int Front_Vision_Track_out_tmp;
  int index_FVT;
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  // --------------------------------------------------------------------------
  //  Front_Vision_Track : [36 X 10]     Input
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
  //  Front_Vision_Track_out : [36 X 10]     Output
  // --------------------------------------------------------------------------
  //  1  : ID
  //  2  : Rel_POS_Y
  //  3  : Rel_POS_X
  //  4  : Rel_VEL_Y
  //  5  : Absolute Velocity X
  //  6  : Absolute Velocity Y
  //  7  : Length
  //  8  : Width
  //  9  : Height
  //  10 : Heading Angle
  //  11 : Classification
  //  12 : Angle Left
  //  13 : Angle Rate
  //  14 : Angle Right
  //  15 : Brake Light
  //  16 : Lane Assign
  //  17 : Motion Category
  //  18 : Motion Orientation
  //  19 : Motion Status
  //  20 : Alive Age
  //  21 : Side
  //  22 : Predicted Object
  //  23 : Turn Signal Left
  //  24 : Turn Signal Right
  //  25 : Preprocessing(Coordinate Transform) Rel_POS_Y
  //  26 : Preprocessing(Coordinate Transform) Rel_POS_X
  //  27 : Preprocessing Relative Velocity Y
  //  28 : Preprocessing Relative Velocity X
  //  29 : Preprocessing Rel_ACC_X
  //  30 : Preprocessing(Unit Conversion) Heading Anlge
  //  31 : Range
  //  32 : Angle
  //  33 : Absolute Velocity
  //  34 : Absolute Velocity X in Motion Attribute
  //  35 : Absolute Velocity Y in Motion Attribute
  //  36 : Motion Attribute
  // --------------------------------------------------------------------------
  //  Front_Radar_Track : [17 X 32]     Input
  // --------------------------------------------------------------------------
  //  1  : Angle
  //  2  : Range
  //  3  : Range Acceleration
  //  4  : Range Rate
  //  5  : Track Status
  //  6  : Width
  //  7  : (Unit conversion, Coordinate transform) Angle
  //  8  : Relative Position X
  //  9  : Relative Position Y
  //  10 : Relative Velocity X
  //  11 : Relative Velocity Y
  //  12 : Relative Acceleration X
  //  13 : Relative Acceleration Y
  //  14 : Preprocessing Creation Flag (not working)
  //  15 : Preprocessing Association Flag (not working)
  //  16 : -
  //  17 : -
  // --------------------------------------------------------------------------
  //  Front_Radar_Track_out : [17 X 32]     Output
  // --------------------------------------------------------------------------
  //  1  : Angle
  //  2  : Range
  //  3  : Range Acceleration
  //  4  : Range Rate
  //  5  : Track Status
  //  6  : Width
  //  7  : (Unit conversion, Coordinate transform) Angle
  //  8  : Relative Position X
  //  9  : Relative Position Y
  //  10 : Relative Velocity X
  //  11 : Relative Velocity Y
  //  12 : Relative Acceleration X
  //  13 : Relative Acceleration Y
  //  14 : Preprocessing Creation Flag (not working)
  //  15 : Preprocessing Association Flag (not working)
  //  16 : Absolute Velocity
  //  17 : Motion Attribute
  // --------------------------------------------------------------------------
  //  initialization
  // --------------------------------------------------------------------------
  std::copy(&Front_Vision_Track[0], &Front_Vision_Track[360],
            &Front_Vision_Track_out[0]);
  std::copy(&Front_Radar_Track[0], &Front_Radar_Track[544],
            &Front_Radar_Track_out[0]);
  Yaw_Rate = In_Vehicle_Sensor[17];
  Vehicle_Speed = In_Vehicle_Sensor[18];
  // --------------------------------------------------------------------------
  //  Parameter
  // --------------------------------------------------------------------------
  if (In_Vehicle_Sensor[18] > 5.5555555555555554) {
    VELOCITY_THRESHOLD = 3.5;
  } else {
    VELOCITY_THRESHOLD = 0.5;
  }
  // --------------------------------------------------------------------------
  //  Assign Motion Attribute to Front Vision Track
  // --------------------------------------------------------------------------
  for (index_FVT = 0; index_FVT < 10; index_FVT++) {
    d = Front_Vision_Track[36 * index_FVT + 24];
    d1 = Front_Vision_Track[36 * index_FVT + 25];
    if (d * d + d1 * d1 != 0.0) {
      d1 = std::abs(Road_Curvature);
      if (d1 < 0.0005) {
        //  straight road
        Front_Vision_Track_out_tmp = 36 * index_FVT + 32;
        Front_Vision_Track_out[Front_Vision_Track_out_tmp] =
            std::abs(Front_Vision_Track[36 * index_FVT + 27] + Vehicle_Speed);
        //  absolut speed(m/s)
        d = Front_Vision_Track_out[Front_Vision_Track_out_tmp];
        if (d < VELOCITY_THRESHOLD) {
          Front_Vision_Track_out[36 * index_FVT + 35] = 1.0;
          //  Front Camera motion = stationary
        } else if (d > VELOCITY_THRESHOLD) {
          Front_Vision_Track_out[36 * index_FVT + 35] = 2.0;
          //  Front Camera motion = dynamic
        }
      } else if (d1 >= 0.0005) {
        //  Curved road
        Front_Vision_Track_out_tmp = 36 * index_FVT + 32;
        Front_Vision_Track_out[Front_Vision_Track_out_tmp] =
            std::abs((Front_Vision_Track[36 * index_FVT + 27] + d * Yaw_Rate) +
                     Vehicle_Speed);
        //  absolut speed(m/s)
        d = Front_Vision_Track_out[Front_Vision_Track_out_tmp];
        if (d < VELOCITY_THRESHOLD) {
          Front_Vision_Track_out[36 * index_FVT + 35] = 1.0;
          //  Front Camera motion = stationary
        } else if (d > VELOCITY_THRESHOLD) {
          Front_Vision_Track_out[36 * index_FVT + 35] = 2.0;
          //  Front Camera motion = dynamic
        }
      }
    }
  }
  // --------------------------------------------------------------------------
  //  Assign Motion Attribute to Front Radar Track
  // --------------------------------------------------------------------------
  for (index_FVT = 0; index_FVT < 32; index_FVT++) {
    d = Front_Radar_Track[17 * index_FVT + 8];
    d1 = Front_Radar_Track[17 * index_FVT + 7];
    if (d * d + d1 * d1 != 0.0) {
      d1 = std::abs(Road_Curvature);
      if (d1 < 0.0005) {
        //  straight road
        Front_Vision_Track_out_tmp = 17 * index_FVT + 15;
        Front_Radar_Track_out[Front_Vision_Track_out_tmp] =
            std::abs(Front_Radar_Track[17 * index_FVT + 9] + Vehicle_Speed);
        //  absolut speed(m/s)
        d = Front_Radar_Track_out[Front_Vision_Track_out_tmp];
        if (d < VELOCITY_THRESHOLD) {
          Front_Radar_Track_out[17 * index_FVT + 16] = 1.0;
          //  Front Radar motion = stationary
        } else if (d > VELOCITY_THRESHOLD) {
          Front_Radar_Track_out[17 * index_FVT + 16] = 2.0;
          //  Front Radar motion = dynamic
        }
      } else if (d1 >= 0.0005) {
        //  Curved road
        Front_Vision_Track_out_tmp = 17 * index_FVT + 15;
        Front_Radar_Track_out[Front_Vision_Track_out_tmp] =
            std::abs((Front_Radar_Track[17 * index_FVT + 9] + d * Yaw_Rate) +
                     Vehicle_Speed);
        //  absolut speed(m/s)
        d = Front_Radar_Track_out[Front_Vision_Track_out_tmp];
        if (d < VELOCITY_THRESHOLD) {
          Front_Radar_Track_out[17 * index_FVT + 16] = 1.0;
          //  Front Radar motion = stationary
        } else if (d > VELOCITY_THRESHOLD) {
          Front_Radar_Track_out[17 * index_FVT + 16] = 2.0;
          //  Front Radar motion = dynamic
        }
      }
    }
  }
}

//
// File trailer for motion_attribute.cpp
//
// [EOF]
//
