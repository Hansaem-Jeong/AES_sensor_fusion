//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: prediction.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "prediction.h"
#include "rt_nonfinite.h"

// Function Definitions
//
// Arguments    : const double Association_Map_k_1[128]
//                const double Fusion_Track_k_1[1280]
//                const double P_Fusion_Track_k_1[1024]
//                double Fusion_Track_Predicted[1280]
//                double P_Fusion_Track_Predicted[1024]
// Return Type  : void
//
void prediction(const double Association_Map_k_1[128],
                const double Fusion_Track_k_1[1280],
                const double P_Fusion_Track_k_1[1024],
                double Fusion_Track_Predicted[1280],
                double P_Fusion_Track_Predicted[1024])
{
  static const double Q_CV[16]{3.9062500000000018E-7,
                               0.0,
                               1.5625000000000004E-5,
                               0.0,
                               0.0,
                               1.5625000000000007E-6,
                               0.0,
                               6.2500000000000015E-5,
                               1.5625000000000004E-5,
                               0.0,
                               0.00062500000000000012,
                               0.0,
                               0.0,
                               6.2500000000000015E-5,
                               0.0,
                               0.0025000000000000005};
  static const double b_a[16]{1.0,  0.0, 0.0, 0.0, 0.0, 1.0,  0.0, 0.0,
                              0.05, 0.0, 1.0, 0.0, 0.0, 0.05, 0.0, 1.0};
  static const double dv[16]{1.0, 0.0, 0.05, 0.0, 0.0, 1.0, 0.0, 0.05,
                             0.0, 0.0, 1.0,  0.0, 0.0, 0.0, 0.0, 1.0};
  double a[16];
  // --------------------------------------------------------------------------
  //  Fusion_Track_k_1 : [20 X 64]     Input
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
  //  Association_Map_k_1 : [64 X 2]     Input
  // --------------------------------------------------------------------------
  //  1  : Front Vision Track
  //  2  : Front Radar Track
  // --------------------------------------------------------------------------
  //  P_Fusion_Track_k_1 : [4 X 4 X 64]  Input
  // --------------------------------------------------------------------------
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  // --------------------------------------------------------------------------
  //  Fusion_Track_Predicted : [20 X 64]     Output
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
  //  Parameter
  // --------------------------------------------------------------------------
  //  Kalman Filter CV model parameter
  // --------------------------------------------------------------------------
  //  initialization
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Prediction(CV model)
  // --------------------------------------------------------------------------
  for (int id_FST{0}; id_FST < 64; id_FST++) {
    if (Association_Map_k_1[id_FST] + Association_Map_k_1[id_FST + 64] != 0.0) {
      double d;
      int i;
      i = 20 * id_FST + 11;
      d = Fusion_Track_k_1[i];
      if ((d == 3.0) || (d == 4.0) || (d == 5.0) || (d == 6.0) || (d == 7.0) ||
          (d == 8.0) || (d == 9.0) || (d == 10.0)) {
        int Fusion_Track_Predicted_tmp;
        for (int i1{0}; i1 < 4; i1++) {
          double d1;
          double d2;
          double d3;
          double d4;
          int i2;
          int i3;
          d1 = 0.0;
          for (i2 = 0; i2 < 4; i2++) {
            int b_Fusion_Track_Predicted_tmp;
            Fusion_Track_Predicted_tmp = i2 << 2;
            b_Fusion_Track_Predicted_tmp = i1 + Fusion_Track_Predicted_tmp;
            d1 += b_a[b_Fusion_Track_Predicted_tmp] *
                  Fusion_Track_k_1[(i2 + 20 * id_FST) + 12];
            i3 = Fusion_Track_Predicted_tmp + (id_FST << 4);
            a[b_Fusion_Track_Predicted_tmp] =
                ((b_a[i1] * P_Fusion_Track_k_1[i3] +
                  b_a[i1 + 4] * P_Fusion_Track_k_1[i3 + 1]) +
                 b_a[i1 + 8] * P_Fusion_Track_k_1[i3 + 2]) +
                b_a[i1 + 12] * P_Fusion_Track_k_1[i3 + 3];
          }
          Fusion_Track_Predicted[(i1 + 20 * id_FST) + 12] = d1;
          d1 = a[i1];
          d2 = a[i1 + 4];
          d3 = a[i1 + 8];
          d4 = a[i1 + 12];
          for (i2 = 0; i2 < 4; i2++) {
            i3 = i2 << 2;
            Fusion_Track_Predicted_tmp = i1 + i3;
            P_Fusion_Track_Predicted[Fusion_Track_Predicted_tmp +
                                     (id_FST << 4)] =
                (((d1 * dv[i3] + d2 * dv[i3 + 1]) + d3 * dv[i3 + 2]) +
                 d4 * dv[i3 + 3]) +
                Q_CV[Fusion_Track_Predicted_tmp];
          }
        }
        Fusion_Track_Predicted[20 * id_FST] = Fusion_Track_k_1[20 * id_FST];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 1;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 2;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 3;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 4;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 5;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 6;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 7;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 8;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 9;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 10;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted[i] = d;
        Fusion_Track_Predicted_tmp = 20 * id_FST + 16;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 17;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
        Fusion_Track_Predicted_tmp = 20 * id_FST + 18;
        Fusion_Track_Predicted[Fusion_Track_Predicted_tmp] =
            Fusion_Track_k_1[Fusion_Track_Predicted_tmp];
      }
    }
  }
}

//
// File trailer for prediction.cpp
//
// [EOF]
//
