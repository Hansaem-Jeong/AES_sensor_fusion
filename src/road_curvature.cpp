//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: road_curvature.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "road_curvature.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"
#include "unit_conversion_initialize.h"

// Function Definitions
//
// #CODEGEN
//
// Arguments    : const double Front_Vision_Lane[68]
//                const double In_Vehicle_Sensor[19]
//                double *Road_Curvature
//                double *Road_Slope
// Return Type  : void
//
void road_curvature(const double Front_Vision_Lane[68],
                    const double In_Vehicle_Sensor[19], double *Road_Curvature,
                    double *Road_Slope)
{
  if (!isInitialized_unit_conversion) {
    unit_conversion_initialize();
  }
  // --------------------------------------------------------------------------
  //  Front_Vision_Lane : [34 X 2(Left, Right)]     Input
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
  //  In_Vehicle_Sensor : [19 X 1]     Input
  // --------------------------------------------------------------------------
  //  1  : Lateral Acceleration
  //  2  : Longitudinal Acceleration
  //  3  : Steering Angle
  //  4  : Steering Speed
  //  5  : Wheel Speed FL
  //  6  : Wheel Speed FR
  //  7  : Wheel Speed RL
  //  8  : Wheel Speed RR
  //  9  : Yawrate
  //  10 : Preprocessing Lateral Acceleration
  //  11 : Preprocessing Longitudinal Acceleration
  //  12 : Preprocessing(Unit conversion) Steering Angle
  //  13 : Preprocessing(Unit conversion) Steering Speed
  //  14 : Preprocessing(Unit conversion) Wheel Speed FL
  //  15 : Preprocessing(Unit conversion) Wheel Speed FR
  //  16 : Preprocessing(Unit conversion) Wheel Speed RL
  //  17 : Preprocessing(Unit conversion) Wheel Speed RR
  //  18 : Preprocessing(Unit conversion) Yawrate
  //  19 : Preprocessing Vehicle Speed
  *Road_Slope = 0.0;
  if ((Front_Vision_Lane[17] >= 3.0) && (Front_Vision_Lane[51] >= 3.0)) {
    *Road_Curvature = 0.5 * (Front_Vision_Lane[28] + Front_Vision_Lane[62]);
    *Road_Slope = 0.5 * (Front_Vision_Lane[27] + Front_Vision_Lane[61]);
  } else if ((Front_Vision_Lane[17] < 3.0) && (Front_Vision_Lane[51] >= 3.0)) {
    *Road_Curvature = Front_Vision_Lane[62];
    *Road_Slope = Front_Vision_Lane[61];
  } else if ((Front_Vision_Lane[17] >= 3.0) && (Front_Vision_Lane[51] < 3.0)) {
    *Road_Curvature = Front_Vision_Lane[28];
    *Road_Slope = Front_Vision_Lane[27];
  } else {
    *Road_Curvature = In_Vehicle_Sensor[17] / In_Vehicle_Sensor[18];
  }
}

//
// File trailer for road_curvature.cpp
//
// [EOF]
//
