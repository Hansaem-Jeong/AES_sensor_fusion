//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: sort.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "sort.h"
#include "rt_nonfinite.h"
#include "sortIdx.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : double x_data[]
//                int idx_data[]
//                int *idx_size
// Return Type  : void
//
namespace coder {
namespace internal {
void b_sort(double x_data[], int idx_data[], int *idx_size)
{
  double vwork_data[64];
  double xwork_data[64];
  double x4[4];
  int iidx_data[64];
  int iwork_data[64];
  int i1;
  int i2;
  int i3;
  int ib;
  int k;
  int nNaNs;
  signed char idx4[4];
  signed char perm[4];
  *idx_size = 64;
  x4[0] = 0.0;
  idx4[0] = 0;
  x4[1] = 0.0;
  idx4[1] = 0;
  x4[2] = 0.0;
  idx4[2] = 0;
  x4[3] = 0.0;
  idx4[3] = 0;
  for (k = 0; k < 64; k++) {
    vwork_data[k] = x_data[k];
    iidx_data[k] = 0;
    iwork_data[k] = 0;
    xwork_data[k] = 0.0;
  }
  nNaNs = 0;
  ib = -1;
  for (k = 0; k < 64; k++) {
    if (std::isnan(vwork_data[k])) {
      iidx_data[63 - nNaNs] = k + 1;
      xwork_data[63 - nNaNs] = vwork_data[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib] = static_cast<signed char>(k + 1);
      x4[ib] = vwork_data[k];
      if (ib + 1 == 4) {
        double d;
        double d1;
        int i4;
        ib = k - nNaNs;
        if (x4[0] <= x4[1]) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }
        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }
        d = x4[i1 - 1];
        d1 = x4[i3 - 1];
        if (d <= d1) {
          d = x4[i2 - 1];
          if (d <= d1) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i2);
            perm[2] = static_cast<signed char>(i3);
            perm[3] = static_cast<signed char>(i4);
          } else if (d <= x4[i4 - 1]) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i2);
            perm[3] = static_cast<signed char>(i4);
          } else {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i4);
            perm[3] = static_cast<signed char>(i2);
          }
        } else {
          d1 = x4[i4 - 1];
          if (d <= d1) {
            if (x4[i2 - 1] <= d1) {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            perm[0] = static_cast<signed char>(i3);
            perm[1] = static_cast<signed char>(i4);
            perm[2] = static_cast<signed char>(i1);
            perm[3] = static_cast<signed char>(i2);
          }
        }
        iidx_data[ib - 3] = idx4[perm[0] - 1];
        iidx_data[ib - 2] = idx4[perm[1] - 1];
        iidx_data[ib - 1] = idx4[perm[2] - 1];
        iidx_data[ib] = idx4[perm[3] - 1];
        vwork_data[ib - 3] = x4[perm[0] - 1];
        vwork_data[ib - 2] = x4[perm[1] - 1];
        vwork_data[ib - 1] = x4[perm[2] - 1];
        vwork_data[ib] = x4[perm[3] - 1];
        ib = -1;
      }
    }
  }
  if (ib + 1 > 0) {
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    if (ib + 1 == 1) {
      perm[0] = 1;
    } else if (ib + 1 == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }
    for (k = 0; k <= ib; k++) {
      i2 = perm[k] - 1;
      i1 = ((k - nNaNs) - ib) + 63;
      iidx_data[i1] = idx4[i2];
      vwork_data[i1] = x4[i2];
    }
  }
  ib = (nNaNs >> 1) + 1;
  for (k = 0; k <= ib - 2; k++) {
    i2 = (k - nNaNs) + 64;
    i1 = iidx_data[i2];
    iidx_data[i2] = iidx_data[63 - k];
    iidx_data[63 - k] = i1;
    vwork_data[i2] = xwork_data[63 - k];
    vwork_data[63 - k] = xwork_data[i2];
  }
  if ((nNaNs & 1) != 0) {
    ib = (ib - nNaNs) + 63;
    vwork_data[ib] = xwork_data[ib];
  }
  if (64 - nNaNs > 1) {
    i3 = (64 - nNaNs) >> 2;
    i1 = 4;
    while (i3 > 1) {
      if ((i3 & 1) != 0) {
        i3--;
        ib = i1 * i3;
        i2 = 64 - (nNaNs + ib);
        if (i2 > i1) {
          merge(iidx_data, vwork_data, ib, i1, i2 - i1, iwork_data, xwork_data);
        }
      }
      ib = i1 << 1;
      i3 >>= 1;
      for (k = 0; k < i3; k++) {
        merge(iidx_data, vwork_data, k * ib, i1, i1, iwork_data, xwork_data);
      }
      i1 = ib;
    }
    if (64 - nNaNs > i1) {
      merge(iidx_data, vwork_data, 0, i1, 64 - (nNaNs + i1), iwork_data,
            xwork_data);
    }
  }
  std::copy(&vwork_data[0], &vwork_data[64], &x_data[0]);
  std::copy(&iidx_data[0], &iidx_data[64], &idx_data[0]);
}

