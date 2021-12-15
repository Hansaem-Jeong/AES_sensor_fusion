//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unit_conversion_front_radar_track.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "unit_conversion_front_radar_track.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const double Front_Radar_Track[192]
//                double Front_Radar_Track_out[544]
// Return Type  : void
//
void unit_conversion_front_radar_track(const double Front_Radar_Track[192],
                                       double Front_Radar_Track_out[544])
{
  // --------------------------------------------------------------------------
  //  Front_Radar_Track : [6 X 32]     Input
  // --------------------------------------------------------------------------
  //  1  : Angle
  //  2  : Range
  //  3  : Range Acceleration
  //  4  : Range Rate
  //  5  : Track Status
  //  6  : Width
  // --------------------------------------------------------------------------
  //  Front_Radar_Track_out : [17 X 32]     Output
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
  //  initialization
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Unit Conversion
  // --------------------------------------------------------------------------
  for (int i{0}; i < 32; i++) {
    for (int i1{0}; i1 < 6; i1++) {
      Front_Radar_Track_out[i1 + 17 * i] = Front_Radar_Track[i1 + 6 * i];
    }
    Front_Radar_Track_out[17 * i + 6] =
        Front_Radar_Track[6 * i] * 0.017453292519943295;
  }
}

//
// File trailer for unit_conversion_front_radar_track.cpp
//
// [EOF]
//
