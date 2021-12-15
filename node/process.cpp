


// unit IN
double in_vehicle_sensor[9];
double front_vision_track[240];
double front_vision_lane[52];
double front_radar_track[192];
// unit OUT, coordinate IN
double in_vehicle_sensor_unit[19];
double front_vision_track_unit[360];
double front_vision_lane_unit[68];
double front_radar_track_unit[544];
// coordinate OUT
double in_vehicle_sensor_coor[19];   // IN : road   motion
double front_vision_track_coor[360]; // IN :        motion
double front_vision_lane_coor[68];   // IN : road            management
double front_radar_track_coor[544];  // IN :        motion
// road OUT
double road_curvature_v;               // IN : motion   management   recognition
double road_slope;                   // IN : motion   management
// motion OUT
double front_vision_track_motion[360];  // IN : gating   shape   
double front_radar_track_motion[544];   // IN : gating           
// gating OUT
double fusion_object[768];           // IN : shape
double old_fusion_object[768];       // IN : shape
double association_map[128];         // IN : shape   tracking   management 
// shape OUT
double fusion_object_shape[768];     // IN :         tracking   management
double shape_id[320];
double old_shape_id[320];            // IN : shape
// tracking OUT
double fusion_track_updated[1280];       // IN : management
double p_fusion_track_updated[1024];     // IN : management
double association_map_updated[128];     // IN : management
// management OUT
double fusion_track_management[1280];         // IN :            recognition
double old_fusion_track_management[1280];     // IN : tracking
double association_map_management[128];       // IN :            recognition
double old_association_map_management[128];   // IN : tracking
double p_fusion_track_management[1024];
double old_p_fusion_track_management[1024];   // IN : tracking

// recognition IN
double fusion_track_in[1280];     // IN : vehicle
double association_map_in[128];   // IN : vehicle
double road_curvature_in;         // IN : vehicle

// vehicle OUT
double fusion_track_recognition[1408];   // IN : pedestrian
double avl[9];
double avr[9];
double rvl[9];
double rvi[9];
double rvr[9];
double fvl[9];
double fvi[9];
double fvr[9];
double rear_object_lane[64];
double old_rear_object_lane[64];
double object_lane_total[64];
double old_object_lane_total[64];
double target_vehicle[72];
// pedestrian OUT
double fusion_track_recognition_pedestrian[1792];
double tmp_fpi[9];
double tmp_fpl[9];
double tmp_fpr[9];
double tmp_fci[9];
double tmp_fcl[9];
double tmp_fcr[9];
double tmp_fei[9];
double tmp_fel[9];
double tmp_fer[9];
double target_pedestrian[27];
double target_cyclist[27];
double target_e_scooter[27];

//
double environmental_sensors[991];
 

PROCESS TRACKING 
{

    // unit_conversion
    unit_conversion(in_vehicle_sensor, front_vision_track, front_vision_lane, front_radar_track,
        in_vehicle_track_unit, front_vision_track_unit, front_vision_lane_unit, front_radar_track_unit);

    // coordinate
    coordinate(in_vehicle_track_unit, front_vision_track_unit, front_vision_lane_unit, front_radar_track_unit,
    in_vehicle_sensor_coor, front_vision_track_coor, front_vision_lane_coor, front_radar_track_coor);


    // road_curvature
    road_curvature(front_vision_lane_coor, in_vehicle_sensor_coor, &road_curvature_v, &road_slope);

    // motion_attribute
    motion_attribute(in_vehicle_sensor_coor, front_vision_track_coor, front_radar_track_coor,
        road_curvature_v, road_slope, front_vision_track_motion, front_radar_track_motion);

    // gating
    gating(front_vision_track_motion, front_radar_track_motion,
        fusion_object, association_map);

    // shape_attribute
    shape_attribute(fusion_object, old_fusion_object, association_map, front_vision_track_motion, old_shape_id,
        fusion_object_shape, shape_id);

    // tracking
    tracking(old_association_map_management, old_fusion_track_management, old_p_fusion_track_management, fusion_object_shape, association_map,
    fusion_track_updated, p_fusion_track_updated, association_map_updated);

    // track_management
    track_management(fusion_track_updated, p_fusion_track_updated, association_map_updated, association_map, fusion_object_shape, road_curvature_v, road_slope, front_vision_lane_coor,
    fusion_track_management, association_map_management, p_fusion_track_management);

    road_curvature_in = road_curvature_v;
    memcpy(association_map_in, association_map_updated, sizeof(association_map_updated));
    


    memcpy(old_fusion_object, fusion_object, sizeof(fusion_object));
    memcpy(old_shape_id, shape_id, sizeof(shape_id));
    memcpy(old_fusion_track_management, fusion_track_management, sizeof(fusion_track_management));
    memcpy(old_association_map_management, association_map_management, sizeof(association_map_management));
    memcpy(old_p_fusion_track_management, p_fusion_track_management, sizeof(p_fusion_track_management));

}

