//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: unit_conversion_initialize.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 13-Dec-2021 00:36:36
//

// Include Files
#include "unit_conversion_initialize.h"
#include "filter_in_vehicle_sensor.h"
#include "rt_nonfinite.h"
#include "unit_conversion_data.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void unit_conversion_initialize()
{
  filter_in_vehicle_sensor_init();
  isInitialized_unit_conversion = true;
}

//
// File trailer for unit_conversion_initialize.cpp
//
// [EOF]
//
