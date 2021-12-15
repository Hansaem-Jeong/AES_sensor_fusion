//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortIdx.h
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

#ifndef SORTIDX_H
#define SORTIDX_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
void b_merge(int idx[5], double x[5], int offset, int np, int nq, int iwork[5],
             double xwork[5]);

void c_merge(int idx[64], double x[64], int offset, int np, int nq,
             int iwork[64], double xwork[64]);

void merge(int idx_data[], double x_data[], int offset, int np, int nq,
           int iwork_data[], double xwork_data[]);

} // namespace internal
} // namespace coder

#endif
//
// File trailer for sortIdx.h
//
// [EOF]
//
