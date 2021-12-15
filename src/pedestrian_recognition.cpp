//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: pedestrian_recognition.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "pedestrian_recognition.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"
#include <algorithm>
#include <cmath>
#include <cstring>

// Function Definitions
//
// Arguments    : const double Fusion_Track_Recognition[1408]
//                double Fusion_Track_Recognition_out[1792]
//                double tmp_FPI[9]
//                double tmp_FPL[9]
//                double tmp_FPR[9]
//                double tmp_FCI[9]
//                double tmp_FCL[9]
//                double tmp_FCR[9]
//                double tmp_FEI[9]
//                double tmp_FEL[9]
//                double tmp_FER[9]
// Return Type  : void
//
void pedestrian_recognition(const double Fusion_Track_Recognition[1408],
                            double Fusion_Track_Recognition_out[1792],
                            double tmp_FPI[9], double tmp_FPL[9],
                            double tmp_FPR[9], double tmp_FCI[9],
                            double tmp_FCL[9], double tmp_FCR[9],
                            double tmp_FEI[9], double tmp_FEL[9],
                            double tmp_FER[9])
{
  double tmp_FCI_candidate[1792];
  double tmp_FCL_candidate[1792];
  double tmp_FCR_candidate[1792];
  double tmp_FEI_candidate[1792];
  double tmp_FEL_candidate[1792];
  double tmp_FER_candidate[1792];
  double tmp_FPI_candidate[1792];
  double tmp_FPL_candidate[1792];
  double tmp_FPR_candidate[1792];
  double left_threshold_Cyclist[64];
  double left_threshold_E_scooter[64];
  double left_threshold_PED[64];
  double poffset_VRU[64];
  double right_threshold_Cyclist[64];
  double right_threshold_E_scooter[64];
  double right_threshold_PED[64];
  double d;
  double dist_to_ego_PED;
  double inlaneRange_Cyclist;
  double inlaneRange_E_scooter;
  double inlaneRange_PED;
  double leftRange_Cyclist;
  double leftRange_E_scooter;
  double leftRange_PED;
  double rightRange_Cyclist;
  double rightRange_E_scooter;
  double rightRange_PED;
  double tmp_FCI_ID;
  double tmp_FCL_ID;
  double tmp_FCR_ID;
  double tmp_FEI_ID;
  double tmp_FEL_ID;
  double tmp_FER_ID;
  double tmp_FPI_ID;
  double tmp_FPL_ID;
  double tmp_FPR_ID;
  int id_FST;
  int valid_inlane_Cyclist_num;
  int valid_inlane_E_scooter_num;
  int valid_inlane_PED_num;
  int valid_left_Cyclist_num;
  int valid_left_E_scooter_num;
  int valid_left_PED_num;
  int valid_right_Cyclist_num;
  int valid_right_E_scooter_num;
  int valid_right_PED_num;
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  // --------------------------------------------------------------------------
  //  Fusion_Track_Recognition : [22 X 64]     Input
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
  //  22 : Vehicle Recognition
  // --------------------------------------------------------------------------
  //  Fusion_Track_Recognition_out : [28 X 64]     Output
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
  //  21 : Vehicle ID
  //  22 : Vehicle Recognition
  //  23 : Pedestrian ID
  //  24 : Pedestrian Recognition
  //  25 : Cyclist ID
  //  26 : Cyclist Recognition
  //  27 : E Scooter ID
  //  28 : E Scooter Recognition
  // --------------------------------------------------------------------------
  //  FPI, FPR, FPL, FCI, FCR, FCL, FEI, FER, FEL : [8 X 1]     Output
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
  //  initialization
  // --------------------------------------------------------------------------
  for (id_FST = 0; id_FST < 64; id_FST++) {
    std::copy(&Fusion_Track_Recognition[id_FST * 22],
              &Fusion_Track_Recognition[static_cast<int>(id_FST * 22 + 22U)],
              &Fusion_Track_Recognition_out[id_FST * 28]);
  }
  std::memset(&tmp_FPI[0], 0, 9U * sizeof(double));
  std::memset(&tmp_FPL[0], 0, 9U * sizeof(double));
  std::memset(&tmp_FPR[0], 0, 9U * sizeof(double));
  valid_inlane_PED_num = -1;
  valid_right_PED_num = -1;
  valid_left_PED_num = -1;
  inlaneRange_PED = 150.0;
  rightRange_PED = 100.0;
  leftRange_PED = 100.0;
  tmp_FPI_ID = 0.0;
  tmp_FPL_ID = 0.0;
  tmp_FPR_ID = 0.0;
  valid_inlane_Cyclist_num = -1;
  valid_right_Cyclist_num = -1;
  valid_left_Cyclist_num = -1;
  inlaneRange_Cyclist = 150.0;
  rightRange_Cyclist = 100.0;
  leftRange_Cyclist = 100.0;
  tmp_FCI_ID = 0.0;
  tmp_FCL_ID = 0.0;
  tmp_FCR_ID = 0.0;
  valid_inlane_E_scooter_num = -1;
  valid_right_E_scooter_num = -1;
  valid_left_E_scooter_num = -1;
  inlaneRange_E_scooter = 150.0;
  rightRange_E_scooter = 100.0;
  leftRange_E_scooter = 100.0;
  tmp_FEI_ID = 0.0;
  tmp_FEL_ID = 0.0;
  tmp_FER_ID = 0.0;
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //  calculate poffset
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //  Pedestrian recognition
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  for (id_FST = 0; id_FST < 64; id_FST++) {
    dist_to_ego_PED = Fusion_Track_Recognition[22 * id_FST];
    d = Fusion_Track_Recognition[22 * id_FST + 1];
    if (dist_to_ego_PED * dist_to_ego_PED + d * d != 0.0) {
      dist_to_ego_PED = Fusion_Track_Recognition[22 * id_FST + 11];
      if ((dist_to_ego_PED == 5.0) || (dist_to_ego_PED == 6.0) ||
          (dist_to_ego_PED == 9.0) || (dist_to_ego_PED == 10.0) ||
          (dist_to_ego_PED == 11.0) || (dist_to_ego_PED == 12.0)) {
        poffset_VRU[id_FST] = Fusion_Track_Recognition[22 * id_FST + 19];
      }
      if ((dist_to_ego_PED == 5.0) || (dist_to_ego_PED == 6.0)) {
        //  Assign right/left threshold according to the long pos of ped track
        //  LONG
        if (d > 70.0) {
          right_threshold_PED[id_FST] = -1.8;
          left_threshold_PED[id_FST] = 1.8;
          //  MID
        } else if (d > 17.5) {
          right_threshold_PED[id_FST] = -1.65;
          left_threshold_PED[id_FST] = 1.65;
          //  SHORT
        } else {
          right_threshold_PED[id_FST] = -1.55;
          left_threshold_PED[id_FST] = 1.55;
        }
        //  Find tmp_FPI/FPL/FPR_candidate
        //  Front
        if ((std::abs(poffset_VRU[id_FST]) < 50.0) && (d <= 150.0) &&
            (d > -70.0)) {
          //  In-Lane
          if ((poffset_VRU[id_FST] >= right_threshold_PED[id_FST]) &&
              (poffset_VRU[id_FST] <= left_threshold_PED[id_FST])) {
            valid_inlane_PED_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 22] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 23] = 102.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FPI_candidate[valid_inlane_PED_num * 28]);
            //  Left
          } else if (poffset_VRU[id_FST] > left_threshold_PED[id_FST]) {
            valid_left_PED_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 22] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 23] = 101.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FPL_candidate[valid_left_PED_num * 28]);
            //  Right
          } else if (poffset_VRU[id_FST] < right_threshold_PED[id_FST]) {
            valid_right_PED_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 22] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 23] = 103.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FPR_candidate[valid_right_PED_num * 28]);
          }
        }
      }
    }
  }
  //  Select nearest PED target
  if (valid_inlane_PED_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_inlane_PED_num; id_FST++) {
      dist_to_ego_PED = tmp_FPI_candidate[28 * id_FST + 1];
      d = tmp_FPI_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (inlaneRange_PED > dist_to_ego_PED) {
        inlaneRange_PED = dist_to_ego_PED;
        tmp_FPI_ID = tmp_FPI_candidate[28 * id_FST + 22];
      }
    }
    if (tmp_FPI_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FPI_ID) - 1) +
                                   23] = 2.0;
    }
  }
  if (valid_left_PED_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_left_PED_num; id_FST++) {
      dist_to_ego_PED = tmp_FPL_candidate[28 * id_FST + 1];
      d = tmp_FPL_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (leftRange_PED > dist_to_ego_PED) {
        leftRange_PED = dist_to_ego_PED;
        tmp_FPL_ID = tmp_FPL_candidate[28 * id_FST + 22];
      }
    }
    if (tmp_FPL_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FPL_ID) - 1) +
                                   23] = 1.0;
    }
  }
  if (valid_right_PED_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_right_PED_num; id_FST++) {
      dist_to_ego_PED = tmp_FPR_candidate[28 * id_FST + 1];
      d = tmp_FPR_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (rightRange_PED > dist_to_ego_PED) {
        rightRange_PED = dist_to_ego_PED;
        tmp_FPR_ID = tmp_FPR_candidate[28 * id_FST + 22];
      }
    }
    if (tmp_FPR_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FPR_ID) - 1) +
                                   23] = 3.0;
    }
  }
  //  generate FPI, FPL, FPR
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //  Cyclist recognition
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  for (id_FST = 0; id_FST < 64; id_FST++) {
    dist_to_ego_PED = Fusion_Track_Recognition[22 * id_FST];
    d = Fusion_Track_Recognition[22 * id_FST + 1];
    if (dist_to_ego_PED * dist_to_ego_PED + d * d != 0.0) {
      dist_to_ego_PED = Fusion_Track_Recognition_out[28 * id_FST + 23];
      if (dist_to_ego_PED == 2.0) {
        tmp_FPI[0] = Fusion_Track_Recognition_out[28 * id_FST + 22];
        tmp_FPI[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FPI[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FPI[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FPI[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FPI[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FPI[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FPI[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      } else if (dist_to_ego_PED == 1.0) {
        tmp_FPL[0] = Fusion_Track_Recognition_out[28 * id_FST + 22];
        tmp_FPL[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FPL[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FPL[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FPL[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FPL[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FPL[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FPL[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      } else if (dist_to_ego_PED == 3.0) {
        tmp_FPR[0] = Fusion_Track_Recognition_out[28 * id_FST + 22];
        tmp_FPR[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FPR[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FPR[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FPR[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FPR[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FPR[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FPR[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      }
      dist_to_ego_PED = Fusion_Track_Recognition[22 * id_FST + 11];
      if ((dist_to_ego_PED == 9.0) || (dist_to_ego_PED == 10.0)) {
        //  Assign right/left threshold according to the long pos of ped track
        //  LONG
        if (d > 70.0) {
          right_threshold_Cyclist[id_FST] = -1.8;
          left_threshold_Cyclist[id_FST] = 1.8;
          //  MID
        } else if (d > 17.5) {
          right_threshold_Cyclist[id_FST] = -1.65;
          left_threshold_Cyclist[id_FST] = 1.65;
          //  SHORT
        } else {
          right_threshold_Cyclist[id_FST] = -1.55;
          left_threshold_Cyclist[id_FST] = 1.55;
        }
        //  Find tmp_FCI/FCL/FCR_candidate
        //  Front
        if ((std::abs(poffset_VRU[id_FST]) < 50.0) && (d <= 150.0) &&
            (d > -70.0)) {
          //  In-Lane
          if ((poffset_VRU[id_FST] >= right_threshold_Cyclist[id_FST]) &&
              (poffset_VRU[id_FST] <= left_threshold_Cyclist[id_FST])) {
            valid_inlane_Cyclist_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 24] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 25] = 102.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FCI_candidate[valid_inlane_Cyclist_num * 28]);
            //  Left
          } else if (poffset_VRU[id_FST] > left_threshold_Cyclist[id_FST]) {
            valid_left_Cyclist_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 24] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 25] = 101.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FCL_candidate[valid_left_Cyclist_num * 28]);
            //  Right
          } else if (poffset_VRU[id_FST] < right_threshold_Cyclist[id_FST]) {
            valid_right_Cyclist_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 24] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 25] = 103.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FCR_candidate[valid_right_Cyclist_num * 28]);
          }
        }
      }
    }
  }
  //  Select nearest Cyclist target
  if (valid_inlane_Cyclist_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_inlane_Cyclist_num; id_FST++) {
      dist_to_ego_PED = tmp_FCI_candidate[28 * id_FST + 1];
      d = tmp_FCI_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (inlaneRange_Cyclist > dist_to_ego_PED) {
        inlaneRange_Cyclist = dist_to_ego_PED;
        //                              tmp_FPI = tmp_FPI_candidate(:,
        //                              index_FPI);
        tmp_FCI_ID = tmp_FCI_candidate[28 * id_FST + 24];
      }
    }
    if (tmp_FCI_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FCI_ID) - 1) +
                                   25] = 2.0;
    }
  }
  if (valid_left_Cyclist_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_left_Cyclist_num; id_FST++) {
      dist_to_ego_PED = tmp_FCL_candidate[28 * id_FST + 1];
      d = tmp_FCL_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (leftRange_Cyclist > dist_to_ego_PED) {
        leftRange_Cyclist = dist_to_ego_PED;
        //                              tmp_FPL = tmp_FPL_candidate(:,
        //                              index_FPL);
        tmp_FCL_ID = tmp_FCL_candidate[28 * id_FST + 24];
      }
    }
    if (tmp_FCL_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FCL_ID) - 1) +
                                   25] = 1.0;
    }
  }
  if (valid_right_Cyclist_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_right_Cyclist_num; id_FST++) {
      dist_to_ego_PED = tmp_FCR_candidate[28 * id_FST + 1];
      d = tmp_FCR_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (rightRange_Cyclist > dist_to_ego_PED) {
        rightRange_Cyclist = dist_to_ego_PED;
        //                              tmp_FPR = tmp_FPR_candidate(:,
        //                              index_FPR);
        tmp_FCR_ID = tmp_FCR_candidate[28 * id_FST + 24];
      }
    }
    if (tmp_FCR_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FCR_ID) - 1) +
                                   25] = 3.0;
    }
  }
  //  generate FCI, FCL, FCR
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  //  E_scooter recognition
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  for (id_FST = 0; id_FST < 64; id_FST++) {
    dist_to_ego_PED = Fusion_Track_Recognition[22 * id_FST];
    d = Fusion_Track_Recognition[22 * id_FST + 1];
    if (dist_to_ego_PED * dist_to_ego_PED + d * d != 0.0) {
      dist_to_ego_PED = Fusion_Track_Recognition_out[28 * id_FST + 25];
      if (dist_to_ego_PED == 2.0) {
        tmp_FCI[0] = Fusion_Track_Recognition_out[28 * id_FST + 24];
        tmp_FCI[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FCI[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FCI[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FCI[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FCI[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FCI[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FCI[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      } else if (dist_to_ego_PED == 1.0) {
        tmp_FCL[0] = Fusion_Track_Recognition_out[28 * id_FST + 24];
        tmp_FCL[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FCL[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FCL[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FCL[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FCL[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FCL[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FCL[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      } else if (dist_to_ego_PED == 3.0) {
        tmp_FCR[0] = Fusion_Track_Recognition_out[28 * id_FST + 24];
        tmp_FCR[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FCR[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FCR[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FCR[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FCR[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FCR[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FCR[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      }
      dist_to_ego_PED = Fusion_Track_Recognition[22 * id_FST + 11];
      if ((dist_to_ego_PED == 11.0) || (dist_to_ego_PED == 12.0)) {
        //  Assign right/left threshold according to the long pos of ped track
        //  LONG
        if (d > 70.0) {
          right_threshold_E_scooter[id_FST] = -1.8;
          left_threshold_E_scooter[id_FST] = 1.8;
          //  MID
        } else if (d > 17.5) {
          right_threshold_E_scooter[id_FST] = -1.65;
          left_threshold_E_scooter[id_FST] = 1.65;
          //  SHORT
        } else {
          right_threshold_E_scooter[id_FST] = -1.55;
          left_threshold_E_scooter[id_FST] = 1.55;
        }
        //  Find tmp_FEI/FEL/FER_candidate
        //  Front
        if ((std::abs(poffset_VRU[id_FST]) < 50.0) && (d <= 150.0) &&
            (d > -70.0)) {
          //  In-Lane
          if ((poffset_VRU[id_FST] >= right_threshold_E_scooter[id_FST]) &&
              (poffset_VRU[id_FST] <= left_threshold_E_scooter[id_FST])) {
            valid_inlane_E_scooter_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 26] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 27] = 102.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FEI_candidate[valid_inlane_E_scooter_num * 28]);
            //  Left
          } else if (poffset_VRU[id_FST] > left_threshold_E_scooter[id_FST]) {
            valid_left_E_scooter_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 26] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 27] = 101.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FEL_candidate[valid_left_E_scooter_num * 28]);
            //  Right
          } else if (poffset_VRU[id_FST] < right_threshold_E_scooter[id_FST]) {
            valid_right_E_scooter_num++;
            Fusion_Track_Recognition_out[28 * id_FST + 26] =
                static_cast<double>(id_FST) + 1.0;
            Fusion_Track_Recognition_out[28 * id_FST + 27] = 103.0;
            std::copy(&Fusion_Track_Recognition_out[id_FST * 28],
                      &Fusion_Track_Recognition_out[static_cast<int>(
                          id_FST * 28 + 28U)],
                      &tmp_FER_candidate[valid_right_E_scooter_num * 28]);
          }
        }
      }
    }
  }
  //  Select nearest E_scooter target
  if (valid_inlane_E_scooter_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_inlane_E_scooter_num; id_FST++) {
      dist_to_ego_PED = tmp_FEI_candidate[28 * id_FST + 1];
      d = tmp_FEI_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (inlaneRange_E_scooter > dist_to_ego_PED) {
        inlaneRange_E_scooter = dist_to_ego_PED;
        tmp_FEI_ID = tmp_FEI_candidate[28 * id_FST + 26];
      }
    }
    if (tmp_FEI_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FEI_ID) - 1) +
                                   27] = 2.0;
    }
  }
  if (valid_left_E_scooter_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_left_E_scooter_num; id_FST++) {
      dist_to_ego_PED = tmp_FEL_candidate[28 * id_FST + 1];
      d = tmp_FEL_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (leftRange_E_scooter > dist_to_ego_PED) {
        leftRange_E_scooter = dist_to_ego_PED;
        tmp_FEL_ID = tmp_FEL_candidate[28 * id_FST + 26];
      }
    }
    if (tmp_FEL_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FEL_ID) - 1) +
                                   27] = 1.0;
    }
  }
  if (valid_right_E_scooter_num + 1 != 0) {
    for (id_FST = 0; id_FST <= valid_right_E_scooter_num; id_FST++) {
      dist_to_ego_PED = tmp_FER_candidate[28 * id_FST + 1];
      d = tmp_FER_candidate[28 * id_FST];
      dist_to_ego_PED = std::sqrt(dist_to_ego_PED * dist_to_ego_PED + d * d);
      if (rightRange_E_scooter > dist_to_ego_PED) {
        rightRange_E_scooter = dist_to_ego_PED;
        tmp_FER_ID = tmp_FER_candidate[28 * id_FST + 26];
      }
    }
    if (tmp_FER_ID != 0.0) {
      Fusion_Track_Recognition_out[28 * (static_cast<int>(tmp_FER_ID) - 1) +
                                   27] = 3.0;
    }
  }
  //  generate FEI, FEL, FER
  for (id_FST = 0; id_FST < 64; id_FST++) {
    dist_to_ego_PED = Fusion_Track_Recognition[22 * id_FST];
    d = Fusion_Track_Recognition[22 * id_FST + 1];
    if (dist_to_ego_PED * dist_to_ego_PED + d * d != 0.0) {
      dist_to_ego_PED = Fusion_Track_Recognition_out[28 * id_FST + 27];
      if (dist_to_ego_PED == 2.0) {
        tmp_FEI[0] = Fusion_Track_Recognition_out[28 * id_FST + 26];
        tmp_FEI[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FEI[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FEI[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FEI[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FEI[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FEI[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FEI[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      } else if (dist_to_ego_PED == 1.0) {
        tmp_FEL[0] = Fusion_Track_Recognition_out[28 * id_FST + 26];
        tmp_FEL[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FEL[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FEL[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FEL[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FEL[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FEL[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FEL[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      } else if (dist_to_ego_PED == 3.0) {
        tmp_FER[0] = Fusion_Track_Recognition_out[28 * id_FST + 26];
        tmp_FER[1] = Fusion_Track_Recognition_out[28 * id_FST];
        tmp_FER[2] = Fusion_Track_Recognition_out[28 * id_FST + 1];
        tmp_FER[3] = Fusion_Track_Recognition_out[28 * id_FST + 2];
        tmp_FER[4] = Fusion_Track_Recognition_out[28 * id_FST + 3];
        tmp_FER[5] = Fusion_Track_Recognition_out[28 * id_FST + 4];
        tmp_FER[6] = Fusion_Track_Recognition_out[28 * id_FST + 5];
        tmp_FER[7] = Fusion_Track_Recognition_out[28 * id_FST + 6];
      }
    }
  }
}

//
// File trailer for pedestrian_recognition.cpp
//
// [EOF]
//
