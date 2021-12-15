//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: inv.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "inv.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const double x[16]
//                double y[16]
// Return Type  : void
//
namespace coder {
void inv(const double x[16], double y[16])
{
  double b_x[16];
  double smax;
  int b_i;
  int i;
  int i1;
  int j;
  int jA;
  int jp1j;
  int k;
  int kAcol;
  signed char ipiv[4];
  signed char p[4];
  for (i = 0; i < 16; i++) {
    y[i] = 0.0;
    b_x[i] = x[i];
  }
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  for (j = 0; j < 3; j++) {
    int b_tmp;
    int mmj_tmp;
    mmj_tmp = 2 - j;
    b_tmp = j * 5;
    jp1j = b_tmp + 2;
    jA = 4 - j;
    kAcol = 0;
    smax = std::abs(b_x[b_tmp]);
    for (k = 2; k <= jA; k++) {
      double s;
      s = std::abs(b_x[(b_tmp + k) - 1]);
      if (s > smax) {
        kAcol = k - 1;
        smax = s;
      }
    }
    if (b_x[b_tmp + kAcol] != 0.0) {
      if (kAcol != 0) {
        jA = j + kAcol;
        ipiv[j] = static_cast<signed char>(jA + 1);
        smax = b_x[j];
        b_x[j] = b_x[jA];
        b_x[jA] = smax;
        smax = b_x[j + 4];
        b_x[j + 4] = b_x[jA + 4];
        b_x[jA + 4] = smax;
        smax = b_x[j + 8];
        b_x[j + 8] = b_x[jA + 8];
        b_x[jA + 8] = smax;
        smax = b_x[j + 12];
        b_x[j + 12] = b_x[jA + 12];
        b_x[jA + 12] = smax;
      }
      i = (b_tmp - j) + 4;
      for (b_i = jp1j; b_i <= i; b_i++) {
        b_x[b_i - 1] /= b_x[b_tmp];
      }
    }
    jA = b_tmp;
    for (kAcol = 0; kAcol <= mmj_tmp; kAcol++) {
      smax = b_x[(b_tmp + (kAcol << 2)) + 4];
      if (smax != 0.0) {
        i = jA + 6;
        i1 = (jA - j) + 8;
        for (jp1j = i; jp1j <= i1; jp1j++) {
          b_x[jp1j - 1] += b_x[((b_tmp + jp1j) - jA) - 5] * -smax;
        }
      }
      jA += 4;
    }
  }
  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  p[3] = 4;
  if (ipiv[0] > 1) {
    jA = p[ipiv[0] - 1];
    p[ipiv[0] - 1] = 1;
    p[0] = static_cast<signed char>(jA);
  }
  if (ipiv[1] > 2) {
    jA = p[ipiv[1] - 1];
    p[ipiv[1] - 1] = p[1];
    p[1] = static_cast<signed char>(jA);
  }
  if (ipiv[2] > 3) {
    jA = p[ipiv[2] - 1];
    p[ipiv[2] - 1] = p[2];
    p[2] = static_cast<signed char>(jA);
  }
  for (k = 0; k < 4; k++) {
    jp1j = (p[k] - 1) << 2;
    y[k + jp1j] = 1.0;
    for (j = k + 1; j < 5; j++) {
      i = (j + jp1j) - 1;
      if (y[i] != 0.0) {
        i1 = j + 1;
        for (b_i = i1; b_i < 5; b_i++) {
          jA = (b_i + jp1j) - 1;
          y[jA] -= y[i] * b_x[(b_i + ((j - 1) << 2)) - 1];
        }
      }
    }
  }
  for (j = 0; j < 4; j++) {
    jA = j << 2;
    for (k = 3; k >= 0; k--) {
      kAcol = k << 2;
      i = k + jA;
      smax = y[i];
      if (smax != 0.0) {
        y[i] = smax / b_x[k + kAcol];
        for (b_i = 0; b_i < k; b_i++) {
          jp1j = b_i + jA;
          y[jp1j] -= y[i] * b_x[b_i + kAcol];
        }
      }
    }
  }
}

} // namespace coder

//
// File trailer for inv.cpp
//
// [EOF]
//
