//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: gating.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "gating.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static double Check_Association_NG2(
    double Check_Reference_id, const coder::array<double, 3U> &tmp_residual,
    const double tmp_norm_residual_data[], const double gating_threshold_y[128],
    const double gating_threshold_x[128], const double gating_threshold_vx[128],
    const double Association_Map[128]);

static void Create_Gating_Threshold_VRU(const double Reference_Track[544],
                                        double tmp_gating_threshold_y[128],
                                        double tmp_gating_threshold_x[128],
                                        double tmp_gating_threshold_vy[128],
                                        double tmp_gating_threshold_vx[128]);

static void Create_Gating_Threshold_Vehicle(
    const double Reference_Track[544], double tmp_gating_threshold_y[128],
    double tmp_gating_threshold_x[128], double tmp_gating_threshold_vy[128],
    double tmp_gating_threshold_vx[128]);

static void Residual_NG_Vehicle(const double Reference_Track[544],
                                const double Target_Track[360],
                                double tmp_residual[12288],
                                double tmp_norm_residual[4096]);

// Function Definitions
//
// Arguments    : double Check_Reference_id
//                const coder::array<double, 3U> &tmp_residual
//                const double tmp_norm_residual_data[]
//                const double gating_threshold_y[128]
//                const double gating_threshold_x[128]
//                const double gating_threshold_vx[128]
//                const double Association_Map[128]
// Return Type  : double
//
static double Check_Association_NG2(
    double Check_Reference_id, const coder::array<double, 3U> &tmp_residual,
    const double tmp_norm_residual_data[], const double gating_threshold_y[128],
    const double gating_threshold_x[128], const double gating_threshold_vx[128],
    const double Association_Map[128])
{
  double x_data[64];
  double tmp_reference_candidate_residual[5];
  double Fused_Target_id;
  double d;
  int iidx_data[64];
  int iidx[5];
  int tmp_reference_candidate_id[5];
  int tmp_target_candidate_id[5];
  int iidx_size[2];
  int index_FST;
  int reference_fused_flag;
  bool exitg1;
  Fused_Target_id = 0.0;
  reference_fused_flag = 0;
  //  Gating
  //  Reference_track(Reference_ID) 가 Association_Map에서 사용됐는지 확인
  if (Check_Reference_id != 0.0) {
    index_FST = 0;
    exitg1 = false;
    while ((!exitg1) && (index_FST < 64)) {
      d = Association_Map[index_FST + 64];
      if ((d == Check_Reference_id) &&
          ((Association_Map[index_FST] + d) - Check_Reference_id != 0.0)) {
        reference_fused_flag = 1;
        exitg1 = true;
      } else {
        index_FST++;
      }
    }
  }
  if (reference_fused_flag == 0) {
    double d1;
    double tmp_target_number;
    int id_FST;
    int target_fused_flag;
    //  1. 현재 reference에서 target 선정 (우선 제일 가까운 1 target 선정했지만,
    //  추후 2 norm으로 sorting && 각 threshold  통과하는 최대 5개 target
    //  선정하여 다른 조건까지 추가해서 선정)
    for (target_fused_flag = 0; target_fused_flag < 64; target_fused_flag++) {
      x_data[target_fused_flag] = tmp_norm_residual_data
          [(static_cast<int>(Check_Reference_id) + 64 * target_fused_flag) - 1];
    }
    coder::internal::sort(x_data, iidx_data, iidx_size);
    for (target_fused_flag = 0; target_fused_flag < 64; target_fused_flag++) {
      x_data[target_fused_flag] = iidx_data[target_fused_flag];
    }
    tmp_target_number = 0.0;
    for (reference_fused_flag = 0; reference_fused_flag < 5;
         reference_fused_flag++) {
      tmp_target_candidate_id[reference_fused_flag] = 0;
    }
    reference_fused_flag = 0;
    exitg1 = false;
    while ((!exitg1) && (reference_fused_flag < 64)) {
      index_FST = static_cast<int>(x_data[reference_fused_flag]);
      //  sorted_target_id가 association map 에서 사용되지 않았는지 확인
      target_fused_flag = 0;
      for (id_FST = 0; id_FST < 64; id_FST++) {
        d = Association_Map[id_FST];
        if ((d == index_FST) && ((d + Association_Map[id_FST + 64]) -
                                     static_cast<double>(index_FST) !=
                                 0.0)) {
          target_fused_flag = 1;
        }
      }
      if (target_fused_flag == 0) {
        //  gating : y, x, vx
        d = tmp_residual[3 * (static_cast<int>(Check_Reference_id) - 1) +
                         192 * (index_FST - 1)];
        if ((d >
             gating_threshold_y[static_cast<int>(Check_Reference_id) - 1]) &&
            (d <
             gating_threshold_y[static_cast<int>(Check_Reference_id) + 63])) {
          d1 = tmp_residual[(3 * (static_cast<int>(Check_Reference_id) - 1) +
                             192 * (index_FST - 1)) +
                            1];
          if ((d1 >
               gating_threshold_x[static_cast<int>(Check_Reference_id) - 1]) &&
              (d1 <
               gating_threshold_x[static_cast<int>(Check_Reference_id) + 63]) &&
              (tmp_residual[(3 * (static_cast<int>(Check_Reference_id) - 1) +
                             192 * (index_FST - 1)) +
                            2] >
               gating_threshold_vx[static_cast<int>(Check_Reference_id) - 1]) &&
              (d < gating_threshold_vx[static_cast<int>(Check_Reference_id) +
                                       63])) {
            tmp_target_number++;
            tmp_target_candidate_id[static_cast<int>(tmp_target_number) - 1] =
                index_FST;
            if (tmp_target_number == 5.0) {
              exitg1 = true;
            } else {
              reference_fused_flag++;
            }
          } else {
            reference_fused_flag++;
          }
        } else {
          reference_fused_flag++;
        }
      } else {
        reference_fused_flag++;
      }
    }
    //  2. 선택된 target(우선 제일 가까운 1 target)에서 가까운 reference 검색(2
    //  norm으로 sorting && 각 threshold  통과하는 최대 5개 reference 선정)
    if (tmp_target_number != 0.0) {
      target_fused_flag = static_cast<int>(tmp_target_number);
      for (id_FST = 0; id_FST < target_fused_flag; id_FST++) {
        for (reference_fused_flag = 0; reference_fused_flag < 64;
             reference_fused_flag++) {
          x_data[reference_fused_flag] =
              tmp_norm_residual_data[reference_fused_flag +
                                     64 *
                                         (tmp_target_candidate_id[id_FST] - 1)];
        }
        coder::internal::b_sort(x_data, iidx_data, &reference_fused_flag);
        tmp_target_number = 0.0;
        for (reference_fused_flag = 0; reference_fused_flag < 5;
             reference_fused_flag++) {
          tmp_reference_candidate_id[reference_fused_flag] = 0;
          tmp_reference_candidate_residual[reference_fused_flag] = 300.0;
        }
        reference_fused_flag = 0;
        exitg1 = false;
        while ((!exitg1) && (reference_fused_flag < 64)) {
          //  reference 검색
          d = tmp_residual[3 * (iidx_data[reference_fused_flag] - 1) +
                           192 * (tmp_target_candidate_id[id_FST] - 1)];
          if ((d > gating_threshold_y[iidx_data[reference_fused_flag] - 1]) &&
              (d < gating_threshold_y[iidx_data[reference_fused_flag] + 63])) {
            d1 = tmp_residual[(3 * (iidx_data[reference_fused_flag] - 1) +
                               192 * (tmp_target_candidate_id[id_FST] - 1)) +
                              1];
            if ((d1 >
                 gating_threshold_x[iidx_data[reference_fused_flag] - 1]) &&
                (d1 <
                 gating_threshold_x[iidx_data[reference_fused_flag] + 63]) &&
                (tmp_residual[(3 * (iidx_data[reference_fused_flag] - 1) +
                               192 * (tmp_target_candidate_id[id_FST] - 1)) +
                              2] >
                 gating_threshold_vx[iidx_data[reference_fused_flag] - 1]) &&
                (d <
                 gating_threshold_vx[iidx_data[reference_fused_flag] + 63])) {
              tmp_target_number++;
              tmp_reference_candidate_id[static_cast<int>(tmp_target_number) -
                                         1] = iidx_data[reference_fused_flag];
              tmp_reference_candidate_residual
                  [static_cast<int>(tmp_target_number) - 1] =
                      x_data[reference_fused_flag];
              if (tmp_target_number == 5.0) {
                exitg1 = true;
              } else {
                reference_fused_flag++;
              }
            } else {
              reference_fused_flag++;
            }
          } else {
            reference_fused_flag++;
          }
        }
        if (tmp_target_number != 0.0) {
          coder::internal::sort(tmp_reference_candidate_residual, iidx);
          for (reference_fused_flag = 0; reference_fused_flag < 5;
               reference_fused_flag++) {
            tmp_reference_candidate_residual[reference_fused_flag] =
                iidx[reference_fused_flag];
          }
          reference_fused_flag = static_cast<int>(tmp_target_number);
          for (index_FST = 0; index_FST < reference_fused_flag; index_FST++) {
            if (tmp_reference_candidate_id
                    [static_cast<int>(
                         tmp_reference_candidate_residual[index_FST]) -
                     1] == Check_Reference_id) {
              Fused_Target_id = tmp_target_candidate_id[id_FST];
            }
          }
        }
      }
    }
  }
  return Fused_Target_id;
}

