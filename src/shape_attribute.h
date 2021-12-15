//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: shape_attribute.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef SHAPE_ATTRIBUTE_H
#define SHAPE_ATTRIBUTE_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void shape_attribute(const double Fusion_Object[768],
                            const double Old_Fusion_Track_Candidate[768],
                            const double Association_Map[128],
                            const double Front_Vision_Track[360],
                            const double Old_Shape[320],
                            double Fusion_Object_out[768],
                            double Shape_ID[320]);

#endif
//
// File trailer for shape_attribute.h
//
// [EOF]
//
