//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unit_conversion_front_vision_track.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "unit_conversion_front_vision_track.h"
#include "rt_nonfinite.h"
#include <algorithm>

// Function Definitions
//
// Arguments    : const double Front_Vision_Track[240]
//                double Front_Vision_Track_out[360]
// Return Type  : void
//
void unit_conversion_front_vision_track(const double Front_Vision_Track[240],
                                        double Front_Vision_Track_out[360])
{
  // --------------------------------------------------------------------------
  //  Front_Vision_Track : [24 X 10]     Input
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
  // --------------------------------------------------------------------------
  //  initialization
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Unit Conversion
  // --------------------------------------------------------------------------
  for (int i{0}; i < 10; i++) {
    std::copy(&Front_Vision_Track[i * 24],
              &Front_Vision_Track[static_cast<int>(i * 24 + 24U)],
              &Front_Vision_Track_out[i * 36]);
    Front_Vision_Track_out[36 * i + 29] = Front_Vision_Track[24 * i + 21];
  }
}

//
// File trailer for unit_conversion_front_vision_track.cpp
//
// [EOF]
//
