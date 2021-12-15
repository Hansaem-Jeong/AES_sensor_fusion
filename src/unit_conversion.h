//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unit_conversion.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef UNIT_CONVERSION_H
#define UNIT_CONVERSION_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void unit_conversion(
    const double In_Vehicle_Sensor[9], const double Front_Vision_Track[240],
    const double Front_Vision_Lane[52], const double Front_Radar_Track[192],
    double In_Vehicle_Sensor_out[19], double Front_Vision_Track_out[360],
    double Front_Vision_Lane_out[68], double Front_Radar_Track_out[544]);

#endif
//
// File trailer for unit_conversion.h
//
// [EOF]
//
