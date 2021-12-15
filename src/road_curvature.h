//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: road_curvature.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef ROAD_CURVATURE_H
#define ROAD_CURVATURE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void road_curvature(const double Front_Vision_Lane[68],
                           const double In_Vehicle_Sensor[19],
                           double *Road_Curvature, double *Road_Slope);

#endif
//
// File trailer for road_curvature.h
//
// [EOF]
//
