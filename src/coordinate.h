//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: coordinate.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef COORDINATE_H
#define COORDINATE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void coordinate(
    const double In_Vehicle_Sensor[19], const double Front_Vision_Track[360],
    const double Front_Vision_Lane[68], const double Front_Radar_Track[544],
    double In_Vehicle_Sensor_out[19], double Front_Vision_Track_out[360],
    double Front_Vision_Lane_out[68], double Front_Radar_Track_out[544]);

#endif
//
// File trailer for coordinate.h
//
// [EOF]
//
