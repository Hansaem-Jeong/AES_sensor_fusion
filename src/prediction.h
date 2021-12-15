//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: prediction.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef PREDICTION_H
#define PREDICTION_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void prediction(const double Association_Map_k_1[128],
                const double Fusion_Track_k_1[1280],
                const double P_Fusion_Track_k_1[1024],
                double Fusion_Track_Predicted[1280],
                double P_Fusion_Track_Predicted[1024]);

#endif
//
// File trailer for prediction.h
//
// [EOF]
//
