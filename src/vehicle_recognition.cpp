//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: vehicle_recognition.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "vehicle_recognition.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"
#include <algorithm>
#include <cmath>

// Function Definitions
//
// Arguments    : const double Fusion_Track[1280]
//                const double Association_Map_out[128]
//                float Road_Curvature
//                const double old_rear_object_lane[64]
//                const double old_object_lane_total[64]
//                double Fusion_Track_Recognition[1408]
//                double AVL[9]
//                double AVR[9]
//                double RVL[9]
//                double RVI[9]
//                double RVR[9]
//                double FVL[9]
//                double FVI[9]
//                double FVR[9]
//                double rear_object_lane[64]
//                double object_lane_total[64]
// Return Type  : void
//
void vehicle_recognition(
    const double Fusion_Track[1280], const double Association_Map_out[128],
    float Road_Curvature, const double old_rear_object_lane[64],
    const double old_object_lane_total[64],
    double Fusion_Track_Recognition[1408], double AVL[9], double AVR[9],
    double RVL[9], double RVI[9], double RVR[9], double FVL[9], double FVI[9],
    double FVR[9], double rear_object_lane[64], double object_lane_total[64])
{
  double tmp_AVL_candidate[1408];
  double tmp_AVR_candidate[1408];
  double tmp_FVI_candidate[1408];
  double tmp_FVL_candidate[1408];
  double tmp_FVR_candidate[1408];
  double tmp_RVI_candidate[1408];
  double tmp_RVL_candidate[1408];
  double tmp_RVR_candidate[1408];
  double left_threhold_total[64];
  double poffset_total[64];
  double right_threhold_total[64];
  double tmp_AVL[22];
  double tmp_AVR[22];
  double tmp_FVI[22];
  double tmp_FVL[22];
  double tmp_FVR[22];
  double tmp_RVI[22];
  double tmp_RVL[22];
  double tmp_RVR[22];
  double d;
  double d1;
  double dist_to_ego;
  double inlaneRange;
  double inlaneRange_Rear;
  double leftRange;
  double leftRange_Adjacent;
  double leftRange_Rear;
  double rightRange;
  double rightRange_Adjacent;
  double rightRange_Rear;
  double tmp_AVL_ID;
  double tmp_AVR_ID;
  double tmp_FVI_ID;
  double tmp_FVL_ID;
  double tmp_FVR_ID;
  double tmp_RVI_ID;
  double tmp_RVL_ID;
  double tmp_RVR_ID;
  int id_FST;
  int status_flag;
  int valid_Adjacent_left_num;
  int valid_Adjacent_right_num;
  int valid_Rear_inlane_num;
  int valid_Rear_left_num;
  int valid_Rear_right_num;
  int valid_inlane_num;
  int valid_left_num;
  int valid_right_num;
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  // --------------------------------------------------------------------------
  //  Fusion_Track : [20 X 64]     Input
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
  //  Fusion_Track_Recognition : [22 X 64]     Output
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
  //  21 : ID
  //  22 : Recognition
  // --------------------------------------------------------------------------
  //  FVL, FVI, ... RVR : [8 X 1]     Output
  // --------------------------------------------------------------------------
  //  1  : ID
  //  1  : Relative position Y
  //  2  : Relative position X
  //  3  : Relative velocity Y
  //  4  : Relative velocity X
  //  5  : Width
  //  6  : Length
  //  7  : Heading angle
  // --------------------------------------------------------------------------
  //  Parameter
  // --------------------------------------------------------------------------
  //  Vehicle width
  //  cut_in = 0;
  // --------------------------------------------------------------------------
  //  initialization
  // --------------------------------------------------------------------------
  valid_Adjacent_right_num = -1;
  valid_Adjacent_left_num = -1;
  valid_Rear_inlane_num = -1;
  valid_Rear_right_num = -1;
  valid_Rear_left_num = -1;
  tmp_FVL_ID = 0.0;
  tmp_FVI_ID = 0.0;
  tmp_FVR_ID = 0.0;
  tmp_AVL_ID = 0.0;
  tmp_AVR_ID = 0.0;
  tmp_RVL_ID = 0.0;
  tmp_RVI_ID = 0.0;
  tmp_RVR_ID = 0.0;
  inlaneRange = 150.0;
  rightRange = 100.0;
  leftRange = 100.0;
  inlaneRange_Rear = 150.0;
  rightRange_Rear = 100.0;
  leftRange_Rear = 100.0;
  rightRange_Adjacent = 100.0;
  leftRange_Adjacent = 100.0;
  valid_inlane_num = -1;
  valid_right_num = -1;
  valid_left_num = -1;
  for (status_flag = 0; status_flag < 64; status_flag++) {
    std::copy(&Fusion_Track[status_flag * 20],
              &Fusion_Track[static_cast<int>(status_flag * 20 + 20U)],
              &Fusion_Track_Recognition[status_flag * 22]);
    poffset_total[status_flag] =
        Fusion_Track_Recognition[22 * status_flag + 19];
    object_lane_total[status_flag] = old_object_lane_total[status_flag];
    rear_object_lane[status_flag] = old_rear_object_lane[status_flag];
  }
  // --------------------------------------------------------------------------
  //  Vehicle Recognition
  // --------------------------------------------------------------------------
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //  status estimation
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // ---------   stright  --------  %%
  if (std::abs(Road_Curvature) <= 0.0005) {
    //  stright road
    status_flag = 1;
    // ---------   curve  --------  %%
  } else {
    //  curve road
    status_flag = 2;
  }
  for (id_FST = 0; id_FST < 64; id_FST++) {
    if (((Association_Map_out[id_FST] + Association_Map_out[id_FST + 64] !=
          0.0) &&
         (Fusion_Track_Recognition[22 * id_FST + 11] == 3.0)) ||
        (Fusion_Track_Recognition[22 * id_FST + 11] == 4.0)) {
      bool guard1{false};
      bool guard2{false};
      d = std::abs(poffset_total[id_FST]);
      guard1 = false;
      guard2 = false;
      if (d < 50.0) {
        d1 = Fusion_Track_Recognition[22 * id_FST + 1];
        if ((d1 < 150.0) && (d1 > -2.0)) {
          // ---------   set threshold  --------  %%
          if (object_lane_total[id_FST] == 0.0) {
            //  first loop
            if (d1 > 70.0) {
              if (status_flag == 1) {
                //  straight
                right_threhold_total[id_FST] = -1.8;
                //  -1.80
                left_threhold_total[id_FST] = 1.8;
                //  +1.80
              } else {
                // curve
                right_threhold_total[id_FST] = -1.9;
                //  -1.9
                left_threhold_total[id_FST] = 1.9;
                //  +1.9
              }
            } else if (d1 > 17.5) {
              if (status_flag == 1) {
                right_threhold_total[id_FST] = -1.65;
                //  -1.65
                left_threhold_total[id_FST] = 1.65;
                //  +1.65
              } else {
                right_threhold_total[id_FST] = -1.8;
                //  -1.8
                left_threhold_total[id_FST] = 1.8;
                //  +1.8
              }
            } else if (status_flag == 1) {
              right_threhold_total[id_FST] = -1.55;
              //  -1.55
              left_threhold_total[id_FST] = 1.55;
              //  +1.55
            } else {
              right_threhold_total[id_FST] = -1.55;
              //  -1.55
              left_threhold_total[id_FST] = 1.55;
              //  +1.55
            }
          } else if (object_lane_total[id_FST] == 1.0) {
            //  inlane case
            if (d1 > 70.0) {
              if (status_flag == 1) {
                //  straight
                right_threhold_total[id_FST] = -1.85;
                //  -1.85
                left_threhold_total[id_FST] = 1.85;
                //  +1.85
              } else {
                // curve
                right_threhold_total[id_FST] = -2.05;
                //  -2.05
                left_threhold_total[id_FST] = 2.05;
                //  +2.05
              }
            } else if (d1 > 17.5) {
              if (status_flag == 1) {
                right_threhold_total[id_FST] = -1.75;
                //  -1.75
                left_threhold_total[id_FST] = 1.75;
                //  +1.75
              } else {
                right_threhold_total[id_FST] = -1.85;
                //  -1.85
                left_threhold_total[id_FST] = 1.85;
                //  +1.85
              }
            } else if (status_flag == 1) {
              right_threhold_total[id_FST] = -1.55;
              //  -1.55
              left_threhold_total[id_FST] = 1.55;
              //  +1.55618821844625
            } else {
              right_threhold_total[id_FST] = -1.55;
              //  -1.55
              left_threhold_total[id_FST] = 1.55;
              //  +1.55
            }
          } else if (object_lane_total[id_FST] == 2.0) {
            //  rightlane case
            if (d1 > 70.0) {
              if (status_flag == 1) {
                //  straight
                right_threhold_total[id_FST] = -1.75;
                //  -1.75
                left_threhold_total[id_FST] = 1.75;
                //  +1.75
              } else {
                // curve
                right_threhold_total[id_FST] = -1.85;
                //  -1.85
                left_threhold_total[id_FST] = 1.85;
                //  +1.85
              }
            } else if (d1 > 17.5) {
              if (status_flag == 1) {
                right_threhold_total[id_FST] = -1.7;
                //  -1.7
                left_threhold_total[id_FST] = 1.7;
                //  +1.7
              } else {
                right_threhold_total[id_FST] = -1.8;
                //  -1.8
                left_threhold_total[id_FST] = 1.8;
                //  +1.8
              }
            } else if (status_flag == 1) {
              right_threhold_total[id_FST] = -1.55;
              //  -1.55
              left_threhold_total[id_FST] = 1.55;
              //  +1.55
            } else {
              right_threhold_total[id_FST] = -1.55;
              //  -1.55
              left_threhold_total[id_FST] = 1.55;
              //  +1.55
            }
          } else if (object_lane_total[id_FST] == 3.0) {
            //  leftlane case
            if (d1 > 70.0) {
              if (status_flag == 1) {
                //  straight
                right_threhold_total[id_FST] = -1.75;
                //  -1.75
                left_threhold_total[id_FST] = 1.75;
                //  +1.75
              } else {
                // curve
                right_threhold_total[id_FST] = -1.85;
                //  -1.85
                left_threhold_total[id_FST] = 1.85;
                //  +1.85
              }
            } else if (d1 > 17.5) {
              if (status_flag == 1) {
                right_threhold_total[id_FST] = -1.7;
                //  -1.65
                left_threhold_total[id_FST] = 1.7;
                //  +1.65
              } else {
                right_threhold_total[id_FST] = -1.8;
                //  -1.8
                left_threhold_total[id_FST] = 1.8;
                //  +1.8
              }
            } else if (status_flag == 1) {
              right_threhold_total[id_FST] = -1.55;
              //  -1.55
              left_threhold_total[id_FST] = 1.55;
              //  +1.55
            } else {
              right_threhold_total[id_FST] = -1.55;
              //  -1.55
              left_threhold_total[id_FST] = 1.55;
              //  +1.55
            }
          }
          // -------------------------   left  ----  %%
          if (poffset_total[id_FST] > left_threhold_total[id_FST]) {
            valid_left_num++;
            Fusion_Track_Recognition[22 * id_FST + 20] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition[22 * id_FST + 21] = 101.0;
            std::copy(
                &Fusion_Track_Recognition[id_FST * 22],
                &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 + 22U)],
                &tmp_FVL_candidate[valid_left_num * 22]);
            object_lane_total[id_FST] = 3.0;
            //  lane info : leftlane
            // ------------------------  inlane  ---- %%
          } else if ((poffset_total[id_FST] >= right_threhold_total[id_FST]) &&
                     (poffset_total[id_FST] <= left_threhold_total[id_FST])) {
            valid_inlane_num++;
            Fusion_Track_Recognition[22 * id_FST + 20] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition[22 * id_FST + 21] = 102.0;
            std::copy(
                &Fusion_Track_Recognition[id_FST * 22],
                &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 + 22U)],
                &tmp_FVI_candidate[valid_inlane_num * 22]);
            object_lane_total[id_FST] = 1.0;
            //  lane info : inlane
            // -------------------------   right ----  %%
          } else if (poffset_total[id_FST] < right_threhold_total[id_FST]) {
            valid_right_num++;
            Fusion_Track_Recognition[22 * id_FST + 20] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition[22 * id_FST + 21] = 103.0;
            std::copy(
                &Fusion_Track_Recognition[id_FST * 22],
                &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 + 22U)],
                &tmp_FVR_candidate[valid_right_num * 22]);
            object_lane_total[id_FST] = 2.0;
            //  lane info : rightlane
          }
        } else {
          guard2 = true;
        }
      } else {
        guard2 = true;
      }
      if (guard2) {
        if (d < 10.0) {
          d1 = Fusion_Track_Recognition[22 * id_FST + 1];
          if ((d1 <= -2.0) && (d1 > -5.0)) {
            //  AV
            // ---------   set threshold  --------  %%
            if (object_lane_total[id_FST] == 0.0) {
              //  first loop
              if (status_flag == 1) {
                right_threhold_total[id_FST] = -1.6;
                //  +1.6
                left_threhold_total[id_FST] = 1.6;
                //  -1.6
              } else {
                right_threhold_total[id_FST] = -1.6;
                //  +1.6
                left_threhold_total[id_FST] = 1.6;
                //  -1.6
              }
            } else if (object_lane_total[id_FST] == 1.0) {
              //  inlane case
              if (status_flag == 1) {
                right_threhold_total[id_FST] = -1.55;
                //  +1.55
                left_threhold_total[id_FST] = 1.55;
                //  -1.55
              } else {
                right_threhold_total[id_FST] = -1.55;
                //  +1.55
                left_threhold_total[id_FST] = 1.55;
                //  -1.55
              }
            } else if (object_lane_total[id_FST] == 2.0) {
              //  rightlane case
              if (status_flag == 1) {
                right_threhold_total[id_FST] = -1.55;
                //  +1.55
                left_threhold_total[id_FST] = 1.55;
                //  -1.55
              } else {
                right_threhold_total[id_FST] = -1.55;
                //  +1.55
                left_threhold_total[id_FST] = 1.55;
                //  -1.55
              }
            } else if (object_lane_total[id_FST] == 3.0) {
              //  leftlane case
              if (status_flag == 1) {
                right_threhold_total[id_FST] = -1.55;
                //  +1.55
                left_threhold_total[id_FST] = 1.55;
                //  -1.55
              } else {
                right_threhold_total[id_FST] = -1.55;
                //  +1.55
                left_threhold_total[id_FST] = 1.55;
                //  -1.55
              }
            }
            // ------------------------ Adjacent inlane  ---- %%
            if ((poffset_total[id_FST] >= right_threhold_total[id_FST]) &&
                (poffset_total[id_FST] <= left_threhold_total[id_FST])) {
              if (poffset_total[id_FST] < 0.0) {
                valid_Adjacent_right_num++;
                Fusion_Track_Recognition[22 * id_FST + 20] =
                    static_cast<double>(id_FST) + 1.0;
                Fusion_Track_Recognition[22 * id_FST + 21] = 105.0;
                std::copy(&Fusion_Track_Recognition[id_FST * 22],
                          &Fusion_Track_Recognition[static_cast<int>(
                              id_FST * 22 + 22U)],
                          &tmp_AVR_candidate[valid_Adjacent_right_num * 22]);
                object_lane_total[id_FST] = 2.0;
                //  lane info : rightlane
              } else {
                valid_Adjacent_left_num++;
                Fusion_Track_Recognition[22 * id_FST + 20] =
                    static_cast<double>(id_FST) + 1.0;
                Fusion_Track_Recognition[22 * id_FST + 21] = 104.0;
                std::copy(&Fusion_Track_Recognition[id_FST * 22],
                          &Fusion_Track_Recognition[static_cast<int>(
                              id_FST * 22 + 22U)],
                          &tmp_AVL_candidate[valid_Adjacent_left_num * 22]);
                object_lane_total[id_FST] = 3.0;
                //  lane info : leftlane
              }
              // -------------------------   left  ----  %%
            } else if (poffset_total[id_FST] > left_threhold_total[id_FST]) {
              valid_Adjacent_left_num++;
              Fusion_Track_Recognition[22 * id_FST + 20] =
                  static_cast<double>(id_FST) + 1.0;
              Fusion_Track_Recognition[22 * id_FST + 21] = 104.0;
              std::copy(&Fusion_Track_Recognition[id_FST * 22],
                        &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 +
                                                                   22U)],
                        &tmp_AVL_candidate[valid_Adjacent_left_num * 22]);
              object_lane_total[id_FST] = 3.0;
              //  lane info : leftlane
              // -------------------------  Adjacent right ----  %%
            } else if (poffset_total[id_FST] < right_threhold_total[id_FST]) {
              valid_Adjacent_right_num++;
              Fusion_Track_Recognition[22 * id_FST + 20] =
                  static_cast<double>(id_FST) + 1.0;
              Fusion_Track_Recognition[22 * id_FST + 21] = 105.0;
              std::copy(&Fusion_Track_Recognition[id_FST * 22],
                        &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 +
                                                                   22U)],
                        &tmp_AVR_candidate[valid_Adjacent_right_num * 22]);
              object_lane_total[id_FST] = 2.0;
              //  lane info : rightlane
            }
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }
      }
      if (guard1 && (d < 10.0)) {
        d = Fusion_Track_Recognition[22 * id_FST + 1];
        if ((d <= -5.0) && (d > -70.0)) {
          //  RV
          // %%---------- set threshold ----------%%%
          if (old_rear_object_lane[id_FST] == 0.0) {
            //  first loop
            if (status_flag == 1) {
              right_threhold_total[id_FST] = -1.6;
              //  +1.6
              left_threhold_total[id_FST] = 1.6;
              //  -1.6
            } else {
              right_threhold_total[id_FST] = -1.6;
              //  +1.6
              left_threhold_total[id_FST] = 1.6;
              //  -1.6
            }
          } else if (old_rear_object_lane[id_FST] == 1.0) {
            //  Inlane
            if (status_flag == 1) {
              right_threhold_total[id_FST] = -1.7;
              //  +1.7
              left_threhold_total[id_FST] = 1.7;
              //  -1.7
            } else {
              right_threhold_total[id_FST] = -1.7;
              //  +1.7
              left_threhold_total[id_FST] = 1.7;
              //  -1.7
            }
          } else if (object_lane_total[id_FST] == 2.0) {
            //  rightlane case
            if (status_flag == 1) {
              right_threhold_total[id_FST] = -1.55;
              //  +1.55
              left_threhold_total[id_FST] = 1.55;
              //  -1.55
            } else {
              right_threhold_total[id_FST] = -1.55;
              //  +1.55
              left_threhold_total[id_FST] = 1.55;
              //  -1.55
            }
          } else if (object_lane_total[id_FST] == 3.0) {
            //  leftlane case
            if (status_flag == 1) {
              right_threhold_total[id_FST] = -1.55;
              //  +1.55
              left_threhold_total[id_FST] = 1.55;
              //  -1.55
            } else {
              right_threhold_total[id_FST] = -1.55;
              //  +1.55
              left_threhold_total[id_FST] = 1.55;
              //  -1.55
            }
          }
          // -------------------------   left  ----  %%
          if (poffset_total[id_FST] > left_threhold_total[id_FST]) {
            valid_Rear_left_num++;
            Fusion_Track_Recognition[22 * id_FST + 20] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition[22 * id_FST + 21] = 106.0;
            std::copy(
                &Fusion_Track_Recognition[id_FST * 22],
                &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 + 22U)],
                &tmp_RVL_candidate[valid_Rear_left_num * 22]);
            object_lane_total[id_FST] = 3.0;
            //  lane info : leftlane
            // -------------------------   inlane ----  %%
          } else if ((poffset_total[id_FST] >= right_threhold_total[id_FST]) &&
                     (poffset_total[id_FST] <= left_threhold_total[id_FST])) {
            valid_Rear_inlane_num++;
            Fusion_Track_Recognition[22 * id_FST + 20] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition[22 * id_FST + 21] = 107.0;
            std::copy(
                &Fusion_Track_Recognition[id_FST * 22],
                &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 + 22U)],
                &tmp_RVI_candidate[valid_Rear_inlane_num * 22]);
            object_lane_total[id_FST] = 1.0;
            //  lane info : inlane
            // -------------------------   right ----  %%
          } else if (poffset_total[id_FST] < right_threhold_total[id_FST]) {
            valid_Rear_right_num++;
            Fusion_Track_Recognition[22 * id_FST + 20] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition[22 * id_FST + 21] = 108.0;
            std::copy(
                &Fusion_Track_Recognition[id_FST * 22],
                &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 + 22U)],
                &tmp_RVR_candidate[valid_Rear_right_num * 22]);
            object_lane_total[id_FST] = 2.0;
            //  lane info : rightlane
          }
        }
      }
    }
  }
  //     %% select nearest target
  // ----  select Front_left target  ----%%
  if (valid_left_num + 1 != 0) {
    for (status_flag = 0; status_flag <= valid_left_num; status_flag++) {
      //  chack motionID & shapeID
      d = tmp_FVL_candidate[22 * status_flag + 11];
      if ((d == 3.0) || (d == 4.0)) {
        //  shape attribute
        //  chack nearer target
        d = tmp_FVL_candidate[22 * status_flag];
        d1 = tmp_FVL_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (leftRange > dist_to_ego) {
          leftRange = dist_to_ego;
          std::copy(
              &tmp_FVL_candidate[status_flag * 22],
              &tmp_FVL_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_FVL[0]);
          tmp_FVL_ID = tmp_FVL_candidate[22 * status_flag + 20];
        }
      } else if ((tmp_FVL_candidate[22 * status_flag + 10] == 2.0) &&
                 (d != 2.0) && (d != 6.0)) {
        //  motion attribute = dynamic & shape ~= guard rail
        //  chack nearer target
        d = tmp_FVL_candidate[22 * status_flag];
        d1 = tmp_FVL_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (leftRange > dist_to_ego) {
          leftRange = dist_to_ego;
          std::copy(
              &tmp_FVL_candidate[status_flag * 22],
              &tmp_FVL_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_FVL[0]);
          tmp_FVL_ID = tmp_FVL_candidate[22 * status_flag + 20];
        }
      }
    }
    if (tmp_FVL_ID != 0.0) {
      Fusion_Track_Recognition[22 * (static_cast<int>(tmp_FVL_ID) - 1) + 21] =
          1.0;
      //  FVL
    }
  }
  // ------  select Front_inlane target  ------%%
  for (status_flag = 0; status_flag <= valid_inlane_num; status_flag++) {
    d = tmp_FVI_candidate[22 * status_flag + 11];
    if ((d == 3.0) || (d == 4.0)) {
      //  shape attribute
      d = tmp_FVI_candidate[22 * status_flag];
      d1 = tmp_FVI_candidate[22 * status_flag + 1];
      dist_to_ego = std::sqrt(d * d + d1 * d1);
      if (inlaneRange > dist_to_ego) {
        inlaneRange = dist_to_ego;
        std::copy(&tmp_FVI_candidate[status_flag * 22],
                  &tmp_FVI_candidate[static_cast<int>(status_flag * 22 + 22U)],
                  &tmp_FVI[0]);
        tmp_FVI_ID = tmp_FVI_candidate[22 * status_flag + 20];
      }
    } else if ((tmp_FVI_candidate[22 * status_flag + 10] == 2.0) &&
               (d != 2.0) && (d != 6.0)) {
      //  motion attribute
      d = tmp_FVI_candidate[22 * status_flag];
      d1 = tmp_FVI_candidate[22 * status_flag + 1];
      dist_to_ego = std::sqrt(d * d + d1 * d1);
      if (inlaneRange > dist_to_ego) {
        inlaneRange = dist_to_ego;
        std::copy(&tmp_FVI_candidate[status_flag * 22],
                  &tmp_FVI_candidate[static_cast<int>(status_flag * 22 + 22U)],
                  &tmp_FVI[0]);
        tmp_FVI_ID = tmp_FVI_candidate[22 * status_flag + 20];
      }
    }
  }
  if (tmp_FVI_ID != 0.0) {
    Fusion_Track_Recognition[22 * (static_cast<int>(tmp_FVI_ID) - 1) + 21] =
        2.0;
    //  FVI
  }
  // ----  select Front_right target  -----%%
  if (valid_right_num + 1 != 0) {
    for (status_flag = 0; status_flag <= valid_right_num; status_flag++) {
      //  chack motionID & shapeID
      d = tmp_FVR_candidate[22 * status_flag + 11];
      if ((d == 3.0) || (d == 4.0)) {
        //  shape attribute
        //  chack nearer target
        d = tmp_FVR_candidate[22 * status_flag];
        d1 = tmp_FVR_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (rightRange > dist_to_ego) {
          rightRange = dist_to_ego;
          std::copy(
              &tmp_FVR_candidate[status_flag * 22],
              &tmp_FVR_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_FVR[0]);
          tmp_FVR_ID = tmp_FVR_candidate[22 * status_flag + 20];
        }
      } else if ((tmp_FVR_candidate[22 * status_flag + 10] == 2.0) &&
                 (d != 2.0) && (d != 6.0)) {
        //  motion attribute = dynamic & shape ~= guard rail
        //  chack nearer target
        d = tmp_FVR_candidate[22 * status_flag];
        d1 = tmp_FVR_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (rightRange > dist_to_ego) {
          rightRange = dist_to_ego;
          std::copy(
              &tmp_FVR_candidate[status_flag * 22],
              &tmp_FVR_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_FVR[0]);
          tmp_FVR_ID = tmp_FVR_candidate[22 * status_flag + 20];
        }
      }
    }
    if (tmp_FVR_ID != 0.0) {
      Fusion_Track_Recognition[22 * (static_cast<int>(tmp_FVR_ID) - 1) + 21] =
          3.0;
      //  FVR
    }
  }
  // ----  select Adjacent_left target  ----%%
  if (valid_Adjacent_left_num + 1 != 0) {
    for (status_flag = 0; status_flag <= valid_Adjacent_left_num;
         status_flag++) {
      //  chack motionID & shapeID
      d = tmp_AVL_candidate[22 * status_flag + 11];
      if ((d == 3.0) || (d == 4.0)) {
        //  shape attribute
        //  chack nearer target
        d = tmp_AVL_candidate[22 * status_flag];
        d1 = tmp_AVL_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (leftRange_Adjacent > dist_to_ego) {
          leftRange_Adjacent = dist_to_ego;
          std::copy(
              &tmp_AVL_candidate[status_flag * 22],
              &tmp_AVL_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_AVL[0]);
          tmp_AVL_ID = tmp_AVL_candidate[22 * status_flag + 20];
        }
      } else if ((tmp_AVL_candidate[22 * status_flag + 10] == 2.0) &&
                 (d != 2.0) && (d != 6.0)) {
        //  motion attribute
        //  chack nearer target
        d = tmp_AVL_candidate[22 * status_flag];
        d1 = tmp_AVL_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (leftRange_Adjacent > dist_to_ego) {
          leftRange_Adjacent = dist_to_ego;
          std::copy(
              &tmp_AVL_candidate[status_flag * 22],
              &tmp_AVL_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_AVL[0]);
          tmp_AVL_ID = tmp_AVL_candidate[22 * status_flag + 20];
        }
      }
    }
    if (tmp_AVL_ID != 0.0) {
      Fusion_Track_Recognition[22 * (static_cast<int>(tmp_AVL_ID) - 1) + 21] =
          4.0;
      //  AVL
    }
  }
  // ----  select Adjacent_right target  -----%%
  if (valid_Adjacent_right_num + 1 != 0) {
    for (status_flag = 0; status_flag <= valid_Adjacent_right_num;
         status_flag++) {
      //  chack motionID & shapeID
      d = tmp_AVR_candidate[22 * status_flag + 11];
      if ((d == 3.0) || (d == 4.0)) {
        //  shape attribute
        //  chack nearer target
        d = tmp_AVR_candidate[22 * status_flag];
        d1 = tmp_AVR_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (rightRange_Adjacent > dist_to_ego) {
          rightRange_Adjacent = dist_to_ego;
          std::copy(
              &tmp_AVR_candidate[status_flag * 22],
              &tmp_AVR_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_AVR[0]);
          tmp_AVR_ID = tmp_AVR_candidate[22 * status_flag + 20];
        }
      } else if ((tmp_AVR_candidate[22 * status_flag + 10] == 2.0) &&
                 (d != 2.0) && (d != 6.0)) {
        //  motion attribute
        //  chack nearer target
        d = tmp_AVR_candidate[22 * status_flag];
        d1 = tmp_AVR_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (rightRange_Adjacent > dist_to_ego) {
          rightRange_Adjacent = dist_to_ego;
          std::copy(
              &tmp_AVR_candidate[status_flag * 22],
              &tmp_AVR_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_AVR[0]);
          tmp_AVR_ID = tmp_AVR_candidate[22 * status_flag + 20];
        }
      }
    }
    if (tmp_AVR_ID != 0.0) {
      Fusion_Track_Recognition[22 * (static_cast<int>(tmp_AVR_ID) - 1) + 21] =
          5.0;
      //  AVR
    }
  }
  // ----  select Rear_left target  ----%%
  if (valid_Rear_left_num + 1 != 0) {
    for (status_flag = 0; status_flag <= valid_Rear_left_num; status_flag++) {
      //  chack motionID & shapeID
      d = tmp_RVL_candidate[22 * status_flag + 11];
      if ((d == 3.0) || (d == 4.0)) {
        //  shape attribute
        //  chack nearer target
        d = tmp_RVL_candidate[22 * status_flag];
        d1 = tmp_RVL_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (leftRange_Rear > dist_to_ego) {
          leftRange_Rear = dist_to_ego;
          std::copy(
              &tmp_RVL_candidate[status_flag * 22],
              &tmp_RVL_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_RVL[0]);
          tmp_RVL_ID = tmp_RVL_candidate[22 * status_flag + 20];
        }
      } else if ((tmp_RVL_candidate[22 * status_flag + 10] == 2.0) &&
                 (d != 2.0) && (d != 6.0)) {
        //  motion attribute
        //  chack nearer target
        d = tmp_RVL_candidate[22 * status_flag];
        d1 = tmp_RVL_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (leftRange_Rear > dist_to_ego) {
          leftRange_Rear = dist_to_ego;
          std::copy(
              &tmp_RVL_candidate[status_flag * 22],
              &tmp_RVL_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_RVL[0]);
          tmp_RVL_ID = tmp_RVL_candidate[22 * status_flag + 20];
        }
      }
    }
    if (tmp_RVL_ID != 0.0) {
      Fusion_Track_Recognition[22 * (static_cast<int>(tmp_RVL_ID) - 1) + 21] =
          6.0;
      //  RVL
    }
  }
  // ------  select Rear_inlane target  ------%%
  if (valid_Rear_inlane_num + 1 != 0) {
    for (status_flag = 0; status_flag <= valid_Rear_inlane_num; status_flag++) {
      d = tmp_RVI_candidate[22 * status_flag + 11];
      if ((d == 3.0) || (d == 4.0)) {
        //  shape attribute
        d = tmp_RVI_candidate[22 * status_flag];
        d1 = tmp_RVI_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (inlaneRange_Rear > dist_to_ego) {
          inlaneRange_Rear = dist_to_ego;
          std::copy(
              &tmp_RVI_candidate[status_flag * 22],
              &tmp_RVI_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_RVI[0]);
          tmp_RVI_ID = tmp_RVI_candidate[22 * status_flag + 20];
        }
      } else if ((tmp_RVI_candidate[22 * status_flag + 10] == 2.0) &&
                 (d != 2.0) && (d != 6.0)) {
        //  motion attribute
        d = tmp_RVI_candidate[22 * status_flag];
        d1 = tmp_RVI_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (inlaneRange_Rear > dist_to_ego) {
          inlaneRange_Rear = dist_to_ego;
          std::copy(
              &tmp_RVI_candidate[status_flag * 22],
              &tmp_RVI_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_RVI[0]);
          tmp_RVI_ID = tmp_RVI_candidate[22 * status_flag + 20];
        }
      }
    }
    if (tmp_RVI_ID != 0.0) {
      Fusion_Track_Recognition[22 * (static_cast<int>(tmp_RVI_ID) - 1) + 21] =
          7.0;
      //  RVI
    }
  }
  // ----  select Rear_right target  -----%%
  if (valid_Rear_right_num + 1 != 0) {
    for (status_flag = 0; status_flag <= valid_Rear_right_num; status_flag++) {
      //  chack motionID & shapeID
      d = tmp_RVR_candidate[22 * status_flag + 11];
      if ((d == 3.0) || (d == 4.0)) {
        //  shape attribute
        //  chack nearer target
        d = tmp_RVR_candidate[22 * status_flag];
        d1 = tmp_RVR_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (rightRange_Rear > dist_to_ego) {
          rightRange_Rear = dist_to_ego;
          std::copy(
              &tmp_RVR_candidate[status_flag * 22],
              &tmp_RVR_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_RVR[0]);
          tmp_RVR_ID = tmp_RVR_candidate[22 * status_flag + 20];
        }
      } else if ((tmp_RVR_candidate[22 * status_flag + 10] == 2.0) &&
                 (d != 2.0) && (d != 6.0)) {
        //  motion attribute
        //  chack nearer target
        d = tmp_RVR_candidate[22 * status_flag];
        d1 = tmp_RVR_candidate[22 * status_flag + 1];
        dist_to_ego = std::sqrt(d * d + d1 * d1);
        if (rightRange_Rear > dist_to_ego) {
          rightRange_Rear = dist_to_ego;
          std::copy(
              &tmp_RVR_candidate[status_flag * 22],
              &tmp_RVR_candidate[static_cast<int>(status_flag * 22 + 22U)],
              &tmp_RVR[0]);
          tmp_RVR_ID = tmp_RVR_candidate[22 * status_flag + 20];
        }
      }
    }
    if (tmp_RVR_ID != 0.0) {
      Fusion_Track_Recognition[22 * (static_cast<int>(tmp_RVR_ID) - 1) + 21] =
          8.0;
      //  RVR
    }
  }
  //  recognition ID에 메뉴버 내보내기
  for (id_FST = 0; id_FST < 64; id_FST++) {
    d = Fusion_Track_Recognition[22 * id_FST];
    d1 = Fusion_Track_Recognition[22 * id_FST + 1];
    if (d * d + d1 * d1 != 0.0) {
      dist_to_ego = Fusion_Track_Recognition[22 * id_FST + 11];
      if ((dist_to_ego == 3.0) || (dist_to_ego == 4.0)) {
        if ((tmp_FVI[20] != 0.0) &&
            (static_cast<double>(id_FST) + 1.0 == tmp_FVI[20])) {
          FVI[0] = Fusion_Track_Recognition[22 * id_FST + 20];
          FVI[1] = d;
          FVI[2] = d1;
          FVI[3] = Fusion_Track_Recognition[22 * id_FST + 2];
          FVI[4] = Fusion_Track_Recognition[22 * id_FST + 3];
          FVI[5] = Fusion_Track_Recognition[22 * id_FST + 4];
          FVI[6] = Fusion_Track_Recognition[22 * id_FST + 5];
          FVI[7] = Fusion_Track_Recognition[22 * id_FST + 6];
        }
        if ((tmp_FVL[20] != 0.0) &&
            (static_cast<double>(id_FST) + 1.0 == tmp_FVL[20])) {
          FVL[0] = Fusion_Track_Recognition[22 * id_FST + 20];
          FVL[1] = d;
          FVL[2] = d1;
          FVL[3] = Fusion_Track_Recognition[22 * id_FST + 2];
          FVL[4] = Fusion_Track_Recognition[22 * id_FST + 3];
          FVL[5] = Fusion_Track_Recognition[22 * id_FST + 4];
          FVL[6] = Fusion_Track_Recognition[22 * id_FST + 5];
          FVL[7] = Fusion_Track_Recognition[22 * id_FST + 6];
        }
        if ((tmp_FVR[20] != 0.0) &&
            (static_cast<double>(id_FST) + 1.0 == tmp_FVR[20])) {
          FVR[0] = Fusion_Track_Recognition[22 * id_FST + 20];
          FVR[1] = d;
          FVR[2] = d1;
          FVR[3] = Fusion_Track_Recognition[22 * id_FST + 2];
          FVR[4] = Fusion_Track_Recognition[22 * id_FST + 3];
          FVR[5] = Fusion_Track_Recognition[22 * id_FST + 4];
          FVR[6] = Fusion_Track_Recognition[22 * id_FST + 5];
          FVR[7] = Fusion_Track_Recognition[22 * id_FST + 6];
        }
        if ((tmp_AVL[20] != 0.0) &&
            (static_cast<double>(id_FST) + 1.0 == tmp_AVL[20])) {
          AVL[0] = Fusion_Track_Recognition[22 * id_FST + 20];
          AVL[1] = d;
          AVL[2] = d1;
          AVL[3] = Fusion_Track_Recognition[22 * id_FST + 2];
          AVL[4] = Fusion_Track_Recognition[22 * id_FST + 3];
          AVL[5] = Fusion_Track_Recognition[22 * id_FST + 4];
          AVL[6] = Fusion_Track_Recognition[22 * id_FST + 5];
          AVL[7] = Fusion_Track_Recognition[22 * id_FST + 6];
        }
        if ((tmp_AVR[20] != 0.0) &&
            (static_cast<double>(id_FST) + 1.0 == tmp_AVR[20])) {
          AVR[0] = Fusion_Track_Recognition[22 * id_FST + 20];
          AVR[1] = d;
          AVR[2] = d1;
          AVR[3] = Fusion_Track_Recognition[22 * id_FST + 2];
          AVR[4] = Fusion_Track_Recognition[22 * id_FST + 3];
          AVR[5] = Fusion_Track_Recognition[22 * id_FST + 4];
          AVR[6] = Fusion_Track_Recognition[22 * id_FST + 5];
          AVR[7] = Fusion_Track_Recognition[22 * id_FST + 6];
        }
        if ((tmp_RVI[20] != 0.0) &&
            (static_cast<double>(id_FST) + 1.0 == tmp_RVI[20])) {
          RVI[0] = Fusion_Track_Recognition[22 * id_FST + 20];
          RVI[1] = d;
          RVI[2] = d1;
          RVI[3] = Fusion_Track_Recognition[22 * id_FST + 2];
          RVI[4] = Fusion_Track_Recognition[22 * id_FST + 3];
          RVI[5] = Fusion_Track_Recognition[22 * id_FST + 4];
          RVI[6] = Fusion_Track_Recognition[22 * id_FST + 5];
          RVI[7] = Fusion_Track_Recognition[22 * id_FST + 6];
        }
        if ((tmp_RVL[20] != 0.0) &&
            (static_cast<double>(id_FST) + 1.0 == tmp_RVL[20])) {
          RVL[0] = Fusion_Track_Recognition[22 * id_FST + 20];
          RVL[1] = d;
          RVL[2] = d1;
          RVL[3] = Fusion_Track_Recognition[22 * id_FST + 2];
          RVL[4] = Fusion_Track_Recognition[22 * id_FST + 3];
          RVL[5] = Fusion_Track_Recognition[22 * id_FST + 4];
          RVL[6] = Fusion_Track_Recognition[22 * id_FST + 5];
          RVL[7] = Fusion_Track_Recognition[22 * id_FST + 6];
        }
        if ((tmp_RVR[20] != 0.0) &&
            (static_cast<double>(id_FST) + 1.0 == tmp_RVR[20])) {
          RVR[0] = Fusion_Track_Recognition[22 * id_FST + 20];
          RVR[1] = d;
          RVR[2] = d1;
          RVR[3] = Fusion_Track_Recognition[22 * id_FST + 2];
          RVR[4] = Fusion_Track_Recognition[22 * id_FST + 3];
          RVR[5] = Fusion_Track_Recognition[22 * id_FST + 4];
          RVR[6] = Fusion_Track_Recognition[22 * id_FST + 5];
          RVR[7] = Fusion_Track_Recognition[22 * id_FST + 6];
        }
      }
    }
  }
}

//
// File trailer for vehicle_recognition.cpp
//
// [EOF]
//
