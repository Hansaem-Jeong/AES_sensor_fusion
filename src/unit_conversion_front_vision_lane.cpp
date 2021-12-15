//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unit_conversion_front_vision_lane.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "unit_conversion_front_vision_lane.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const double Front_Vision_Lane[52]
//                double Front_Vision_Lane_out[68]
// Return Type  : void
//
void unit_conversion_front_vision_lane(const double Front_Vision_Lane[52],
                                       double Front_Vision_Lane_out[68])
{
  // --------------------------------------------------------------------------
  //  Front_Vision_Lane : [26 X 2(Left, Right)]     Input
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
  //  27 : -
  //  28 : -
  //  29 : -
  //  30 : -
  //  31 : -
  //  32 : -
  //  33 : -
  //  34 : -
  // --------------------------------------------------------------------------
  //  initialization
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Unit Conversion
  // --------------------------------------------------------------------------
  for (int i{0}; i < 26; i++) {
    Front_Vision_Lane_out[i] = Front_Vision_Lane[i];
    Front_Vision_Lane_out[i + 34] = Front_Vision_Lane[i + 26];
  }
}

//
// File trailer for unit_conversion_front_vision_lane.cpp
//
// [EOF]
//