//
// Arguments    : double x[64]
//                int idx[64]
// Return Type  : void
//
void b_sort(double x[64], int idx[64])
{
  double xwork[64];
  double x4[4];
  int iwork[64];
  int i1;
  int i2;
  int i3;
  int ib;
  int k;
  int nNaNs;
  signed char idx4[4];
  signed char perm[4];
  x4[0] = 0.0;
  idx4[0] = 0;
  x4[1] = 0.0;
  idx4[1] = 0;
  x4[2] = 0.0;
  idx4[2] = 0;
  x4[3] = 0.0;
  idx4[3] = 0;
  std::memset(&idx[0], 0, 64U * sizeof(int));
  std::memset(&xwork[0], 0, 64U * sizeof(double));
  nNaNs = 0;
  ib = 0;
  for (k = 0; k < 64; k++) {
    if (std::isnan(x[k])) {
      idx[63 - nNaNs] = k + 1;
      xwork[63 - nNaNs] = x[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = static_cast<signed char>(k + 1);
      x4[ib - 1] = x[k];
      if (ib == 4) {
        double d;
        double d1;
        int i4;
        ib = k - nNaNs;
        if (x4[0] <= x4[1]) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }
        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }
        d = x4[i1 - 1];
        d1 = x4[i3 - 1];
        if (d <= d1) {
          d = x4[i2 - 1];
          if (d <= d1) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i2);
            perm[2] = static_cast<signed char>(i3);
            perm[3] = static_cast<signed char>(i4);
          } else if (d <= x4[i4 - 1]) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i2);
            perm[3] = static_cast<signed char>(i4);
          } else {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i4);
            perm[3] = static_cast<signed char>(i2);
          }
        } else {
          d1 = x4[i4 - 1];
          if (d <= d1) {
            if (x4[i2 - 1] <= d1) {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            perm[0] = static_cast<signed char>(i3);
            perm[1] = static_cast<signed char>(i4);
            perm[2] = static_cast<signed char>(i1);
            perm[3] = static_cast<signed char>(i2);
          }
        }
        idx[ib - 3] = idx4[perm[0] - 1];
        idx[ib - 2] = idx4[perm[1] - 1];
        idx[ib - 1] = idx4[perm[2] - 1];
        idx[ib] = idx4[perm[3] - 1];
        x[ib - 3] = x4[perm[0] - 1];
        x[ib - 2] = x4[perm[1] - 1];
        x[ib - 1] = x4[perm[2] - 1];
        x[ib] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }
  if (ib > 0) {
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }
    for (k = 0; k < ib; k++) {
      i2 = perm[k] - 1;
      i1 = ((k - nNaNs) - ib) + 64;
      idx[i1] = idx4[i2];
      x[i1] = x4[i2];
    }
  }
  ib = (nNaNs >> 1) + 64;
  for (k = 0; k <= ib - 65; k++) {
    i2 = (k - nNaNs) + 64;
    i1 = idx[i2];
    idx[i2] = idx[63 - k];
    idx[63 - k] = i1;
    x[i2] = xwork[63 - k];
    x[63 - k] = xwork[i2];
  }
  if ((nNaNs & 1) != 0) {
    ib -= nNaNs;
    x[ib] = xwork[ib];
  }
  if (64 - nNaNs > 1) {
    std::memset(&iwork[0], 0, 64U * sizeof(int));
    i3 = (64 - nNaNs) >> 2;
    i1 = 4;
    while (i3 > 1) {
      if ((i3 & 1) != 0) {
        i3--;
        ib = i1 * i3;
        i2 = 64 - (nNaNs + ib);
        if (i2 > i1) {
          c_merge(idx, x, ib, i1, i2 - i1, iwork, xwork);
        }
      }
      ib = i1 << 1;
      i3 >>= 1;
      for (k = 0; k < i3; k++) {
        c_merge(idx, x, k * ib, i1, i1, iwork, xwork);
      }
      i1 = ib;
    }
    if (64 - nNaNs > i1) {
      c_merge(idx, x, 0, i1, 64 - (nNaNs + i1), iwork, xwork);
    }
  }
}

