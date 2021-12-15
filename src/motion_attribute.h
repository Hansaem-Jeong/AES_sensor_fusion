//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: motion_attribute.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef MOTION_ATTRIBUTE_H
#define MOTION_ATTRIBUTE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void motion_attribute(const double In_Vehicle_Sensor[19],
                             const double Front_Vision_Track[360],
                             const double Front_Radar_Track[544],
                             float Road_Curvature, float Road_Slope,
                             double Front_Vision_Track_out[360],
                             double Front_Radar_Track_out[544]);

#endif
//
// File trailer for motion_attribute.h
//
// [EOF]
//
