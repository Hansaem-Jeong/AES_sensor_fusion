//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: track_management.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "track_management.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double Fusion_Track_Updated[1280]
//                const double P_Fusion_Track_Updated[1024]
//                const double Association_Map_Updated[128]
//                const double Association_Map[128]
//                const double Fusion_Object[128]
//                float Road_Curvature
//                float Road_Slope
//                const double Front_Vision_Lane[68]
//                double Fusion_Track_out[1280]
//                double Association_Map_out[128]
//                double P_Fusion_Track_out[1024]
// Return Type  : void
//
void track_management(const double Fusion_Track_Updated[1280],
                      const double P_Fusion_Track_Updated[1024],
                      const double Association_Map_Updated[128],
                      const double Association_Map[128],
                      const double Fusion_Object[128], float Road_Curvature,
                      float, const double Front_Vision_Lane[68],
                      double Fusion_Track_out[1280],
                      double Association_Map_out[128],
                      double P_Fusion_Track_out[1024])
{
  double Fusion_Track_out_tmp;
  double d;
  int Fusion_Object_Assigned_Flag;
  int Fusion_Object_Exist_Flag;
  int b_id_FST;
  int id_FO;
  int id_FST;
  bool exitg1;
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  // --------------------------------------------------------------------------
  //  Fusion_Track_Updated : [20 X 64]     Input
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
  //  P_Fusion_Track_Updated : [4 X 4 X 64]  Input
  // --------------------------------------------------------------------------
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  // --------------------------------------------------------------------------
  //  Association_Map_Updated : [64 X 2]     Input
  // --------------------------------------------------------------------------
  //  1  : Front Vision Track
  //  2  : Front Radar Track
  // --------------------------------------------------------------------------
  //  Association_Map : [64 X 2]     Input
  // --------------------------------------------------------------------------
  //  1  : Front Vision Track
  //  2  : Front Radar Track
  // --------------------------------------------------------------------------
  //  Front_Vision_Lane : [34 X 2(Left, Right)]    Input
  // --------------------------------------------------------------------------
  //  1  : View Start Longitudinal Distance
  //  2  : View End Longitudinal Distance
  //  3  : Lane Mark Confidence h
  //  4  : Lane Mark Confidence n
  //  5  : Lane Prediction
  //  6  : Neighbor Avail
  //  7  : Neighbor Type
  //  8  : Guardrail
  //  9  : Highway Merge
  //  10  : Highway Exit
  //  11 : Lane Color
  //  12 : View Range Start Point
  //  13 : Neighbor Distance [m]
  //  14 : Neighbor Road Slope [rad]
  //  15 : Neighbor Curvature [1/m]
  //  16 : Neighbor Curvature Rate [1/m^2]
  //  17 : Classification
  //  18 : Confidence
  //  19 : Marker Width
  //  20 : Distance [m]
  //  21 : Road Slope [rad]
  //  22 : Curvature [1/m]
  //  23 : Curvature Rate [1/m^2]
  //  24 : Consturction Area
  //  25 : LDW Availability
  //  26 : LDW Status
  //  27 : Preprocessing(Coordinate Transform) Distance
  //  28 : Preprocessing(Coordinate Transform) Road Slope
  //  29 : Preprocessing(Coordinate Transform) Curvature
  //  30 : Preprocessing(Coordinate Transform) Curvature Rate
  //  31 : Preprocessing(Coordinate Transform) Next Distance
  //  32 : Preprocessing(Coordinate Transform) Next Road Slope
  //  33 : Preprocessing(Coordinate Transform) Next Curvature
  //  34 : Preprocessing(Coordinate Transform) Next Curvature Rate
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
  //  Fusion_Track_out : [20 X 64]     Output
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
  //  13 : (Tracking) Relative position Y
  //  14 : (Tracking) Relative position X
  //  15 : (Tracking) Relative velocity Y
  //  16 : (Tracking) Relative velocity X
  //  17 : Updated Age
  //  18 : Coasting Age
  //  19 : Life Time
  //  20 : Relative normal position with respect to lane
  // --------------------------------------------------------------------------
  //  Association_Map_out : [64 X 2]     Output
  // --------------------------------------------------------------------------
  //  1  : Front Vision Track
  //  2  : Front Radar Track
  // --------------------------------------------------------------------------
  //  P_Fusion_Track_out : [4 X 4 X 32]     Output
  // --------------------------------------------------------------------------
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  // --------------------------------------------------------------------------
  //  Parameter
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  initialization
  // --------------------------------------------------------------------------
  std::copy(&Association_Map_Updated[0], &Association_Map_Updated[128],
            &Association_Map_out[0]);
  Fusion_Object_Assigned_Flag = 0;
  Fusion_Object_Exist_Flag = 0;
  // --------------------------------------------------------------------------
  //  Track management - Maintenance
  // --------------------------------------------------------------------------
  for (id_FO = 0; id_FO < 64; id_FO++) {
    Fusion_Track_out_tmp = Association_Map[id_FO + 64];
    if (Association_Map[id_FO] + Fusion_Track_out_tmp != 0.0) {
      d = Fusion_Object[(id_FO << 6) + 11];
      if ((d == 3.0) || (d == 4.0) || (d == 5.0) || (d == 6.0) || (d == 7.0) ||
          (d == 8.0) || (d == 9.0) || (d == 10.0)) {
        id_FST = 0;
        b_id_FST = 0;
        exitg1 = false;
        while ((!exitg1) && (b_id_FST < 64)) {
          id_FST = b_id_FST;
          d = Association_Map_Updated[b_id_FST + 64];
          if ((Association_Map_Updated[b_id_FST] + d != 0.0) &&
              (Association_Map[id_FO] == Association_Map_Updated[b_id_FST]) &&
              (Fusion_Track_out_tmp == d)) {
            d = Fusion_Track_Updated[20 * b_id_FST + 11];
            if ((d == 3.0) || (d == 4.0) || (d == 5.0) || (d == 6.0) ||
                (d == 7.0) || (d == 8.0) || (d == 9.0) || (d == 10.0)) {
              Fusion_Object_Assigned_Flag = 1;
              exitg1 = true;
            } else {
              b_id_FST++;
            }
          } else {
            b_id_FST++;
          }
        }
        if (Fusion_Object_Assigned_Flag == 1) {
          std::copy(&Fusion_Track_Updated[id_FST * 20],
                    &Fusion_Track_Updated[static_cast<int>(id_FST * 20 + 20U)],
                    &Fusion_Track_out[id_FST * 20]);
          for (Fusion_Object_Assigned_Flag = 0; Fusion_Object_Assigned_Flag < 4;
               Fusion_Object_Assigned_Flag++) {
            b_id_FST = (Fusion_Object_Assigned_Flag << 2) + (id_FST << 4);
            P_Fusion_Track_out[b_id_FST] = P_Fusion_Track_Updated[b_id_FST];
            P_Fusion_Track_out[b_id_FST + 1] =
                P_Fusion_Track_Updated[b_id_FST + 1];
            P_Fusion_Track_out[b_id_FST + 2] =
                P_Fusion_Track_Updated[b_id_FST + 2];
            P_Fusion_Track_out[b_id_FST + 3] =
                P_Fusion_Track_Updated[b_id_FST + 3];
          }
          //  updated_age +1
          Fusion_Object_Assigned_Flag = 20 * id_FST + 16;
          Fusion_Track_out[Fusion_Object_Assigned_Flag] =
              Fusion_Track_Updated[Fusion_Object_Assigned_Flag] + 1.0;
          //  coasting_age -1
          Fusion_Object_Assigned_Flag = 20 * id_FST + 17;
          Fusion_Track_out_tmp =
              Fusion_Track_Updated[Fusion_Object_Assigned_Flag];
          if (Fusion_Track_out_tmp > 0.0) {
            Fusion_Track_out[Fusion_Object_Assigned_Flag] =
                Fusion_Track_out_tmp - 1.0;
          }
          //  life time +1
          Fusion_Object_Assigned_Flag = 20 * id_FST + 18;
          Fusion_Track_out[Fusion_Object_Assigned_Flag] =
              Fusion_Track_Updated[Fusion_Object_Assigned_Flag] + 1.0;
          if (Fusion_Track_out[Fusion_Object_Assigned_Flag] > 3.0) {
            //  3
            Fusion_Track_out[Fusion_Object_Assigned_Flag] = 3.0;
          }
          Fusion_Object_Assigned_Flag = 0;
        }
      }
    }
  }
  // --------------------------------------------------------------------------
  //  Track management - Creation
  // --------------------------------------------------------------------------
  //  create track from unassigned Fusion Object in Association_Map
  //  ussasinged = Association_Map_Updated(X), Association_Map(O)
  for (id_FO = 0; id_FO < 64; id_FO++) {
    Fusion_Track_out_tmp = Association_Map[id_FO + 64];
    if (Association_Map[id_FO] + Fusion_Track_out_tmp != 0.0) {
      id_FST = 0;
      exitg1 = false;
      while ((!exitg1) && (id_FST < 64)) {
        d = Association_Map_Updated[id_FST + 64];
        if ((Association_Map_Updated[id_FST] + d != 0.0) &&
            (Association_Map[id_FO] == Association_Map_Updated[id_FST]) &&
            (Fusion_Track_out_tmp == d)) {
          Fusion_Object_Assigned_Flag = 1;
          exitg1 = true;
        } else {
          id_FST++;
        }
      }
      if (Fusion_Object_Assigned_Flag == 0) {
        id_FST = 0;
        exitg1 = false;
        while ((!exitg1) && (id_FST < 64)) {
          if (Association_Map_out[id_FST] + Association_Map_out[id_FST + 64] ==
              0.0) {
            Association_Map_out[id_FST] = Association_Map[id_FO];
            Association_Map_out[id_FST + 64] = Fusion_Track_out_tmp;
            std::copy(&Fusion_Object[id_FO * 64],
                      &Fusion_Object[static_cast<int>(id_FO * 64 + 12U)],
                      &Fusion_Track_out[id_FST * 20]);
            Fusion_Object_Assigned_Flag = id_FO << 6;
            Fusion_Track_out[20 * id_FST + 12] =
                Fusion_Object[Fusion_Object_Assigned_Flag];
            Fusion_Track_out[20 * id_FST + 13] =
                Fusion_Object[Fusion_Object_Assigned_Flag + 1];
            Fusion_Track_out[20 * id_FST + 14] =
                Fusion_Object[Fusion_Object_Assigned_Flag + 2];
            Fusion_Track_out[20 * id_FST + 15] =
                Fusion_Object[Fusion_Object_Assigned_Flag + 3];
            //  P_Fusion_Track_Updated
            for (Fusion_Object_Assigned_Flag = 0;
                 Fusion_Object_Assigned_Flag < 4;
                 Fusion_Object_Assigned_Flag++) {
              b_id_FST = (Fusion_Object_Assigned_Flag << 2) + (id_FST << 4);
              P_Fusion_Track_out[b_id_FST] = 0.0;
              P_Fusion_Track_out[b_id_FST + 1] = 0.0;
              P_Fusion_Track_out[b_id_FST + 2] = 0.0;
              P_Fusion_Track_out[b_id_FST + 3] = 0.0;
            }
            b_id_FST = id_FST << 4;
            P_Fusion_Track_out[b_id_FST] = 1.0;
            P_Fusion_Track_out[b_id_FST + 5] = 1.0;
            P_Fusion_Track_out[b_id_FST + 10] = 1.0;
            P_Fusion_Track_out[b_id_FST + 15] = 1.0;
            Fusion_Track_out[20 * id_FST + 16] = 1.0;
            Fusion_Track_out[20 * id_FST + 17] = 0.0;
            Fusion_Track_out[20 * id_FST + 18] = 1.0;
            exitg1 = true;
          } else {
            id_FST++;
          }
        }
      }
      Fusion_Object_Assigned_Flag = 0;
    }
  }
  // --------------------------------------------------------------------------
  //  Track management - Deletion
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Post fusion - Coordinate with respect to lane
  // --------------------------------------------------------------------------
  for (id_FST = 0; id_FST < 64; id_FST++) {
    Fusion_Track_out_tmp = Association_Map_Updated[id_FST + 64];
    if (Association_Map_Updated[id_FST] + Fusion_Track_out_tmp != 0.0) {
      id_FO = 0;
      exitg1 = false;
      while ((!exitg1) && (id_FO < 64)) {
        d = Association_Map[id_FO + 64];
        if ((Association_Map[id_FO] + d != 0.0) &&
            (Association_Map_Updated[id_FST] == Association_Map[id_FO]) &&
            (Fusion_Track_out_tmp == d)) {
          Fusion_Object_Exist_Flag = 1;
          exitg1 = true;
        } else {
          id_FO++;
        }
      }
      if (Fusion_Object_Exist_Flag == 0) {
        //  coasting age +1, if coasting age > 1, life time -1
        std::copy(&Fusion_Track_Updated[id_FST * 20],
                  &Fusion_Track_Updated[static_cast<int>(id_FST * 20 + 20U)],
                  &Fusion_Track_out[id_FST * 20]);
        for (Fusion_Object_Assigned_Flag = 0; Fusion_Object_Assigned_Flag < 4;
             Fusion_Object_Assigned_Flag++) {
          b_id_FST = (Fusion_Object_Assigned_Flag << 2) + (id_FST << 4);
          P_Fusion_Track_out[b_id_FST] = P_Fusion_Track_Updated[b_id_FST];
          P_Fusion_Track_out[b_id_FST + 1] =
              P_Fusion_Track_Updated[b_id_FST + 1];
          P_Fusion_Track_out[b_id_FST + 2] =
              P_Fusion_Track_Updated[b_id_FST + 2];
          P_Fusion_Track_out[b_id_FST + 3] =
              P_Fusion_Track_Updated[b_id_FST + 3];
        }
        Fusion_Object_Assigned_Flag = 20 * id_FST + 17;
        Fusion_Track_out_tmp =
            Fusion_Track_Updated[Fusion_Object_Assigned_Flag] + 1.0;
        Fusion_Track_out[Fusion_Object_Assigned_Flag] = Fusion_Track_out_tmp;
        if (Fusion_Track_out_tmp > 0.0) {
          Fusion_Object_Assigned_Flag = 20 * id_FST + 18;
          Fusion_Track_out[Fusion_Object_Assigned_Flag] =
              Fusion_Track_Updated[Fusion_Object_Assigned_Flag] - 1.0;
        }
        if (Fusion_Track_out[20 * id_FST + 18] < 0.0) {
          std::memset(&Fusion_Track_out[id_FST * 20], 0, 20U * sizeof(double));
          for (Fusion_Object_Assigned_Flag = 0; Fusion_Object_Assigned_Flag < 4;
               Fusion_Object_Assigned_Flag++) {
            b_id_FST = (Fusion_Object_Assigned_Flag << 2) + (id_FST << 4);
            P_Fusion_Track_out[b_id_FST] = 0.0;
            P_Fusion_Track_out[b_id_FST + 1] = 0.0;
            P_Fusion_Track_out[b_id_FST + 2] = 0.0;
            P_Fusion_Track_out[b_id_FST + 3] = 0.0;
          }
          Association_Map_out[id_FST] = 0.0;
          Association_Map_out[id_FST + 64] = 0.0;
        }
      }
      Fusion_Object_Exist_Flag = 0;
    }
    if (Association_Map_out[id_FST] + Association_Map_out[id_FST + 64] != 0.0) {
      if ((Front_Vision_Lane[17] >= 3.0) || (Front_Vision_Lane[51] >= 3.0)) {
        if (std::abs(Road_Curvature) < 0.0005) {
          //  staright
          Fusion_Track_out[20 * id_FST + 19] = Fusion_Track_out[20 * id_FST];
        } else {
          float a;
          //  curve
          a = 1.0F / Road_Curvature -
              static_cast<float>(Fusion_Track_out[20 * id_FST]);
          Fusion_Track_out_tmp = Fusion_Track_out[20 * id_FST + 1];
          Fusion_Track_out[20 * id_FST + 19] =
              std::abs(1.0F / Road_Curvature) -
              std::sqrt(a * a + static_cast<float>(Fusion_Track_out_tmp *
                                                   Fusion_Track_out_tmp));
        }
      } else {
        Fusion_Track_out[20 * id_FST + 19] = Fusion_Track_out[20 * id_FST];
      }
    }
  }
}

//
// File trailer for track_management.cpp
//
// [EOF]
//
