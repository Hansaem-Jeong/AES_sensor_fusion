//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: shape_attribute.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "shape_attribute.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double Fusion_Object[768]
//                const double Old_Fusion_Track_Candidate[768]
//                const double Association_Map[128]
//                const double Front_Vision_Track[360]
//                const double Old_Shape[320]
//                double Fusion_Object_out[768]
//                double Shape_ID[320]
// Return Type  : void
//
void shape_attribute(const double Fusion_Object[768],
                     const double Old_Fusion_Track_Candidate[768],
                     const double Association_Map[128],
                     const double Front_Vision_Track[360],
                     const double Old_Shape[320], double Fusion_Object_out[768],
                     double Shape_ID[320])
{
  double Gating_Info_Old_Fusion_Track_Candidate[192];
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  // --------------------------------------------------------------------------
  //  Front_Vision_Track : [36 X 10]     Input
  // --------------------------------------------------------------------------
  //  1  : ID
  //  2  : Rel_POS_Y
  //  3  : Rel_POS_X
  //  4  : Rel_VEL_Y
  //  5  : Absolute Velocity X
  //  6  : Absolute Velocity Y
  //  7  : Length
  //  8  : Width
  //  9  : Height
  //  10 : Heading Angle
  //  11 : Classification
  //  12 : Angle Left
  //  13 : Angle Rate
  //  14 : Angle Right
  //  15 : Brake Light
  //  16 : Lane Assign
  //  17 : Motion Category
  //  18 : Motion Orientation
  //  19 : Motion Status
  //  20 : Alive Age
  //  21 : Side
  //  22 : Predicted Object
  //  23 : Turn Signal Left
  //  24 : Turn Signal Right
  //  25 : Preprocessing(Coordinate Transform) Rel_POS_Y
  //  26 : Preprocessing(Coordinate Transform) Rel_POS_X
  //  27 : Preprocessing Relative Velocity Y
  //  28 : Preprocessing Relative Velocity X
  //  29 : Preprocessing Rel_ACC_X
  //  30 : Preprocessing(Unit Conversion) Heading Anlge
  //  31 : Range
  //  32 : Angle
  //  33 : Absolute Velocity
  //  34 : Absolute Velocity X in Motion Attribute
  //  35 : Absolute Velocity Y in Motion Attribute
  //  36 : Motion Attribute
  // --------------------------------------------------------------------------
  //  Fusion Object : [12 X 64]     Input
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
  //  12 : -
  // --------------------------------------------------------------------------
  //  Fusion_Object_out : [12 X 64]     Output
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
  //  Shape_ID : [64 X 5]     Input, Output
  // --------------------------------------------------------------------------
  //  1 : Shape
  //  2 : Vehicle stack
  //  3 : Pedestrian stack
  //  4 : Motor Bike stack
  //  5 : Bicycle stack
  // --------------------------------------------------------------------------
  //  Shape : [64 X 1]     Output
  // --------------------------------------------------------------------------
  //  1 : Shape
  // --------------------------------------------------------------------------
  //  Parameter
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Initialization
  // --------------------------------------------------------------------------
  // Fusion_Object_out = coder.nullcopy(zeros([FUSION_TRACK.SHAPE_STATE_NUMBER,
  // FUSION_TRACK.TRACK_NUMBER],'double'));
  std::copy(&Fusion_Object[0], &Fusion_Object[768], &Fusion_Object_out[0]);
  //  1 : Shape
  //  2 : Vehicle stack
  //  3 : Pedestrian
  //  4 : Motor Bike stack
  //  5 : Bicycle stack
  // --------------------------------------------------------------------------
  //  Assign Shape Attribute Using Fusion Track Candidate
  // --------------------------------------------------------------------------
  for (int id_FST{0}; id_FST < 64; id_FST++) {
    double d;
    d = Association_Map[id_FST];
    if (d + Association_Map[id_FST + 64] != 0.0) {
      int Gating_Info_Old_Fusion_Track_Candidate_tmp;
      int gated_Old_Fusion_Track_Candidate_ID;
      int tmp_FVT_index;
      //  Fusion Track Candidate(k-1)과 Fusion Track Candidate(k) gating
      //  Circular gating
      //  X : [x; y]
      std::memset(&Gating_Info_Old_Fusion_Track_Candidate[0], 0,
                  192U * sizeof(double));
      //  1  : ID
      //  2  : distance between old_track and track
      //  3  : 0 = Gating fail/ 1 = Gating success
      gated_Old_Fusion_Track_Candidate_ID = -1;
      for (tmp_FVT_index = 0; tmp_FVT_index < 64; tmp_FVT_index++) {
        double absxk;
        double absxk_tmp;
        double dist_Old2Meas;
        double scale;
        double t;
        double y;
        scale = 3.3121686421112381E-170;
        dist_Old2Meas = Old_Fusion_Track_Candidate[12 * tmp_FVT_index];
        absxk = std::abs(dist_Old2Meas);
        if (absxk > 3.3121686421112381E-170) {
          y = 1.0;
          scale = absxk;
        } else {
          t = absxk / 3.3121686421112381E-170;
          y = t * t;
        }
        absxk_tmp = Old_Fusion_Track_Candidate[12 * tmp_FVT_index + 1];
        absxk = std::abs(absxk_tmp);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
        y = scale * std::sqrt(y);
        if (!(y == 0.0)) {
          scale = 3.3121686421112381E-170;
          absxk = std::abs(dist_Old2Meas - Fusion_Object[12 * id_FST]);
          if (absxk > 3.3121686421112381E-170) {
            dist_Old2Meas = 1.0;
            scale = absxk;
          } else {
            t = absxk / 3.3121686421112381E-170;
            dist_Old2Meas = t * t;
          }
          absxk = std::abs(absxk_tmp - Fusion_Object[12 * id_FST + 1]);
          if (absxk > scale) {
            t = scale / absxk;
            dist_Old2Meas = dist_Old2Meas * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            dist_Old2Meas += t * t;
          }
          dist_Old2Meas = scale * std::sqrt(dist_Old2Meas);
          Gating_Info_Old_Fusion_Track_Candidate[3 * tmp_FVT_index] =
              static_cast<double>(tmp_FVT_index) + 1.0;
          Gating_Info_Old_Fusion_Track_Candidate_tmp = 3 * tmp_FVT_index + 1;
          Gating_Info_Old_Fusion_Track_Candidate
              [Gating_Info_Old_Fusion_Track_Candidate_tmp] = dist_Old2Meas;
          if (dist_Old2Meas <= 2.5) {
            Gating_Info_Old_Fusion_Track_Candidate[3 * tmp_FVT_index + 2] = 1.0;
            if (gated_Old_Fusion_Track_Candidate_ID + 1 == 0) {
              gated_Old_Fusion_Track_Candidate_ID = tmp_FVT_index;
            } else if (Gating_Info_Old_Fusion_Track_Candidate
                           [3 * gated_Old_Fusion_Track_Candidate_ID + 1] >
                       Gating_Info_Old_Fusion_Track_Candidate
                           [Gating_Info_Old_Fusion_Track_Candidate_tmp]) {
              gated_Old_Fusion_Track_Candidate_ID = tmp_FVT_index;
            }
          }
        }
      }
      if (gated_Old_Fusion_Track_Candidate_ID + 1 != 0) {
        //  shape id(k-1) == confirm
        if ((Old_Shape[gated_Old_Fusion_Track_Candidate_ID] == 4.0) ||
            (Old_Shape[gated_Old_Fusion_Track_Candidate_ID] == 6.0) ||
            (Old_Shape[gated_Old_Fusion_Track_Candidate_ID] == 10.0) ||
            (Old_Shape[gated_Old_Fusion_Track_Candidate_ID] == 8.0)) {
          if (d != 0.0) {
            for (Gating_Info_Old_Fusion_Track_Candidate_tmp = 0;
                 Gating_Info_Old_Fusion_Track_Candidate_tmp < 5;
                 Gating_Info_Old_Fusion_Track_Candidate_tmp++) {
              tmp_FVT_index = Gating_Info_Old_Fusion_Track_Candidate_tmp << 6;
              Shape_ID[id_FST + tmp_FVT_index] =
                  Old_Shape[gated_Old_Fusion_Track_Candidate_ID +
                            tmp_FVT_index];
            }
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          }
        } else {
          //  stack +
          if (d != 0.0) {
            bool exitg1;
            // --------------------------------------------------------------------------
            //  function
            // --------------------------------------------------------------------------
            tmp_FVT_index = -1;
            Gating_Info_Old_Fusion_Track_Candidate_tmp = 0;
            exitg1 = false;
            while ((!exitg1) &&
                   (Gating_Info_Old_Fusion_Track_Candidate_tmp < 10)) {
              if (Front_Vision_Track
                      [36 * Gating_Info_Old_Fusion_Track_Candidate_tmp + 6] ==
                  Association_Map[id_FST]) {
                tmp_FVT_index = Gating_Info_Old_Fusion_Track_Candidate_tmp;
                exitg1 = true;
              } else {
                Gating_Info_Old_Fusion_Track_Candidate_tmp++;
              }
            }
            d = Front_Vision_Track[36 * tmp_FVT_index];
            if ((d == 2.0) || (d == 1.0)) {
              Shape_ID[id_FST] = 3.0;
              Shape_ID[id_FST + 64] =
                  Old_Shape[gated_Old_Fusion_Track_Candidate_ID + 64] + 1.0;
            } else if (d == 5.0) {
              Shape_ID[id_FST] = 5.0;
              Shape_ID[id_FST + 128] =
                  Old_Shape[gated_Old_Fusion_Track_Candidate_ID + 128] + 1.0;
            } else if (d == 3.0) {
              Shape_ID[id_FST] = 7.0;
              Shape_ID[id_FST + 192] =
                  Old_Shape[gated_Old_Fusion_Track_Candidate_ID + 192] + 1.0;
            } else if (d == 4.0) {
              Shape_ID[id_FST] = 9.0;
              Shape_ID[id_FST + 256] =
                  Old_Shape[gated_Old_Fusion_Track_Candidate_ID + 256] + 1.0;
            }
          }
          //  veh
          if (Shape_ID[id_FST + 64] > 20.0) {
            Shape_ID[id_FST] = 4.0;
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          } else if (Shape_ID[id_FST] != 0.0) {
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          }
          //  ped
          if (Shape_ID[id_FST + 128] > 20.0) {
            Shape_ID[id_FST] = 6.0;
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          } else if (Shape_ID[id_FST] != 0.0) {
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          }
          //  motor bike
          if (Shape_ID[id_FST + 192] > 20.0) {
            Shape_ID[id_FST] = 8.0;
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          } else if (Shape_ID[id_FST] != 0.0) {
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          }
          //  bicycle
          if (Shape_ID[id_FST + 256] > 20.0) {
            Shape_ID[id_FST] = 10.0;
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          } else if (Shape_ID[id_FST] != 0.0) {
            Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
          }
        }
      } else if (d != 0.0) {
        bool exitg1;
        // --------------------------------------------------------------------------
        //  function
        // --------------------------------------------------------------------------
        tmp_FVT_index = -1;
        Gating_Info_Old_Fusion_Track_Candidate_tmp = 0;
        exitg1 = false;
        while ((!exitg1) && (Gating_Info_Old_Fusion_Track_Candidate_tmp < 10)) {
          if (Front_Vision_Track
                  [36 * Gating_Info_Old_Fusion_Track_Candidate_tmp + 6] ==
              Association_Map[id_FST]) {
            tmp_FVT_index = Gating_Info_Old_Fusion_Track_Candidate_tmp;
            exitg1 = true;
          } else {
            Gating_Info_Old_Fusion_Track_Candidate_tmp++;
          }
        }
        d = Front_Vision_Track[36 * tmp_FVT_index];
        if ((d == 2.0) || (d == 1.0)) {
          Shape_ID[id_FST] = 3.0;
          Shape_ID[id_FST + 64] = 1.0;
        } else if (d == 5.0) {
          Shape_ID[id_FST] = 5.0;
          Shape_ID[id_FST + 128] = 1.0;
        } else if (d == 3.0) {
          Shape_ID[id_FST] = 7.0;
          Shape_ID[id_FST + 192] = 1.0;
        } else if (d == 4.0) {
          Shape_ID[id_FST] = 9.0;
          Shape_ID[id_FST + 256] = 1.0;
        }
        if (Shape_ID[id_FST] != 0.0) {
          Fusion_Object_out[12 * id_FST + 11] = Shape_ID[id_FST];
        }
      }
    }
  }
}

//
// File trailer for shape_attribute.cpp
//
// [EOF]
//