//
// Arguments    : const double Reference_Track[544]
//                double tmp_gating_threshold_y[128]
//                double tmp_gating_threshold_x[128]
//                double tmp_gating_threshold_vy[128]
//                double tmp_gating_threshold_vx[128]
// Return Type  : void
//
static void Create_Gating_Threshold_VRU(const double Reference_Track[544],
                                        double tmp_gating_threshold_y[128],
                                        double tmp_gating_threshold_x[128],
                                        double tmp_gating_threshold_vy[128],
                                        double tmp_gating_threshold_vx[128])
{
  for (int index_Reference{0}; index_Reference < 32; index_Reference++) {
    double d;
    double d1;
    d = Reference_Track[17 * index_Reference + 8];
    d1 = Reference_Track[17 * index_Reference + 7];
    if (d * d + d1 * d1 != 0.0) {
      if ((d1 > 0.0) && (d1 <= 25.0)) {
        //  ROI1
        tmp_gating_threshold_y[index_Reference] = -1.0;
        tmp_gating_threshold_y[index_Reference + 64] = 1.0;
        tmp_gating_threshold_x[index_Reference] = -2.5;
        tmp_gating_threshold_x[index_Reference + 64] = 2.5;
        tmp_gating_threshold_vy[index_Reference] = -1.0;
        tmp_gating_threshold_vy[index_Reference + 64] = 1.0;
        tmp_gating_threshold_vx[index_Reference] = -1.5;
        tmp_gating_threshold_vx[index_Reference + 64] = 1.5;
      } else if ((d1 > 25.0) && (d1 <= 35.0)) {
        //  ROI2
        tmp_gating_threshold_y[index_Reference] = -0.1 * (d - 25.0) - 1.0;
        tmp_gating_threshold_y[index_Reference + 64] = 0.1 * (d - 25.0) + 1.0;
        tmp_gating_threshold_x[index_Reference] = -0.25 * (d1 - 25.0) - 2.5;
        tmp_gating_threshold_x[index_Reference + 64] = 0.25 * (d1 - 25.0) + 2.5;
        tmp_gating_threshold_vy[index_Reference] = -1.5;
        tmp_gating_threshold_vy[index_Reference + 64] = 1.5;
        tmp_gating_threshold_vx[index_Reference] = -2.0;
        tmp_gating_threshold_vx[index_Reference + 64] = 2.0;
      } else if ((d1 > 35.0) && (d1 <= 120.0)) {
        //  ROI3
        tmp_gating_threshold_y[index_Reference] = -2.0;
        tmp_gating_threshold_y[index_Reference + 64] = 2.0;
        tmp_gating_threshold_x[index_Reference] = -5.0;
        tmp_gating_threshold_x[index_Reference + 64] = 5.0;
        tmp_gating_threshold_vy[index_Reference] = -2.0;
        tmp_gating_threshold_vy[index_Reference + 64] = 2.0;
        tmp_gating_threshold_vx[index_Reference] = -2.5;
        tmp_gating_threshold_vx[index_Reference + 64] = 2.5;
      }
    }
  }
}

