//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: correction.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "correction.h"
#include "inv.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// Arguments    : const double Fusion_Object[768]
//                const double Association_Map[128]
//                const double Association_Map_k_1[128]
//                const double Fusion_Track_Predicted[1280]
//                const double P_Fusion_Track_Predicted[1024]
//                double Fusion_Track_Updated[1280]
//                double P_Fusion_Track_Updated[1024]
//                double Association_Map_Updated[128]
// Return Type  : void
//
void correction(const double Fusion_Object[768],
                const double Association_Map[128],
                const double Association_Map_k_1[128],
                const double Fusion_Track_Predicted[1280],
                const double P_Fusion_Track_Predicted[1024],
                double Fusion_Track_Updated[1280],
                double P_Fusion_Track_Updated[1024],
                double Association_Map_Updated[128])
{
  static const double R_CV[16]{0.01, 0.0, 0.0,  0.0, 0.0, 0.01, 0.0, 0.0,
                               0.0,  0.0, 0.01, 0.0, 0.0, 0.0,  0.0, 0.01};
  static double Residual_VRU[16384];
  static double Residual_Vehicle[16384];
  static const signed char a[16]{1, 0, 0, 0, 0, 1, 0, 0,
                                 0, 0, 1, 0, 0, 0, 0, 1};
  double Norm_Residual_VRU[4096];
  double Norm_Residual_Vehicle[4096];
  double z_CV[256];
  double x[64];
  double K_CV[16];
  double b_a[16];
  double dv[16];
  double absxk;
  double d;
  double d1;
  double scale;
  double t;
  double y;
  int iidx[64];
  int sorted_Fusion_Object_id[64];
  int Residual_Vehicle_tmp;
  int i;
  int i1;
  int i2;
  int id_FO;
  int id_FST;
  signed char i3;
  signed char i4;
  signed char i5;
  signed char i6;
  bool guard1{false};
  // --------------------------------------------------------------------------
  //  Fusion_Object : [12 X 64]     Input
  // --------------------------------------------------------------------------
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  //  5  : Width
  //  6  : Length
  //  7  : Heading angle
  //  8  : Fused FVT ID
  //  9  : Fused FRT ID
  //  10 : Absolute Velocity in Motion Attribute
  //  11 : Motion
  //  12 : Shape
  // --------------------------------------------------------------------------
  //  Association_Map : [64 X 2]     Input
  // --------------------------------------------------------------------------
  //  1  : Front Vision Track
  //  2  : Front Radar Track
  // --------------------------------------------------------------------------
  //  Association_Map_k_1 : [64 X 2]     Input
  // --------------------------------------------------------------------------
  //  1  : Front Vision Track
  //  2  : Front Radar Track
  // --------------------------------------------------------------------------
  //  Fusion_Track_Predicted : [20 X 64]     Input
  // --------------------------------------------------------------------------
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  //  5  : Width
  //  6  : Length
  //  7  : Heading angle
  //  8  : Fused FVT ID
  //  9  : Fused FRT ID
  //  10 : Absolute Velocity in Motion Attribute
  //  11 : Motion Attribute
  //  12 : Shape Attribute
  //  13 : (Tracking) Relative position Y
  //  14 : (Tracking) Relative position X
  //  15 : (Tracking) Relative velocity Y
  //  16 : (Tracking) Relative velocity X
  //  17 : Updated Age
  //  18 : Coasting Age
  //  19 : Life Time
  //  20 : Relative normal position with respect to lane
  // --------------------------------------------------------------------------
  //  P_Fusion_Track_Predicted : [4 X 4 X 64]  Input
  // --------------------------------------------------------------------------
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  // --------------------------------------------------------------------------
  //  Fusion_Track_Updated : [20 X 64]     Output
  // --------------------------------------------------------------------------
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  //  5  : Width
  //  6  : Length
  //  7  : Heading angle
  //  8  : Fused FVT ID
  //  9  : Fused FRT ID
  //  10 : Absolute Velocity in Motion Attribute
  //  11 : Motion Attribute
  //  12 : Shape Attribute
  //  13 : (Tracking) Relative position Y
  //  14 : (Tracking) Relative position X
  //  15 : (Tracking) Relative velocity Y
  //  16 : (Tracking) Relative velocity X
  //  17 : Updated Age
  //  18 : Coasting Age
  //  19 : Life Time
  //  20 : Relative normal position with respect to lane
  // --------------------------------------------------------------------------
  //  P_Fusion_Track_Updated : [4 X 4 X 64]  Output
  // --------------------------------------------------------------------------
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  // --------------------------------------------------------------------------
  //  Association_Map_Updated : [64 X 2]     Output
  // --------------------------------------------------------------------------
  //  1  : Front Vision Track
  //  2  : Front Radar Track
  // --------------------------------------------------------------------------
  //  Parameter
  // --------------------------------------------------------------------------
  //  Kalman Filter CV model parameter
  // --------------------------------------------------------------------------
  //  initialization
  // --------------------------------------------------------------------------
  for (i = 0; i < 16384; i++) {
    Residual_Vehicle[i] = 300.0;
  }
  //  (residual state X Reference number X Target number)
  for (i = 0; i < 4096; i++) {
    Norm_Residual_Vehicle[i] = 300.0;
  }
  //  (Reference number X Target number)
  for (i = 0; i < 16384; i++) {
    Residual_VRU[i] = 300.0;
  }
  //  (residual state X Reference number X Target number)
  for (i = 0; i < 4096; i++) {
    Norm_Residual_VRU[i] = 300.0;
  }
  //  (Reference number X Target number)
  // --------------------------------------------------------------------------
  //  Correction(CV model)
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Residual Calculation for Vehicle
  // --------------------------------------------------------------------------
  for (id_FST = 0; id_FST < 64; id_FST++) {
    if (Association_Map_k_1[id_FST] + Association_Map_k_1[id_FST + 64] != 0.0) {
      scale = Fusion_Track_Predicted[20 * id_FST + 11];
      if ((scale == 3.0) || (scale == 4.0)) {
        for (id_FO = 0; id_FO < 64; id_FO++) {
          if (Association_Map[id_FO] + Association_Map[id_FO + 64] != 0.0) {
            scale = Fusion_Object[12 * id_FO + 11];
            if ((scale == 3.0) || (scale == 4.0)) {
              Residual_Vehicle_tmp = (id_FST << 2) + (id_FO << 8);
              Residual_Vehicle[Residual_Vehicle_tmp] =
                  Fusion_Track_Predicted[20 * id_FST + 12] -
                  Fusion_Object[12 * id_FO];
              Residual_Vehicle[Residual_Vehicle_tmp + 1] =
                  Fusion_Track_Predicted[20 * id_FST + 13] -
                  Fusion_Object[12 * id_FO + 1];
              Residual_Vehicle[Residual_Vehicle_tmp + 2] =
                  Fusion_Track_Predicted[20 * id_FST + 14] -
                  Fusion_Object[12 * id_FO + 2];
              Residual_Vehicle[Residual_Vehicle_tmp + 3] =
                  Fusion_Track_Predicted[20 * id_FST + 15] -
                  Fusion_Object[12 * id_FO + 3];
              scale = 3.3121686421112381E-170;
              absxk = std::abs(Residual_Vehicle[Residual_Vehicle_tmp]);
              if (absxk > 3.3121686421112381E-170) {
                y = 1.0;
                scale = absxk;
              } else {
                t = absxk / 3.3121686421112381E-170;
                y = t * t;
              }
              absxk = std::abs(Residual_Vehicle[Residual_Vehicle_tmp + 1]);
              if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
              } else {
                t = absxk / scale;
                y += t * t;
              }
              absxk = std::abs(Residual_Vehicle[Residual_Vehicle_tmp + 2]);
              if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
              } else {
                t = absxk / scale;
                y += t * t;
              }
              absxk = std::abs(Residual_Vehicle[Residual_Vehicle_tmp + 3]);
              if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
              } else {
                t = absxk / scale;
                y += t * t;
              }
              Norm_Residual_Vehicle[id_FST + (id_FO << 6)] =
                  scale * std::sqrt(y);
            }
          }
        }
      }
    }
  }
  // --------------------------------------------------------------------------
  //  Correction for Vehicle
  // --------------------------------------------------------------------------
  for (id_FST = 0; id_FST < 64; id_FST++) {
    if (Association_Map_k_1[id_FST] + Association_Map_k_1[id_FST + 64] != 0.0) {
      i = 20 * id_FST + 11;
      scale = Fusion_Track_Predicted[i];
      if ((scale == 3.0) || (scale == 4.0)) {
        for (i1 = 0; i1 < 64; i1++) {
          x[i1] = Norm_Residual_Vehicle[id_FST + (i1 << 6)];
        }
        coder::internal::b_sort(x, iidx);
        std::copy(&iidx[0], &iidx[64], &sorted_Fusion_Object_id[0]);
        std::copy(&Norm_Residual_Vehicle[sorted_Fusion_Object_id[0] * 64 + -64],
                  &Norm_Residual_Vehicle[sorted_Fusion_Object_id[0] * 64],
                  &x[0]);
        coder::internal::b_sort(x, iidx);
        guard1 = false;
        if (iidx[0] == id_FST + 1) {
          i1 = id_FST << 2;
          i2 = i1 + ((sorted_Fusion_Object_id[0] - 1) << 8);
          absxk = Residual_Vehicle[i2];
          if ((absxk > -2.0) && (absxk < 2.0)) {
            absxk = Residual_Vehicle[i2 + 1];
            if ((absxk > -2.0) && (absxk < 2.0)) {
              absxk = Residual_Vehicle[i2 + 2];
              if ((absxk > -2.0) && (absxk < 2.0)) {
                absxk = Residual_Vehicle[i2 + 3];
                if ((absxk > -2.0) && (absxk < 2.0)) {
                  scale = Fusion_Track_Predicted[20 * id_FST + 12];
                  absxk = Fusion_Track_Predicted[20 * id_FST + 13];
                  t = Fusion_Track_Predicted[20 * id_FST + 14];
                  y = Fusion_Track_Predicted[20 * id_FST + 15];
                  for (i2 = 0; i2 < 4; i2++) {
                    z_CV[i2 + i1] =
                        Fusion_Object[i2 +
                                      12 * (sorted_Fusion_Object_id[0] - 1)] -
                        (((static_cast<double>(a[i2]) * scale +
                           static_cast<double>(a[i2 + 4]) * absxk) +
                          static_cast<double>(a[i2 + 8]) * t) +
                         static_cast<double>(a[i2 + 12]) * y);
                  }
                  Residual_Vehicle_tmp = 12 * (sorted_Fusion_Object_id[0] - 1);
                  Fusion_Track_Updated[20 * id_FST] =
                      Fusion_Object[Residual_Vehicle_tmp];
                  Fusion_Track_Updated[20 * id_FST + 1] =
                      Fusion_Object[Residual_Vehicle_tmp + 1];
                  Fusion_Track_Updated[20 * id_FST + 2] =
                      Fusion_Object[Residual_Vehicle_tmp + 2];
                  Fusion_Track_Updated[20 * id_FST + 3] =
                      Fusion_Object[Residual_Vehicle_tmp + 3];
                  Fusion_Track_Updated[20 * id_FST + 4] =
                      Fusion_Object[Residual_Vehicle_tmp + 4];
                  Fusion_Track_Updated[20 * id_FST + 5] =
                      Fusion_Object[Residual_Vehicle_tmp + 5];
                  Fusion_Track_Updated[20 * id_FST + 6] =
                      Fusion_Object[Residual_Vehicle_tmp + 6];
                  //  ASSOCIATION MAP UPDATE
                  scale = Association_Map[sorted_Fusion_Object_id[0] - 1];
                  Association_Map_Updated[id_FST] = scale;
                  absxk = Association_Map[sorted_Fusion_Object_id[0] + 63];
                  Association_Map_Updated[id_FST + 64] = absxk;
                  Fusion_Track_Updated[20 * id_FST + 7] = scale;
                  Fusion_Track_Updated[20 * id_FST + 8] = absxk;
                  Fusion_Track_Updated[20 * id_FST + 9] =
                      Fusion_Object[Residual_Vehicle_tmp + 9];
                  Fusion_Track_Updated[20 * id_FST + 10] =
                      Fusion_Object[Residual_Vehicle_tmp + 10];
                  Fusion_Track_Updated[i] =
                      Fusion_Object[Residual_Vehicle_tmp + 11];
                } else {
                  guard1 = true;
                }
              } else {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
        if (guard1) {
          Fusion_Track_Updated[20 * id_FST] =
              Fusion_Track_Predicted[20 * id_FST];
          Residual_Vehicle_tmp = 20 * id_FST + 1;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 2;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 3;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 4;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 5;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 6;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 7;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 8;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 9;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 10;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Fusion_Track_Updated[i] = scale;
        }
        for (i = 0; i < 4; i++) {
          i3 = a[i];
          i4 = a[i + 4];
          i5 = a[i + 8];
          i6 = a[i + 12];
          for (i1 = 0; i1 < 4; i1++) {
            i2 = i1 << 2;
            Residual_Vehicle_tmp = i2 + (id_FST << 4);
            b_a[i + i2] =
                ((static_cast<double>(i3) *
                      P_Fusion_Track_Predicted[Residual_Vehicle_tmp] +
                  static_cast<double>(i4) *
                      P_Fusion_Track_Predicted[Residual_Vehicle_tmp + 1]) +
                 static_cast<double>(i5) *
                     P_Fusion_Track_Predicted[Residual_Vehicle_tmp + 2]) +
                static_cast<double>(i6) *
                    P_Fusion_Track_Predicted[Residual_Vehicle_tmp + 3];
          }
          scale = b_a[i];
          absxk = b_a[i + 4];
          t = b_a[i + 8];
          y = b_a[i + 12];
          for (i1 = 0; i1 < 4; i1++) {
            i2 = i1 << 2;
            Residual_Vehicle_tmp = i + i2;
            K_CV[Residual_Vehicle_tmp] =
                (((scale * static_cast<double>(a[i2]) +
                   absxk * static_cast<double>(a[i2 + 1])) +
                  t * static_cast<double>(a[i2 + 2])) +
                 y * static_cast<double>(a[i2 + 3])) +
                R_CV[Residual_Vehicle_tmp];
          }
          i1 = i + (id_FST << 4);
          for (i2 = 0; i2 < 4; i2++) {
            Residual_Vehicle_tmp = i2 << 2;
            b_a[i + Residual_Vehicle_tmp] =
                ((P_Fusion_Track_Predicted[i1] *
                      static_cast<double>(a[Residual_Vehicle_tmp]) +
                  P_Fusion_Track_Predicted[i1 + 4] *
                      static_cast<double>(a[Residual_Vehicle_tmp + 1])) +
                 P_Fusion_Track_Predicted[i1 + 8] *
                     static_cast<double>(a[Residual_Vehicle_tmp + 2])) +
                P_Fusion_Track_Predicted[i1 + 12] *
                    static_cast<double>(a[Residual_Vehicle_tmp + 3]);
          }
        }
        coder::inv(K_CV, dv);
        i = id_FST << 4;
        for (i1 = 0; i1 < 4; i1++) {
          scale = 0.0;
          absxk = b_a[i1];
          t = b_a[i1 + 4];
          y = b_a[i1 + 8];
          d = b_a[i1 + 12];
          for (i2 = 0; i2 < 4; i2++) {
            Residual_Vehicle_tmp = i2 << 2;
            d1 = ((absxk * dv[Residual_Vehicle_tmp] +
                   t * dv[Residual_Vehicle_tmp + 1]) +
                  y * dv[Residual_Vehicle_tmp + 2]) +
                 d * dv[Residual_Vehicle_tmp + 3];
            K_CV[i1 + Residual_Vehicle_tmp] = d1;
            scale += d1 * z_CV[i2 + (id_FST << 2)];
          }
          Residual_Vehicle_tmp = (i1 + 20 * id_FST) + 12;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp] + scale;
          scale = K_CV[i1];
          absxk = K_CV[i1 + 4];
          t = K_CV[i1 + 8];
          y = K_CV[i1 + 12];
          for (i2 = 0; i2 < 4; i2++) {
            Residual_Vehicle_tmp = i2 << 2;
            b_a[i1 + Residual_Vehicle_tmp] =
                ((scale * static_cast<double>(a[Residual_Vehicle_tmp]) +
                  absxk * static_cast<double>(a[Residual_Vehicle_tmp + 1])) +
                 t * static_cast<double>(a[Residual_Vehicle_tmp + 2])) +
                y * static_cast<double>(a[Residual_Vehicle_tmp + 3]);
          }
          scale = b_a[i1];
          absxk = b_a[i1 + 4];
          t = b_a[i1 + 8];
          y = b_a[i1 + 12];
          for (i2 = 0; i2 < 4; i2++) {
            Residual_Vehicle_tmp = i2 << 2;
            id_FO = Residual_Vehicle_tmp + i;
            Residual_Vehicle_tmp = (i1 + Residual_Vehicle_tmp) + i;
            P_Fusion_Track_Updated[Residual_Vehicle_tmp] =
                P_Fusion_Track_Predicted[Residual_Vehicle_tmp] -
                (((scale * P_Fusion_Track_Predicted[id_FO] +
                   absxk * P_Fusion_Track_Predicted[id_FO + 1]) +
                  t * P_Fusion_Track_Predicted[id_FO + 2]) +
                 y * P_Fusion_Track_Predicted[id_FO + 3]);
          }
        }
        Residual_Vehicle_tmp = 20 * id_FST + 17;
        Fusion_Track_Updated[Residual_Vehicle_tmp] =
            Fusion_Track_Predicted[Residual_Vehicle_tmp];
        Residual_Vehicle_tmp = 20 * id_FST + 18;
        Fusion_Track_Updated[Residual_Vehicle_tmp] =
            Fusion_Track_Predicted[Residual_Vehicle_tmp];
        Residual_Vehicle_tmp = 20 * id_FST + 16;
        Fusion_Track_Updated[Residual_Vehicle_tmp] =
            Fusion_Track_Predicted[Residual_Vehicle_tmp];
      }
    }
  }
  // --------------------------------------------------------------------------
  //  Residual Calculation for VRU
  // --------------------------------------------------------------------------
  for (id_FST = 0; id_FST < 64; id_FST++) {
    if (Association_Map_k_1[id_FST] + Association_Map_k_1[id_FST + 64] != 0.0) {
      scale = Fusion_Track_Predicted[20 * id_FST + 11];
      if ((scale == 3.0) || (scale == 4.0) || (scale == 5.0) ||
          (scale == 6.0) || (scale == 7.0) || (scale == 8.0) ||
          (scale == 9.0) || (scale == 10.0)) {
        for (id_FO = 0; id_FO < 64; id_FO++) {
          if (Association_Map[id_FO] + Association_Map[id_FO + 64] != 0.0) {
            scale = Fusion_Object[12 * id_FO + 11];
            if ((scale == 5.0) || (scale == 6.0) || (scale == 7.0) ||
                (scale == 8.0) || (scale == 9.0) || (scale == 10.0)) {
              Residual_Vehicle_tmp = (id_FST << 2) + (id_FO << 8);
              Residual_VRU[Residual_Vehicle_tmp] =
                  Fusion_Track_Predicted[20 * id_FST] -
                  Fusion_Object[12 * id_FO];
              Residual_VRU[Residual_Vehicle_tmp + 1] =
                  Fusion_Track_Predicted[20 * id_FST + 1] -
                  Fusion_Object[12 * id_FO + 1];
              Residual_VRU[Residual_Vehicle_tmp + 2] =
                  Fusion_Track_Predicted[20 * id_FST + 2] -
                  Fusion_Object[12 * id_FO + 2];
              Residual_VRU[Residual_Vehicle_tmp + 3] =
                  Fusion_Track_Predicted[20 * id_FST + 3] -
                  Fusion_Object[12 * id_FO + 3];
              scale = 3.3121686421112381E-170;
              absxk = std::abs(Residual_VRU[Residual_Vehicle_tmp]);
              if (absxk > 3.3121686421112381E-170) {
                y = 1.0;
                scale = absxk;
              } else {
                t = absxk / 3.3121686421112381E-170;
                y = t * t;
              }
              absxk = std::abs(Residual_VRU[Residual_Vehicle_tmp + 1]);
              if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
              } else {
                t = absxk / scale;
                y += t * t;
              }
              absxk = std::abs(Residual_VRU[Residual_Vehicle_tmp + 2]);
              if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
              } else {
                t = absxk / scale;
                y += t * t;
              }
              absxk = std::abs(Residual_VRU[Residual_Vehicle_tmp + 3]);
              if (absxk > scale) {
                t = scale / absxk;
                y = y * t * t + 1.0;
                scale = absxk;
              } else {
                t = absxk / scale;
                y += t * t;
              }
              Norm_Residual_VRU[id_FST + (id_FO << 6)] = scale * std::sqrt(y);
            }
          }
        }
      }
    }
  }
  // --------------------------------------------------------------------------
  //  Correction for VRU
  // --------------------------------------------------------------------------
  for (id_FST = 0; id_FST < 64; id_FST++) {
    if (Association_Map_k_1[id_FST] + Association_Map_k_1[id_FST + 64] != 0.0) {
      i = 20 * id_FST + 11;
      scale = Fusion_Track_Predicted[i];
      if ((scale == 5.0) || (scale == 6.0) || (scale == 7.0) ||
          (scale == 8.0) || (scale == 9.0) || (scale == 10.0)) {
        for (i1 = 0; i1 < 64; i1++) {
          x[i1] = Norm_Residual_VRU[id_FST + (i1 << 6)];
        }
        coder::internal::b_sort(x, iidx);
        std::copy(&iidx[0], &iidx[64], &sorted_Fusion_Object_id[0]);
        std::copy(&Norm_Residual_VRU[sorted_Fusion_Object_id[0] * 64 + -64],
                  &Norm_Residual_VRU[sorted_Fusion_Object_id[0] * 64], &x[0]);
        coder::internal::b_sort(x, iidx);
        guard1 = false;
        if (iidx[0] == id_FST + 1) {
          i1 = id_FST << 2;
          i2 = i1 + ((sorted_Fusion_Object_id[0] - 1) << 8);
          absxk = Residual_VRU[i2];
          if ((absxk > -2.0) && (absxk < 2.0)) {
            absxk = Residual_VRU[i2 + 1];
            if ((absxk > -2.0) && (absxk < 2.0)) {
              absxk = Residual_VRU[i2 + 2];
              if ((absxk > -2.0) && (absxk < 2.0)) {
                absxk = Residual_VRU[i2 + 3];
                if ((absxk > -2.0) && (absxk < 2.0)) {
                  scale = Fusion_Track_Predicted[20 * id_FST + 12];
                  absxk = Fusion_Track_Predicted[20 * id_FST + 13];
                  t = Fusion_Track_Predicted[20 * id_FST + 14];
                  y = Fusion_Track_Predicted[20 * id_FST + 15];
                  for (i2 = 0; i2 < 4; i2++) {
                    z_CV[i2 + i1] =
                        Fusion_Object[i2 +
                                      12 * (sorted_Fusion_Object_id[0] - 1)] -
                        (((static_cast<double>(a[i2]) * scale +
                           static_cast<double>(a[i2 + 4]) * absxk) +
                          static_cast<double>(a[i2 + 8]) * t) +
                         static_cast<double>(a[i2 + 12]) * y);
                  }
                  Residual_Vehicle_tmp = 12 * (sorted_Fusion_Object_id[0] - 1);
                  Fusion_Track_Updated[20 * id_FST] =
                      Fusion_Object[Residual_Vehicle_tmp];
                  Fusion_Track_Updated[20 * id_FST + 1] =
                      Fusion_Object[Residual_Vehicle_tmp + 1];
                  Fusion_Track_Updated[20 * id_FST + 2] =
                      Fusion_Object[Residual_Vehicle_tmp + 2];
                  Fusion_Track_Updated[20 * id_FST + 3] =
                      Fusion_Object[Residual_Vehicle_tmp + 3];
                  Fusion_Track_Updated[20 * id_FST + 4] =
                      Fusion_Object[Residual_Vehicle_tmp + 4];
                  Fusion_Track_Updated[20 * id_FST + 5] =
                      Fusion_Object[Residual_Vehicle_tmp + 5];
                  Fusion_Track_Updated[20 * id_FST + 6] =
                      Fusion_Object[Residual_Vehicle_tmp + 6];
                  //  ASSOCIATION MAP UPDATE
                  scale = Association_Map[sorted_Fusion_Object_id[0] - 1];
                  Association_Map_Updated[id_FST] = scale;
                  absxk = Association_Map[sorted_Fusion_Object_id[0] + 63];
                  Association_Map_Updated[id_FST + 64] = absxk;
                  Fusion_Track_Updated[20 * id_FST + 7] = scale;
                  Fusion_Track_Updated[20 * id_FST + 8] = absxk;
                  Fusion_Track_Updated[20 * id_FST + 9] =
                      Fusion_Object[Residual_Vehicle_tmp + 9];
                  Fusion_Track_Updated[20 * id_FST + 10] =
                      Fusion_Object[Residual_Vehicle_tmp + 10];
                  Fusion_Track_Updated[i] =
                      Fusion_Object[Residual_Vehicle_tmp + 11];
                } else {
                  guard1 = true;
                }
              } else {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
        if (guard1) {
          Fusion_Track_Updated[20 * id_FST] =
              Fusion_Track_Predicted[20 * id_FST];
          Residual_Vehicle_tmp = 20 * id_FST + 1;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 2;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 3;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 4;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 5;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 6;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 7;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 8;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 9;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Residual_Vehicle_tmp = 20 * id_FST + 10;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp];
          Fusion_Track_Updated[i] = scale;
        }
        for (i = 0; i < 4; i++) {
          i3 = a[i];
          i4 = a[i + 4];
          i5 = a[i + 8];
          i6 = a[i + 12];
          for (i1 = 0; i1 < 4; i1++) {
            i2 = i1 << 2;
            Residual_Vehicle_tmp = i2 + (id_FST << 4);
            b_a[i + i2] =
                ((static_cast<double>(i3) *
                      P_Fusion_Track_Predicted[Residual_Vehicle_tmp] +
                  static_cast<double>(i4) *
                      P_Fusion_Track_Predicted[Residual_Vehicle_tmp + 1]) +
                 static_cast<double>(i5) *
                     P_Fusion_Track_Predicted[Residual_Vehicle_tmp + 2]) +
                static_cast<double>(i6) *
                    P_Fusion_Track_Predicted[Residual_Vehicle_tmp + 3];
          }
          scale = b_a[i];
          absxk = b_a[i + 4];
          t = b_a[i + 8];
          y = b_a[i + 12];
          for (i1 = 0; i1 < 4; i1++) {
            i2 = i1 << 2;
            Residual_Vehicle_tmp = i + i2;
            K_CV[Residual_Vehicle_tmp] =
                (((scale * static_cast<double>(a[i2]) +
                   absxk * static_cast<double>(a[i2 + 1])) +
                  t * static_cast<double>(a[i2 + 2])) +
                 y * static_cast<double>(a[i2 + 3])) +
                R_CV[Residual_Vehicle_tmp];
          }
          i1 = i + (id_FST << 4);
          for (i2 = 0; i2 < 4; i2++) {
            Residual_Vehicle_tmp = i2 << 2;
            b_a[i + Residual_Vehicle_tmp] =
                ((P_Fusion_Track_Predicted[i1] *
                      static_cast<double>(a[Residual_Vehicle_tmp]) +
                  P_Fusion_Track_Predicted[i1 + 4] *
                      static_cast<double>(a[Residual_Vehicle_tmp + 1])) +
                 P_Fusion_Track_Predicted[i1 + 8] *
                     static_cast<double>(a[Residual_Vehicle_tmp + 2])) +
                P_Fusion_Track_Predicted[i1 + 12] *
                    static_cast<double>(a[Residual_Vehicle_tmp + 3]);
          }
        }
        coder::inv(K_CV, dv);
        i = id_FST << 4;
        for (i1 = 0; i1 < 4; i1++) {
          scale = 0.0;
          absxk = b_a[i1];
          t = b_a[i1 + 4];
          y = b_a[i1 + 8];
          d = b_a[i1 + 12];
          for (i2 = 0; i2 < 4; i2++) {
            Residual_Vehicle_tmp = i2 << 2;
            d1 = ((absxk * dv[Residual_Vehicle_tmp] +
                   t * dv[Residual_Vehicle_tmp + 1]) +
                  y * dv[Residual_Vehicle_tmp + 2]) +
                 d * dv[Residual_Vehicle_tmp + 3];
            K_CV[i1 + Residual_Vehicle_tmp] = d1;
            scale += d1 * z_CV[i2 + (id_FST << 2)];
          }
          Residual_Vehicle_tmp = (i1 + 20 * id_FST) + 12;
          Fusion_Track_Updated[Residual_Vehicle_tmp] =
              Fusion_Track_Predicted[Residual_Vehicle_tmp] + scale;
          scale = K_CV[i1];
          absxk = K_CV[i1 + 4];
          t = K_CV[i1 + 8];
          y = K_CV[i1 + 12];
          for (i2 = 0; i2 < 4; i2++) {
            Residual_Vehicle_tmp = i2 << 2;
            b_a[i1 + Residual_Vehicle_tmp] =
                ((scale * static_cast<double>(a[Residual_Vehicle_tmp]) +
                  absxk * static_cast<double>(a[Residual_Vehicle_tmp + 1])) +
                 t * static_cast<double>(a[Residual_Vehicle_tmp + 2])) +
                y * static_cast<double>(a[Residual_Vehicle_tmp + 3]);
          }
          scale = b_a[i1];
          absxk = b_a[i1 + 4];
          t = b_a[i1 + 8];
          y = b_a[i1 + 12];
          for (i2 = 0; i2 < 4; i2++) {
            Residual_Vehicle_tmp = i2 << 2;
            id_FO = Residual_Vehicle_tmp + i;
            Residual_Vehicle_tmp = (i1 + Residual_Vehicle_tmp) + i;
            P_Fusion_Track_Updated[Residual_Vehicle_tmp] =
                P_Fusion_Track_Predicted[Residual_Vehicle_tmp] -
                (((scale * P_Fusion_Track_Predicted[id_FO] +
                   absxk * P_Fusion_Track_Predicted[id_FO + 1]) +
                  t * P_Fusion_Track_Predicted[id_FO + 2]) +
                 y * P_Fusion_Track_Predicted[id_FO + 3]);
          }
        }
        Residual_Vehicle_tmp = 20 * id_FST + 17;
        Fusion_Track_Updated[Residual_Vehicle_tmp] =
            Fusion_Track_Predicted[Residual_Vehicle_tmp];
        Residual_Vehicle_tmp = 20 * id_FST + 18;
        Fusion_Track_Updated[Residual_Vehicle_tmp] =
            Fusion_Track_Predicted[Residual_Vehicle_tmp];
        Residual_Vehicle_tmp = 20 * id_FST + 16;
        Fusion_Track_Updated[Residual_Vehicle_tmp] =
            Fusion_Track_Predicted[Residual_Vehicle_tmp];
      }
    }
  }
}

//
// File trailer for correction.cpp
//
// [EOF]
//
