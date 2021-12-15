//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sortIdx.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "sortIdx.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : int idx[5]
//                double x[5]
//                int offset
//                int np
//                int nq
//                int iwork[5]
//                double xwork[5]
// Return Type  : void
//
namespace coder {
namespace internal {
void b_merge(int idx[5], double x[5], int offset, int np, int nq, int iwork[5],
             double xwork[5])
{
  if (nq != 0) {
    int i;
    int iout;
    int j;
    int n_tmp;
    int p;
    n_tmp = np + nq;
    for (j = 0; j < n_tmp; j++) {
      i = offset + j;
      iwork[j] = idx[i];
      xwork[j] = x[i];
    }
    p = 0;
    iout = offset - 1;
    int exitg1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork[p] <= xwork[4]) {
        idx[iout] = iwork[p];
        x[iout] = xwork[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx[iout] = iwork[4];
        x[iout] = xwork[4];
        if (5 >= n_tmp) {
          iout -= p;
          for (j = p + 1; j <= np; j++) {
            i = iout + j;
            idx[i] = iwork[j - 1];
            x[i] = xwork[j - 1];
          }
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : int idx[64]
//                double x[64]
//                int offset
//                int np
//                int nq
//                int iwork[64]
//                double xwork[64]
// Return Type  : void
//
void c_merge(int idx[64], double x[64], int offset, int np, int nq,
             int iwork[64], double xwork[64])
{
  if (nq != 0) {
    int iout;
    int j;
    int n_tmp;
    int p;
    int q;
    n_tmp = np + nq;
    for (j = 0; j < n_tmp; j++) {
      iout = offset + j;
      iwork[j] = idx[iout];
      xwork[j] = x[iout];
    }
    p = 0;
    q = np;
    iout = offset - 1;
    int exitg1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork[p] <= xwork[q]) {
        idx[iout] = iwork[p];
        x[iout] = xwork[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx[iout] = iwork[q];
        x[iout] = xwork[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (j = p + 1; j <= np; j++) {
            iout = q + j;
            idx[iout] = iwork[j - 1];
            x[iout] = xwork[j - 1];
          }
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

//
// Arguments    : int idx_data[]
//                double x_data[]
//                int offset
//                int np
//                int nq
//                int iwork_data[]
//                double xwork_data[]
// Return Type  : void
//
void merge(int idx_data[], double x_data[], int offset, int np, int nq,
           int iwork_data[], double xwork_data[])
{
  if (nq != 0) {
    int iout;
    int j;
    int n_tmp;
    int p;
    int q;
    n_tmp = np + nq;
    for (j = 0; j < n_tmp; j++) {
      iout = offset + j;
      iwork_data[j] = idx_data[iout];
      xwork_data[j] = x_data[iout];
    }
    p = 0;
    q = np;
    iout = offset - 1;
    int exitg1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork_data[p] <= xwork_data[q]) {
        idx_data[iout] = iwork_data[p];
        x_data[iout] = xwork_data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx_data[iout] = iwork_data[q];
        x_data[iout] = xwork_data[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (j = p + 1; j <= np; j++) {
            iout = q + j;
            idx_data[iout] = iwork_data[j - 1];
            x_data[iout] = xwork_data[j - 1];
          }
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for sortIdx.cpp
//
// [EOF]
//
