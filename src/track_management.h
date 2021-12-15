//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: track_management.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef TRACK_MANAGEMENT_H
#define TRACK_MANAGEMENT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void track_management(const double Fusion_Track_Updated[1280],
                             const double P_Fusion_Track_Updated[1024],
                             const double Association_Map_Updated[128],
                             const double Association_Map[128],
                             const double Fusion_Object[128],
                             float Road_Curvature, float Road_Slope,
                             const double Front_Vision_Lane[68],
                             double Fusion_Track_out[1280],
                             double Association_Map_out[128],
                             double P_Fusion_Track_out[1024]);

#endif
//
// File trailer for track_management.h
//
// [EOF]
//
