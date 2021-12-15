struct in_vehicle_sensor {
	double LAT_ACC;
	double LONG_ACC;
	double SAS_Angle;
	double SAS_Speed;
	double WHL_SPD_FL;
	double WHL_SPD_FR;
	double WHL_SPD_RL;
	double WHL_SPD_RR;
	double YAW_RATE;
};

struct front_vision_track {
	double Object_Class;
	double Longtitudinal_Distance;
	double Motion_Category;
	double Lateral_Distance;
	double Absolute_Long_Velocity;
	double Absolute_Lateral_Velocity;
	double ID;
	double Predicted_Object;
	double Angle_Right;
	double Motion_Orientation;
	double Angle_Rate_Mean;
	double Absolute_Long_Acc;
	double Lane_Assignment;
	double Length;
	double Brake_Light;
	double Width;
	double AliveCounter;
	double Turn_Indicator_Left;
	double Turn_Indicator_Right;
	double Obstacle_Heading;
	double Obstacle_Height_1;
	double Obstacle_Side_1;
	double Obstacle_Height_2;
	double Obstacle_Side_2;
};

struct front_vision_lane_right {
	double Rh_View_Start_Longitudinal_Dist;
	double Rh_View_End_Longitudinal_Dist;
	double LaneMark_Confidence_Rn_ME;
	double LaneMark_Confidence_Rh_ME; // msg error
	double RightLanePrediction;
	double Rh_Neightbor_Avail;
	double Rh_Neightbor_Type;
	double Rh_Guardrail;
	double Highway_Merge_Right;
	double Highway_Exit_Right;
	double RightLaneColorInfo;
	double Rh_ViewRange_StartPoint;
	double Rh_Neighbor_LaneMark_Pos_C0;
	double Rh_Neighbor_LaneMark_Model_B_C1;
	double Rh_Neighbor_LaneMark_Model_A_C2;
	double Rh_Neighbor_LaneMark_Model_dA_C3;
	double Classification_Rh_ME;
	double Quality_Rh_ME; // msg error
	double Marker_Width_Rh_ME;
	double LaneMarkPosition_C0_Rh_ME;
	double LaneMarkHeadingAngle_C1_Rh_ME;
	double LaneMarkModelA_C2_Rh_ME;
	double LaneMarkModelDerivA_C3_Rh_ME;
	double Construction_Area_Detected;
	double LDW_System_Availability_Rh_ME;
	double LDW_Warning_Status_Rh_ME;
};

struct front_vision_lane_left {
	double Lh_View_Start_Longitudinal_Dist;
	double Lh_View_End_Longitudinal_Dist;
	double LaneMark_Confidence_Ln_ME;
	double LaneMark_Confidence_Lh_ME; // msg error
	double leftLanePrediction;
	double Lh_Neightbor_Avail;
	double Lh_Neightbor_Type;
	double Lh_Guardrail;
	double Highway_Merge_left;
	double Highway_Exit_left;
	double leftLaneColorInfo;
	double Lh_ViewRange_StartPoint;
	double Lh_Neighbor_LaneMark_Pos_C0;
	double Lh_Neighbor_LaneMark_Model_B_C1;
	double Lh_Neighbor_LaneMark_Model_A_C2;
	double Lh_Neighbor_LaneMark_Model_dA_C3;
	double Classification_Lh_ME;
	double Quality_Lh_ME; // msg error
	double Marker_Width_Lh_ME;
	double LaneMarkPosition_C0_Lh_ME;
	double LaneMarkHeadingAngle_C1_Lh_ME;
	double LaneMarkModelA_C2_Lh_ME;
	double LaneMarkModelDerivA_C3_Lh_ME;
	double Construction_Area_Detected;
	double LDW_System_Availability_Lh_ME;
	double LDW_Warning_Status_Lh_ME;
};

struct front_radar_track {
	double Track_Angle;
	double Track_Range;
	double Track_Range_Accel;
	double Track_Range_Rate;
	double Track_Status;
	double Track_Width;
};
