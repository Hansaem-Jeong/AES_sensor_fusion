//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: coordinate_transformation_front_vision_lane.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "coordinate_transformation_front_vision_lane.h"
#include "rt_nonfinite.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : const double Front_Vision_Lane[68]
//                double Front_Vision_Lane_out[68]
// Return Type  : void
//
void coordinate_transformation_front_vision_lane(
    const double Front_Vision_Lane[68], double Front_Vision_Lane_out[68])
{
  // --------------------------------------------------------------------------
  //  Front_Vision_Lane : [34 X 2(Left, Right)]     Input
  // --------------------------------------------------------------------------
  //  1  : View Start Longitudinal Distance
  //  2  : View End Longitudinal Distance
  //  3  : Lane Mark Confidence h
  //  4  : Lane Mark Confidence n
  //  5  : Lane Prediction
  //  6  : Neighbor Avail
  //  7  : Neighbor Type
  //  8  : Guardrail
  //  9  : Highway Merge
  //  10  : Highway Exit
  //  11 : Lane Color
  //  12 : View Range Start Point
  //  13 : Neighbor Distance [m]
  //  14 : Neighbor Road Slope [rad]
  //  15 : Neighbor Curvature [1/m]
  //  16 : Neighbor Curvature Rate [1/m^2]
  //  17 : Classification
  //  18 : Confidence
  //  19 : Marker Width
  //  20 : Distance [m]
  //  21 : Road Slope [rad]
  //  22 : Curvature [1/m]
  //  23 : Curvature Rate [1/m^2]
  //  24 : Consturction Area
  //  25 : LDW Availability
  //  26 : LDW Status
  //  27 : -
  //  28 : -
  //  29 : -
  //  30 : -
  //  31 : -
  //  32 : -
  //  33 : -
  //  34 : -
  // --------------------------------------------------------------------------
  //  Front_Vision_Lane_out : [34 X 2(Left, Right)]     Output
  // --------------------------------------------------------------------------
  //  1  : View Start Longitudinal Distance
  //  2  : View End Longitudinal Distance
  //  3  : Lane Mark Confidence h
  //  4  : Lane Mark Confidence n
  //  5  : Lane Prediction
  //  6  : Neighbor Avail
  //  7  : Neighbor Type
  //  8  : Guardrail
  //  9  : Highway Merge
  //  10  : Highway Exit
  //  11 : Lane Color
  //  12 : View Range Start Point
  //  13 : Neighbor Distance [m]
  //  14 : Neighbor Road Slope [rad]
  //  15 : Neighbor Curvature [1/m]
  //  16 : Neighbor Curvature Rate [1/m^2]
  //  17 : Classification
  //  18 : Confidence
  //  19 : Marker Width
  //  20 : Distance [m]
  //  21 : Road Slope [rad]
  //  22 : Curvature [1/m]
  //  23 : Curvature Rate [1/m^2]
  //  24 : Consturction Area
  //  25 : LDW Availability
  //  26 : LDW Status
  //  27 : Preprocessing(Coordinate Transform) Distance
  //  28 : Preprocessing(Coordinate Transform) Road Slope
  //  29 : Preprocessing(Coordinate Transform) Curvature
  //  30 : Preprocessing(Coordinate Transform) Curvature Rate
  //  31 : Preprocessing(Coordinate Transform) Next Distance
  //  32 : Preprocessing(Coordinate Transform) Next Road Slope
  //  33 : Preprocessing(Coordinate Transform) Next Curvature
  //  34 : Preprocessing(Coordinate Transform) Next Curvature Rate
  // --------------------------------------------------------------------------
  //  Coordinate Transform
  // --------------------------------------------------------------------------
  std::copy(&Front_Vision_Lane[0], &Front_Vision_Lane[68],
            &Front_Vision_Lane_out[0]);
  //  left lane
  Front_Vision_Lane_out[26] = -Front_Vision_Lane[19];
  Front_Vision_Lane_out[27] = -Front_Vision_Lane[20];
  Front_Vision_Lane_out[28] = Front_Vision_Lane[21] * -2.0;
  Front_Vision_Lane_out[29] = Front_Vision_Lane[22] * -6.0;
  Front_Vision_Lane_out[30] = -Front_Vision_Lane[12];
  Front_Vision_Lane_out[31] = -Front_Vision_Lane[13];
  Front_Vision_Lane_out[32] = Front_Vision_Lane[14] * -2.0;
  Front_Vision_Lane_out[33] = Front_Vision_Lane[15] * -6.0;
  //  right lane
  Front_Vision_Lane_out[60] = -Front_Vision_Lane[53];
  Front_Vision_Lane_out[61] = -Front_Vision_Lane[54];
  Front_Vision_Lane_out[62] = Front_Vision_Lane[55] * -2.0;
  Front_Vision_Lane_out[63] = Front_Vision_Lane[56] * -6.0;
  Front_Vision_Lane_out[64] = -Front_Vision_Lane[46];
  Front_Vision_Lane_out[65] = -Front_Vision_Lane[54];
  Front_Vision_Lane_out[66] = Front_Vision_Lane[48] * -2.0;
  Front_Vision_Lane_out[67] = Front_Vision_Lane[49] * -6.0;
}

//
// File trailer for coordinate_transformation_front_vision_lane.cpp
//
// [EOF]
//