//
// Arguments    : double x_data[]
//                int idx_data[]
//                int idx_size[2]
// Return Type  : void
//
void sort(double x_data[], int idx_data[], int idx_size[2])
{
  double xwork_data[64];
  double x4[4];
  int iwork_data[64];
  int i1;
  int i2;
  int i3;
  int ib;
  int k;
  int nNaNs;
  signed char idx4[4];
  signed char perm[4];
  idx_size[0] = 1;
  idx_size[1] = 64;
  x4[0] = 0.0;
  idx4[0] = 0;
  x4[1] = 0.0;
  idx4[1] = 0;
  x4[2] = 0.0;
  idx4[2] = 0;
  x4[3] = 0.0;
  idx4[3] = 0;
  std::memset(&idx_data[0], 0, 64U * sizeof(int));
  std::memset(&iwork_data[0], 0, 64U * sizeof(int));
  std::memset(&xwork_data[0], 0, 64U * sizeof(double));
  nNaNs = 0;
  ib = 0;
  for (k = 0; k < 64; k++) {
    if (std::isnan(x_data[k])) {
      idx_data[63 - nNaNs] = k + 1;
      xwork_data[63 - nNaNs] = x_data[k];
      nNaNs++;
    } else {
      ib++;
      idx4[ib - 1] = static_cast<signed char>(k + 1);
      x4[ib - 1] = x_data[k];
      if (ib == 4) {
        double d;
        double d1;
        int i4;
        ib = k - nNaNs;
        if (x4[0] <= x4[1]) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }
        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }
        d = x4[i1 - 1];
        d1 = x4[i3 - 1];
        if (d <= d1) {
          d = x4[i2 - 1];
          if (d <= d1) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i2);
            perm[2] = static_cast<signed char>(i3);
            perm[3] = static_cast<signed char>(i4);
          } else if (d <= x4[i4 - 1]) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i2);
            perm[3] = static_cast<signed char>(i4);
          } else {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i4);
            perm[3] = static_cast<signed char>(i2);
          }
        } else {
          d1 = x4[i4 - 1];
          if (d <= d1) {
            if (x4[i2 - 1] <= d1) {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            perm[0] = static_cast<signed char>(i3);
            perm[1] = static_cast<signed char>(i4);
            perm[2] = static_cast<signed char>(i1);
            perm[3] = static_cast<signed char>(i2);
          }
        }
        idx_data[ib - 3] = idx4[perm[0] - 1];
        idx_data[ib - 2] = idx4[perm[1] - 1];
        idx_data[ib - 1] = idx4[perm[2] - 1];
        idx_data[ib] = idx4[perm[3] - 1];
        x_data[ib - 3] = x4[perm[0] - 1];
        x_data[ib - 2] = x4[perm[1] - 1];
        x_data[ib - 1] = x4[perm[2] - 1];
        x_data[ib] = x4[perm[3] - 1];
        ib = 0;
      }
    }
  }
  if (ib > 0) {
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    if (ib == 1) {
      perm[0] = 1;
    } else if (ib == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }
    for (k = 0; k < ib; k++) {
      i2 = perm[k] - 1;
      i1 = ((k - nNaNs) - ib) + 64;
      idx_data[i1] = idx4[i2];
      x_data[i1] = x4[i2];
    }
  }
  ib = (nNaNs >> 1) + 64;
  for (k = 0; k <= ib - 65; k++) {
    i2 = (k - nNaNs) + 64;
    i1 = idx_data[i2];
    idx_data[i2] = idx_data[63 - k];
    idx_data[63 - k] = i1;
    x_data[i2] = xwork_data[63 - k];
    x_data[63 - k] = xwork_data[i2];
  }
  if ((nNaNs & 1) != 0) {
    ib -= nNaNs;
    x_data[ib] = xwork_data[ib];
  }
  if (64 - nNaNs > 1) {
    i3 = (64 - nNaNs) >> 2;
    i1 = 4;
    while (i3 > 1) {
      if ((i3 & 1) != 0) {
        i3--;
        ib = i1 * i3;
        i2 = 64 - (nNaNs + ib);
        if (i2 > i1) {
          merge(idx_data, x_data, ib, i1, i2 - i1, iwork_data, xwork_data);
        }
      }
      ib = i1 << 1;
      i3 >>= 1;
      for (k = 0; k < i3; k++) {
        merge(idx_data, x_data, k * ib, i1, i1, iwork_data, xwork_data);
      }
      i1 = ib;
    }
    if (64 - nNaNs > i1) {
      merge(idx_data, x_data, 0, i1, 64 - (nNaNs + i1), iwork_data, xwork_data);
    }
  }
}