//
// y_threshold = zeros(Fusion_Track_Param.TRACK_NUMBER,2);
//  x_threshold = zeros(Fusion_Track_Param.TRACK_NUMBER,2);
//  vy_threshold = zeros(Fusion_Track_Param.TRACK_NUMBER,2);
//  vx_threshold = zeros(Fusion_Track_Param.TRACK_NUMBER,2);
//
//  ROI_near_x_min = 0;
//  ROI_near_x_max = 0;
//  ROI_far_x_min = 0;
//  ROI_far_x_max = 0;
//  ROI_far_x_slope = 0;
//
//  y_threshold_near = 0;
//  y_threshold_far = 0;
//  x_threshold_near = 0;
//  vy_threshold_near = 0;
//  vy_threshold_far = 0;
//  vx_threshold_near = 0;
//  vx_threshold_far = 0;
//
//  reference_exist_flag = 0;
//
// Arguments    : const double Reference_Track[544]
//                double tmp_gating_threshold_y[128]
//                double tmp_gating_threshold_x[128]
//                double tmp_gating_threshold_vy[128]
//                double tmp_gating_threshold_vx[128]
// Return Type  : void
//
static void Create_Gating_Threshold_Vehicle(const double Reference_Track[544],
                                            double tmp_gating_threshold_y[128],
                                            double tmp_gating_threshold_x[128],
                                            double tmp_gating_threshold_vy[128],
                                            double tmp_gating_threshold_vx[128])
{
  for (int index_Reference{0}; index_Reference < 32; index_Reference++) {
    double d;
    double d1;
    d = Reference_Track[17 * index_Reference + 8];
    d1 = Reference_Track[17 * index_Reference + 7];
    if (d * d + d1 * d1 != 0.0) {
      if ((d1 > 0.0) && (d1 <= 40.0)) {
        //  front near
        tmp_gating_threshold_y[index_Reference] = -2.7;
        tmp_gating_threshold_y[index_Reference + 64] = 2.7;
        tmp_gating_threshold_x[index_Reference] = -7.0;
        tmp_gating_threshold_x[index_Reference + 64] = 7.0;
        tmp_gating_threshold_vy[index_Reference] = -5.0;
        tmp_gating_threshold_vy[index_Reference + 64] = 5.0;
        tmp_gating_threshold_vx[index_Reference] = -6.0;
        tmp_gating_threshold_vx[index_Reference + 64] = 6.0;
      } else if ((d1 > 40.0) && (d1 <= 70.0)) {
        //  front far
        tmp_gating_threshold_y[index_Reference] = -2.7;
        tmp_gating_threshold_y[index_Reference + 64] = 2.7;
        tmp_gating_threshold_x[index_Reference] = -0.3333 * (d1 - 40.0) - 7.0;
        tmp_gating_threshold_x[index_Reference + 64] =
            0.3333 * (d1 - 40.0) + 7.0;
        tmp_gating_threshold_vy[index_Reference] = -5.0;
        tmp_gating_threshold_vy[index_Reference + 64] = 5.0;
        tmp_gating_threshold_vx[index_Reference] = -6.0;
        tmp_gating_threshold_vx[index_Reference + 64] = 6.0;
      } else if (d1 > 70.0) {
        tmp_gating_threshold_y[index_Reference] = -2.7;
        tmp_gating_threshold_y[index_Reference + 64] = 2.7;
        tmp_gating_threshold_x[index_Reference] = -17.0;
        tmp_gating_threshold_x[index_Reference + 64] = 17.0;
        tmp_gating_threshold_vy[index_Reference] = -5.0;
        tmp_gating_threshold_vy[index_Reference + 64] = 5.0;
        tmp_gating_threshold_vx[index_Reference] = -6.0;
        tmp_gating_threshold_vx[index_Reference + 64] = 6.0;
      }
    }
  }
}

