//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: vehicle_recognition.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef VEHICLE_RECOGNITION_H
#define VEHICLE_RECOGNITION_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void vehicle_recognition(
    const double Fusion_Track[1280], const double Association_Map_out[128],
    float Road_Curvature, const double old_rear_object_lane[64],
    const double old_object_lane_total[64],
    double Fusion_Track_Recognition[1408], double AVL[9], double AVR[9],
    double RVL[9], double RVI[9], double RVR[9], double FVL[9], double FVI[9],
    double FVR[9], double rear_object_lane[64], double object_lane_total[64]);

#endif
//
// File trailer for vehicle_recognition.h
//
// [EOF]
//