//
// Arguments    : double x[5]
//                int idx[5]
// Return Type  : void
//
void sort(double x[5], int idx[5])
{
  double xwork[5];
  double x4[4];
  int iwork[5];
  int i;
  int i1;
  int i2;
  int i3;
  int k;
  int nNaNs;
  signed char idx4[4];
  signed char perm[4];
  x4[0] = 0.0;
  idx4[0] = 0;
  x4[1] = 0.0;
  idx4[1] = 0;
  x4[2] = 0.0;
  idx4[2] = 0;
  x4[3] = 0.0;
  idx4[3] = 0;
  for (i = 0; i < 5; i++) {
    idx[i] = 0;
    xwork[i] = 0.0;
  }
  nNaNs = 0;
  i = 0;
  for (k = 0; k < 5; k++) {
    if (std::isnan(x[k])) {
      idx[4 - nNaNs] = k + 1;
      xwork[4 - nNaNs] = x[k];
      nNaNs++;
    } else {
      i++;
      idx4[i - 1] = static_cast<signed char>(k + 1);
      x4[i - 1] = x[k];
      if (i == 4) {
        double d;
        double d1;
        int i4;
        i = k - nNaNs;
        if (x4[0] <= x4[1]) {
          i1 = 1;
          i2 = 2;
        } else {
          i1 = 2;
          i2 = 1;
        }
        if (x4[2] <= x4[3]) {
          i3 = 3;
          i4 = 4;
        } else {
          i3 = 4;
          i4 = 3;
        }
        d = x4[i1 - 1];
        d1 = x4[i3 - 1];
        if (d <= d1) {
          d = x4[i2 - 1];
          if (d <= d1) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i2);
            perm[2] = static_cast<signed char>(i3);
            perm[3] = static_cast<signed char>(i4);
          } else if (d <= x4[i4 - 1]) {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i2);
            perm[3] = static_cast<signed char>(i4);
          } else {
            perm[0] = static_cast<signed char>(i1);
            perm[1] = static_cast<signed char>(i3);
            perm[2] = static_cast<signed char>(i4);
            perm[3] = static_cast<signed char>(i2);
          }
        } else {
          d1 = x4[i4 - 1];
          if (d <= d1) {
            if (x4[i2 - 1] <= d1) {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i2);
              perm[3] = static_cast<signed char>(i4);
            } else {
              perm[0] = static_cast<signed char>(i3);
              perm[1] = static_cast<signed char>(i1);
              perm[2] = static_cast<signed char>(i4);
              perm[3] = static_cast<signed char>(i2);
            }
          } else {
            perm[0] = static_cast<signed char>(i3);
            perm[1] = static_cast<signed char>(i4);
            perm[2] = static_cast<signed char>(i1);
            perm[3] = static_cast<signed char>(i2);
          }
        }
        idx[i - 3] = idx4[perm[0] - 1];
        idx[i - 2] = idx4[perm[1] - 1];
        idx[i - 1] = idx4[perm[2] - 1];
        idx[i] = idx4[perm[3] - 1];
        x[i - 3] = x4[perm[0] - 1];
        x[i - 2] = x4[perm[1] - 1];
        x[i - 1] = x4[perm[2] - 1];
        x[i] = x4[perm[3] - 1];
        i = 0;
      }
    }
  }
  if (i > 0) {
    perm[1] = 0;
    perm[2] = 0;
    perm[3] = 0;
    if (i == 1) {
      perm[0] = 1;
    } else if (i == 2) {
      if (x4[0] <= x4[1]) {
        perm[0] = 1;
        perm[1] = 2;
      } else {
        perm[0] = 2;
        perm[1] = 1;
      }
    } else if (x4[0] <= x4[1]) {
      if (x4[1] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 2;
        perm[2] = 3;
      } else if (x4[0] <= x4[2]) {
        perm[0] = 1;
        perm[1] = 3;
        perm[2] = 2;
      } else {
        perm[0] = 3;
        perm[1] = 1;
        perm[2] = 2;
      }
    } else if (x4[0] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 1;
      perm[2] = 3;
    } else if (x4[1] <= x4[2]) {
      perm[0] = 2;
      perm[1] = 3;
      perm[2] = 1;
    } else {
      perm[0] = 3;
      perm[1] = 2;
      perm[2] = 1;
    }
    for (k = 0; k < i; k++) {
      i2 = perm[k] - 1;
      i1 = ((k - nNaNs) - i) + 5;
      idx[i1] = idx4[i2];
      x[i1] = x4[i2];
    }
  }
  i = (nNaNs >> 1) + 5;
  for (k = 0; k <= i - 6; k++) {
    i2 = (k - nNaNs) + 5;
    i1 = idx[i2];
    idx[i2] = idx[4 - k];
    idx[4 - k] = i1;
    x[i2] = xwork[4 - k];
    x[4 - k] = xwork[i2];
  }
  if ((nNaNs & 1) != 0) {
    i -= nNaNs;
    x[i] = xwork[i];
  }
  if (5 - nNaNs > 1) {
    for (i = 0; i < 5; i++) {
      iwork[i] = 0;
    }
    i3 = (5 - nNaNs) >> 2;
    i1 = 4;
    while (i3 > 1) {
      if ((i3 & 1) != 0) {
        i3--;
        i = i1 * i3;
        i2 = 5 - (nNaNs + i);
        if (i2 > i1) {
          b_merge(idx, x, i, i1, i2 - i1, iwork, xwork);
        }
      }
      i = i1 << 1;
      i3 >>= 1;
      for (k = 0; k < i3; k++) {
        b_merge(idx, x, k * i, i1, i1, iwork, xwork);
      }
      i1 = i;
    }
    if (5 - nNaNs > i1) {
      b_merge(idx, x, 0, i1, 5 - (nNaNs + i1), iwork, xwork);
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for sort.cpp
//
// [EOF]
//