//
// Arguments    : const double Reference_Track[544]
//                const double Target_Track[360]
//                double tmp_residual[12288]
//                double tmp_norm_residual[4096]
// Return Type  : void
//
static void Residual_NG_Vehicle(const double Reference_Track[544],
                                const double Target_Track[360],
                                double tmp_residual[12288],
                                double tmp_norm_residual[4096])
{
  double id_Target;
  int target_exist_flag;
  for (target_exist_flag = 0; target_exist_flag < 12288; target_exist_flag++) {
    tmp_residual[target_exist_flag] = 300.0;
  }
  //  (residual state(Y, X) X Reference number X Target number)
  for (target_exist_flag = 0; target_exist_flag < 4096; target_exist_flag++) {
    tmp_norm_residual[target_exist_flag] = 300.0;
  }
  //  (Reference number X Target number)
  id_Target = 0.0;
  //  Residual calculation
  for (int index_Reference{0}; index_Reference < 32; index_Reference++) {
    double d;
    double d1;
    //  check reference track existence(ID or position)
    d = Reference_Track[17 * index_Reference + 8];
    d1 = Reference_Track[17 * index_Reference + 7];
    if (d * d + d1 * d1 != 0.0) {
      for (int index_Target{0}; index_Target < 10; index_Target++) {
        double scale;
        int target_bicycle_class_flag;
        int target_pedestrian_class_flag;
        //  check target track existence(ID or position)
        target_exist_flag = 0;
        target_pedestrian_class_flag = 0;
        target_bicycle_class_flag = 0;
        scale = Target_Track[36 * index_Target + 6];
        if (scale != 0.0) {
          target_exist_flag = 1;
          id_Target = scale;
        }
        //  If target type = FVT, check classification is VRU
        scale = Target_Track[36 * index_Target];
        if (scale == 5.0) {
          target_pedestrian_class_flag = 1;
        } else if ((scale == 3.0) || (scale == 4.0)) {
          target_bicycle_class_flag = 1;
        }
        if ((target_exist_flag == 1) && (target_pedestrian_class_flag == 0) &&
            (target_bicycle_class_flag == 0)) {
          double absxk;
          double t;
          double y;
          //  prep. pos
          //  prep pos
          target_exist_flag =
              3 * index_Reference + 192 * (static_cast<int>(id_Target) - 1);
          tmp_residual[target_exist_flag] =
              d - Target_Track[36 * index_Target + 24];
          tmp_residual[target_exist_flag + 1] =
              d1 - Target_Track[36 * index_Target + 25];
          tmp_residual[target_exist_flag + 2] =
              Reference_Track[17 * index_Reference + 9] -
              Target_Track[36 * index_Target + 27];
          //  2-norm calculation
          scale = 3.3121686421112381E-170;
          absxk = std::abs(tmp_residual[target_exist_flag]);
          if (absxk > 3.3121686421112381E-170) {
            y = 1.0;
            scale = absxk;
          } else {
            t = absxk / 3.3121686421112381E-170;
            y = t * t;
          }
          absxk = std::abs(tmp_residual[target_exist_flag + 1]);
          if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            y += t * t;
          }
          absxk = std::abs(tmp_residual[target_exist_flag + 2]);
          if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            y += t * t;
          }
          tmp_norm_residual[index_Reference + ((static_cast<int>(id_Target) - 1)
                                               << 6)] = scale * std::sqrt(y);
        }
      }
    }
  }
}

