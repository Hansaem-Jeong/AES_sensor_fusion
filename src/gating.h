//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gating.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef GATING_H
#define GATING_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void gating(const double Front_Vision_Track[360],
                   const double Front_Radar_Track[544],
                   double Fusion_Object[768], double Association_Map[128]);

#endif
//
// File trailer for gating.h
//
// [EOF]
//