PROCESS RECOGNITION
{
    
    // vehicle_recognition
    vehicle_recognition(fusion_track_in, association_map_in, road_curvature_in, old_rear_object_lane, old_object_lane_total, 
    fusion_track_recognition, avl, avr, rvl, rvi, rvr, fvl, fvi, fvr, rear_object_lane, object_lane_total);
    for (int i=0; i<9; ++i) {
        target_vehicle[8*i] = fvl[i];
        target_vehicle[8*i+1] = fvi[i];
        target_vehicle[8*i+2] = fvr[i];
        target_vehicle[8*i+3] = avl[i];
        target_vehicle[8*i+4] = avr[i];
        target_vehicle[8*i+5] = rvl[i];
        target_vehicle[8*i+6] = rvi[i];
        target_vehicle[8*i+7] = rvr[i];
    }

    // pedestrian_recognition
    pedestrian_recognition(fusion_track_recognition, fusion_track_recognition_pedestrian, 
        tmp_fpi, tmp_fpl, tmp_fpr, tmp_fci, tmp_fcl, tmp_fcr, tmp_fei, tmp_fel, tmp_fer);
    for (int i=0; i<3; ++i) {
        target_pedestrian[3*i] = tmp_fpi[i];
        target_pedestrian[3*i+1] = tmp_fpl[i];
        target_pedestrian[3*i+2] = tmp_fpr[i];
        
        target_cyclist[3*i] = tmp_fci[i];
        target_cyclist[3*i+1] = tmp_fcl[i];
        target_cyclist[3*i+2] = tmp_fcr[i];

        target_e_scooter[3*i] = tmp_fei[i];
        target_e_scooter[3*i+1] = tmp_fel[i];
        target_e_scooter[3*i+2] = tmp_fer[i];
    }

    int tmp_size = 0;
    memcpy(environmental_sensors, in_vehicle_sensor_coor, sizeof(in_vehicle_sensor_coor));
    tmp_size = sizeof(in_vehicle_sensor_coor);
    memcpy(&environmental_sensors[tmp_size], front_vision_track_motion, sizeof(front_vision_track_motion));
    tmp_size += sizeof(front_vision_track_motion);
    memcpy(&environmental_sensors[tmp_size], front_vision_lane_coor, sizeof(front_vision_lane_coor));
    tmp_size += sizeof(front_vision_lane_coor);
    memcpy(&environmental_sensors[tmp_size], front_radar_track_motion, sizeof(front_radar_track_motion));


    // Result
    // - environmental_sensors
    // - fusion_track_recognition_pedestrian
    // - association_map_management
    // - target_vehicle
    // - target_pedestrian
    // - target_cyclist
    // - target_e_scooter

    memcpy(old_rear_object_lane, rear_object_lane, sizeof(rear_object_lane));
    memcpy(old_object_lane_total, object_lane_total, sizeof(object_lane_total));

}





