//
// Arguments    : const double Front_Vision_Track[360]
//                const double Front_Radar_Track[544]
//                double Fusion_Object[768]
//                double Association_Map[128]
// Return Type  : void
//
void gating(const double Front_Vision_Track[360],
            const double Front_Radar_Track[544], double Fusion_Object[768],
            double Association_Map[128])
{
  static double tmp_residual[12288];
  coder::array<double, 3U> c_tmp_residual;
  coder::array<double, 3U> d_tmp_residual;
  double b_tmp_residual[12288];
  double b_tmp_norm_residual[4096];
  double tmp_norm_residual[4096];
  double Threshold_VEHICLE_FRT_FVT_vx[128];
  double Threshold_VEHICLE_FRT_FVT_x[128];
  double Threshold_VEHICLE_FRT_FVT_y[128];
  double Threshold_VRU_FRT_FVT_vx[128];
  double Threshold_VRU_FRT_FVT_x[128];
  double Threshold_VRU_FRT_FVT_y[128];
  double expl_temp[128];
  double d;
  double d1;
  double scale;
  int Tmp_reference_fused_flag;
  int index_FST;
  int index_Target;
  int target_bicycle_class_flag;
  int target_exist_flag;
  int target_pedestrian_class_flag;
  bool exitg1;
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
  //  Fusion Object : [12 X 64]     Output
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
  //  Association_Map : [64 X 2]     Output
  // --------------------------------------------------------------------------
  //  1  : Front Vision Track
  //  2  : Front Radar Track
  // --------------------------------------------------------------------------
  //  Parameter of norm gating
  // --------------------------------------------------------------------------
  //  ASSOCIATION.GATING.INPUT_NUMBER*2 : min and max of INPUT FEATURE
  //  ASSOCIATION.GATING.INPUT_NUMBER*2 : min and max of INPUT FEATURE
  //  FRT to FVT norm gating threshold
  Create_Gating_Threshold_Vehicle(
      Front_Radar_Track, Threshold_VEHICLE_FRT_FVT_y,
      Threshold_VEHICLE_FRT_FVT_x, expl_temp, Threshold_VEHICLE_FRT_FVT_vx);
  // --------------------------------------------------------------------------
  //  Parameter of norm gating for Pedestrian
  // --------------------------------------------------------------------------
  Create_Gating_Threshold_VRU(Front_Radar_Track, Threshold_VRU_FRT_FVT_y,
                              Threshold_VRU_FRT_FVT_x, expl_temp,
                              Threshold_VRU_FRT_FVT_vx);
  // --------------------------------------------------------------------------
  //  Initialization
  // --------------------------------------------------------------------------
  // --------------------------------------------------------------------------
  //  Residual Calculation of Norm gating for Vehicle
  // --------------------------------------------------------------------------
  Residual_NG_Vehicle(Front_Radar_Track, Front_Vision_Track, tmp_residual,
                      tmp_norm_residual);
  //  (residual state X Reference number X Target number)
  //  (Reference number X Target number)
  // --------------------------------------------------------------------------
  //  Residual Calculation of Norm gating for VRU
  // --------------------------------------------------------------------------
  for (target_exist_flag = 0; target_exist_flag < 12288; target_exist_flag++) {
    b_tmp_residual[target_exist_flag] = 300.0;
  }
  //  (residual state(Y, X) X Reference number X Target number)
  for (target_exist_flag = 0; target_exist_flag < 4096; target_exist_flag++) {
    b_tmp_norm_residual[target_exist_flag] = 300.0;
  }
  //  (Reference number X Target number)
  //  Residual calculation
  for (Tmp_reference_fused_flag = 0; Tmp_reference_fused_flag < 32;
       Tmp_reference_fused_flag++) {
    double id_Target;
    //  check reference track existence(ID or position)
    id_Target = 0.0;
    d = Front_Radar_Track[17 * Tmp_reference_fused_flag + 8];
    d1 = Front_Radar_Track[17 * Tmp_reference_fused_flag + 7];
    if (d * d + d1 * d1 != 0.0) {
      for (index_Target = 0; index_Target < 10; index_Target++) {
        //  check target track existence(ID or position)
        target_exist_flag = 0;
        target_pedestrian_class_flag = 0;
        target_bicycle_class_flag = 0;
        scale = Front_Vision_Track[36 * index_Target + 6];
        if (scale != 0.0) {
          target_exist_flag = 1;
          id_Target = scale;
        }
        //  If target type = FVT, check classification is VRU
        scale = Front_Vision_Track[36 * index_Target];
        if (scale == 5.0) {
          target_pedestrian_class_flag = 1;
        } else if ((scale == 3.0) || (scale == 4.0)) {
          target_bicycle_class_flag = 1;
        }
        if ((target_exist_flag == 1) && ((target_pedestrian_class_flag == 1) ||
                                         (target_bicycle_class_flag == 1))) {
          double absxk;
          double t;
          double y;
          //  prep. pos
          //  prep pos
          target_exist_flag = 3 * Tmp_reference_fused_flag +
                              192 * (static_cast<int>(id_Target) - 1);
          b_tmp_residual[target_exist_flag] =
              d - Front_Vision_Track[36 * index_Target + 24];
          b_tmp_residual[target_exist_flag + 1] =
              d1 - Front_Vision_Track[36 * index_Target + 25];
          b_tmp_residual[target_exist_flag + 2] =
              Front_Radar_Track[17 * Tmp_reference_fused_flag + 9] -
              Front_Vision_Track[36 * index_Target + 27];
          //  2-norm calculation
          scale = 3.3121686421112381E-170;
          absxk = std::abs(b_tmp_residual[target_exist_flag]);
          if (absxk > 3.3121686421112381E-170) {
            y = 1.0;
            scale = absxk;
          } else {
            t = absxk / 3.3121686421112381E-170;
            y = t * t;
          }
          absxk = std::abs(b_tmp_residual[target_exist_flag + 1]);
          if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            y += t * t;
          }
          absxk = std::abs(b_tmp_residual[target_exist_flag + 2]);
          if (absxk > scale) {
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            y += t * t;
          }
          b_tmp_norm_residual[Tmp_reference_fused_flag +
                              ((static_cast<int>(id_Target) - 1) << 6)] =
              scale * std::sqrt(y);
        }
      }
    }
  }
  //  (residual state X Reference number X Target number)
  //  (Reference number X Target number)
  // --------------------------------------------------------------------------
  //  Norm gating for Vehicle
  // --------------------------------------------------------------------------
  //  (Front Radar Track) to (Front Vision Track)
  for (target_pedestrian_class_flag = 0; target_pedestrian_class_flag < 32;
       target_pedestrian_class_flag++) {
    Tmp_reference_fused_flag = 0;
    d = Front_Radar_Track[17 * target_pedestrian_class_flag + 8];
    d1 = Front_Radar_Track[17 * target_pedestrian_class_flag + 7];
    if (d * d + d1 * d1 != 0.0) {
      index_FST = 0;
      exitg1 = false;
      while ((!exitg1) && (index_FST < 64)) {
        if ((Association_Map[index_FST + 64] ==
             static_cast<double>(target_pedestrian_class_flag) + 1.0) &&
            (Association_Map[index_FST] != 0.0)) {
          Tmp_reference_fused_flag = 1;
          exitg1 = true;
        } else {
          index_FST++;
        }
      }
      if (Tmp_reference_fused_flag == 0) {
        c_tmp_residual.set(&tmp_residual[0], 3, 64, 64);
        scale = Check_Association_NG2(
            static_cast<double>(target_pedestrian_class_flag) + 1.0,
            c_tmp_residual, tmp_norm_residual, Threshold_VEHICLE_FRT_FVT_y,
            Threshold_VEHICLE_FRT_FVT_x, Threshold_VEHICLE_FRT_FVT_vx,
            Association_Map);
        if (scale + static_cast<double>(target_pedestrian_class_flag + 1) !=
            0.0) {
          target_exist_flag = 0;
          exitg1 = false;
          while ((!exitg1) && (target_exist_flag < 64)) {
            if (Association_Map[target_exist_flag] +
                    Association_Map[target_exist_flag + 64] ==
                0.0) {
              Association_Map[target_exist_flag] = scale;
              Association_Map[target_exist_flag + 64] = 0.0;
              exitg1 = true;
            } else {
              target_exist_flag++;
            }
          }
        }
      }
    }
  }
  //  (Front Vision Track)
  for (index_Target = 0; index_Target < 10; index_Target++) {
    scale = 0.0;
    target_exist_flag = 0;
    Tmp_reference_fused_flag = 0;
    target_pedestrian_class_flag = 0;
    target_bicycle_class_flag = 0;
    d = Front_Vision_Track[36 * index_Target + 6];
    if (d != 0.0) {
      scale = d;
      target_exist_flag = 1;
      index_FST = 0;
      exitg1 = false;
      while ((!exitg1) && (index_FST < 64)) {
        if (Association_Map[index_FST] == d) {
          Tmp_reference_fused_flag = 1;
          exitg1 = true;
        } else {
          index_FST++;
        }
      }
    }
    d = Front_Vision_Track[36 * index_Target];
    if (d == 5.0) {
      target_pedestrian_class_flag = 1;
    } else if ((d == 3.0) || (d == 4.0)) {
      target_bicycle_class_flag = 1;
    }
    if ((target_exist_flag == 1) && (Tmp_reference_fused_flag == 0) &&
        (target_pedestrian_class_flag == 0) &&
        (target_bicycle_class_flag == 0) && (scale != 0.0)) {
      target_exist_flag = 0;
      exitg1 = false;
      while ((!exitg1) && (target_exist_flag < 64)) {
        if (Association_Map[target_exist_flag] +
                Association_Map[target_exist_flag + 64] ==
            0.0) {
          Association_Map[target_exist_flag] = scale;
          Association_Map[target_exist_flag + 64] = 0.0;
          exitg1 = true;
        } else {
          target_exist_flag++;
        }
      }
    }
  }
  // --------------------------------------------------------------------------
  //  Association for Pedestrian
  // --------------------------------------------------------------------------
  //  (Front Radar Track) to (Front Vision Track)
  for (target_pedestrian_class_flag = 0; target_pedestrian_class_flag < 32;
       target_pedestrian_class_flag++) {
    Tmp_reference_fused_flag = 0;
    d = Front_Radar_Track[17 * target_pedestrian_class_flag + 8];
    d1 = Front_Radar_Track[17 * target_pedestrian_class_flag + 7];
    if (d * d + d1 * d1 != 0.0) {
      index_FST = 0;
      exitg1 = false;
      while ((!exitg1) && (index_FST < 64)) {
        if ((Association_Map[index_FST + 64] ==
             static_cast<double>(target_pedestrian_class_flag) + 1.0) &&
            (Association_Map[index_FST] != 0.0)) {
          Tmp_reference_fused_flag = 1;
          exitg1 = true;
        } else {
          index_FST++;
        }
      }
      if (Tmp_reference_fused_flag == 0) {
        d_tmp_residual.set(&b_tmp_residual[0], 3, 64, 64);
        scale = Check_Association_NG2(
            static_cast<double>(target_pedestrian_class_flag) + 1.0,
            d_tmp_residual, b_tmp_norm_residual, Threshold_VRU_FRT_FVT_y,
            Threshold_VRU_FRT_FVT_x, Threshold_VRU_FRT_FVT_vx, Association_Map);
        if (scale + static_cast<double>(target_pedestrian_class_flag + 1) !=
            0.0) {
          target_exist_flag = 0;
          exitg1 = false;
          while ((!exitg1) && (target_exist_flag < 64)) {
            if (Association_Map[target_exist_flag] +
                    Association_Map[target_exist_flag + 64] ==
                0.0) {
              Association_Map[target_exist_flag] = scale;
              Association_Map[target_exist_flag + 64] = 0.0;
              exitg1 = true;
            } else {
              target_exist_flag++;
            }
          }
        }
      }
    }
  }
  //  (Front Vision Track)
  for (index_Target = 0; index_Target < 10; index_Target++) {
    scale = 0.0;
    target_exist_flag = 0;
    Tmp_reference_fused_flag = 0;
    target_pedestrian_class_flag = 0;
    target_bicycle_class_flag = 0;
    d = Front_Vision_Track[36 * index_Target + 6];
    if (d != 0.0) {
      scale = d;
      target_exist_flag = 1;
      index_FST = 0;
      exitg1 = false;
      while ((!exitg1) && (index_FST < 64)) {
        if (Association_Map[index_FST] == d) {
          Tmp_reference_fused_flag = 1;
          exitg1 = true;
        } else {
          index_FST++;
        }
      }
    }
    d = Front_Vision_Track[36 * index_Target];
    if (d == 5.0) {
      target_pedestrian_class_flag = 1;
    } else if ((d == 3.0) || (d == 4.0)) {
      target_bicycle_class_flag = 1;
    }
    if ((target_exist_flag == 1) && (Tmp_reference_fused_flag == 0) &&
        ((target_pedestrian_class_flag == 1) ||
         (target_bicycle_class_flag == 1)) &&
        (scale != 0.0)) {
      target_exist_flag = 0;
      exitg1 = false;
      while ((!exitg1) && (target_exist_flag < 64)) {
        if (Association_Map[target_exist_flag] +
                Association_Map[target_exist_flag + 64] ==
            0.0) {
          Association_Map[target_exist_flag] = scale;
          Association_Map[target_exist_flag + 64] = 0.0;
          exitg1 = true;
        } else {
          target_exist_flag++;
        }
      }
    }
  }
  // --------------------------------------------------------------------------
  //  Creation of Fusion Object
  // --------------------------------------------------------------------------
  for (index_FST = 0; index_FST < 64; index_FST++) {
    d = Association_Map[index_FST + 64];
    d1 = Association_Map[index_FST];
    if (d1 + d != 0.0) {
      //  FVT + FRT
      if ((d1 != 0.0) && (d != 0.0)) {
        //  id -> find index
        // --------------------------------------------------------------------------
        //  function
        // --------------------------------------------------------------------------
        // --------------------------------------------------------------------------
        //  function
        // --------------------------------------------------------------------------
        Fusion_Object[12 * index_FST] = Front_Vision_Track[-12];
        target_exist_flag = 17 * (static_cast<int>(d) - 1);
        Fusion_Object[12 * index_FST + 1] =
            Front_Radar_Track[target_exist_flag + 7];
        Fusion_Object[12 * index_FST + 2] = Front_Vision_Track[-10];
        Fusion_Object[12 * index_FST + 3] =
            Front_Radar_Track[target_exist_flag + 9];
        Fusion_Object[12 * index_FST + 4] = Front_Vision_Track[-19];
        Fusion_Object[12 * index_FST + 5] = Front_Vision_Track[-21];
        Fusion_Object[12 * index_FST + 6] = Front_Vision_Track[-7];
        Fusion_Object[12 * index_FST + 7] = d1;
        Fusion_Object[12 * index_FST + 8] = d;
        Fusion_Object[12 * index_FST + 9] =
            Front_Radar_Track[target_exist_flag + 15];
        Fusion_Object[12 * index_FST + 10] =
            Front_Radar_Track[target_exist_flag + 16];
        //  FVT
      } else if ((d1 != 0.0) && (d == 0.0)) {
        //  id -> find index
        // --------------------------------------------------------------------------
        //  function
        // --------------------------------------------------------------------------
        Fusion_Object[12 * index_FST] = Front_Vision_Track[-12];
        Fusion_Object[12 * index_FST + 1] = Front_Vision_Track[-11];
        Fusion_Object[12 * index_FST + 2] = Front_Vision_Track[-10];
        Fusion_Object[12 * index_FST + 3] = Front_Vision_Track[-9];
        Fusion_Object[12 * index_FST + 4] = Front_Vision_Track[-19];
        Fusion_Object[12 * index_FST + 5] = Front_Vision_Track[-21];
        Fusion_Object[12 * index_FST + 6] = Front_Vision_Track[-7];
        Fusion_Object[12 * index_FST + 7] = d1;
        Fusion_Object[12 * index_FST + 9] = Front_Vision_Track[-4];
        Fusion_Object[12 * index_FST + 10] = Front_Vision_Track[-1];
        //  FRT
      } else if ((d1 == 0.0) && (d != 0.0)) {
        //  id -> find index
        // --------------------------------------------------------------------------
        //  function
        // --------------------------------------------------------------------------
        target_exist_flag = 17 * (static_cast<int>(d) - 1);
        Fusion_Object[12 * index_FST] =
            Front_Radar_Track[target_exist_flag + 8];
        Fusion_Object[12 * index_FST + 1] =
            Front_Radar_Track[target_exist_flag + 7];
        Fusion_Object[12 * index_FST + 2] =
            Front_Radar_Track[target_exist_flag + 10];
        Fusion_Object[12 * index_FST + 3] =
            Front_Radar_Track[target_exist_flag + 9];
        Fusion_Object[12 * index_FST + 4] = 0.0;
        Fusion_Object[12 * index_FST + 5] = 0.0;
        Fusion_Object[12 * index_FST + 6] = 0.0;
        Fusion_Object[12 * index_FST + 8] = d;
        Fusion_Object[12 * index_FST + 9] =
            Front_Radar_Track[target_exist_flag + 15];
        Fusion_Object[12 * index_FST + 10] =
            Front_Radar_Track[target_exist_flag + 16];
      }
    }
  }
}

//
// File trailer for gating.cpp
//
// [EOF]
//
