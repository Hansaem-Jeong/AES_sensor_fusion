//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: tracking.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "tracking.h"
#include "correction.h"
#include "prediction.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"

// Function Definitions
//
// Arguments    : const double Association_Map_k_1[128]
//                const double Fusion_Track_k_1[1280]
//                const double P_Fusion_Track_k_1[1024]
//                const double Fusion_Object[768]
//                const double Association_Map[128]
//                double Fusion_Track_Updated[1280]
//                double P_Fusion_Track_Updated[1024]
//                double Association_Map_Updated[128]
// Return Type  : void
//
void tracking(
    const double Association_Map_k_1[128], const double Fusion_Track_k_1[1280],
    const double P_Fusion_Track_k_1[1024], const double Fusion_Object[768],
    const double Association_Map[128], double Fusion_Track_Updated[1280],
    double P_Fusion_Track_Updated[1024], double Association_Map_Updated[128])
{
  double Fusion_Track_Predicted[1280];
  double P_Fusion_Track_Predicted[1024];
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  prediction(Association_Map_k_1, Fusion_Track_k_1, P_Fusion_Track_k_1,
             Fusion_Track_Predicted, P_Fusion_Track_Predicted);
  correction(Fusion_Object, Association_Map, Association_Map_k_1,
             Fusion_Track_Predicted, P_Fusion_Track_Predicted,
             Fusion_Track_Updated, P_Fusion_Track_Updated,
             Association_Map_Updated);
}

//
// File trailer for tracking.cpp
//
// [EOF]
//
