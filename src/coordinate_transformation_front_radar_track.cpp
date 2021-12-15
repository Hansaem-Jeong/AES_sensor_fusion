//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: coordinate_transformation_front_radar_track.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "coordinate_transformation_front_radar_track.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : double Front_Radar_Track[544]
// Return Type  : void
//
void coordinate_transformation_front_radar_track(double Front_Radar_Track[544])
{
  // --------------------------------------------------------------------------
  //  Front_Radar_Track : [17 X 32]     Input
  // --------------------------------------------------------------------------
  //  1  : Angle
  //  2  : Range
  //  3  : Range Acceleration
  //  4  : Range Rate
  //  5  : Track Status
  //  6  : Width
  //  7  : (Unit conversion) Angle
  //  8  : -
  //  9  : -
  //  10 : -
  //  11 : -
  //  12 : -
  //  13 : -
  //  14 : -
  //  15 : -
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
  //  14 : -
  //  15 : -
  //  16 : -
  //  17 : -
  // --------------------------------------------------------------------------
  //  Coordinate Transform
  // --------------------------------------------------------------------------
  for (int k{0}; k < 32; k++) {
    int i;
    int i1;
    i = 17 * k + 6;
    Front_Radar_Track[i] = -Front_Radar_Track[i];
    i1 = 17 * k + 1;
    Front_Radar_Track[17 * k + 7] =
        std::cos(Front_Radar_Track[i]) * Front_Radar_Track[i1];
    Front_Radar_Track[17 * k + 8] =
        std::sin(Front_Radar_Track[i]) * Front_Radar_Track[i1];
    i1 = 17 * k + 3;
    Front_Radar_Track[17 * k + 9] =
        std::cos(Front_Radar_Track[i]) * Front_Radar_Track[i1];
    Front_Radar_Track[17 * k + 10] =
        std::sin(Front_Radar_Track[i]) * Front_Radar_Track[i1];
    i1 = 17 * k + 2;
    Front_Radar_Track[17 * k + 11] =
        std::cos(Front_Radar_Track[i]) * Front_Radar_Track[i1];
    Front_Radar_Track[17 * k + 12] =
        std::sin(Front_Radar_Track[i]) * Front_Radar_Track[i1];
  }
}

//
// File trailer for coordinate_transformation_front_radar_track.cpp
//
// [EOF]
//
