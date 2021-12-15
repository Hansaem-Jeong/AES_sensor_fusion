//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef SORT_H
#define SORT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void b_sort(double x_data[], int idx_data[], int *idx_size);

void b_sort(double x[64], int idx[64]);

void sort(double x_data[], int idx_data[], int idx_size[2]);

void sort(double x[5], int idx[5]);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for sort.h
//
// [EOF]
//
