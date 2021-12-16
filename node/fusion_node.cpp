#include "fusion_node.h"
#include <thread>
#include <vector>


using namespace std;

void callback_ivs(const chassis_msg::LOG_BYTE0::ConstPtr& byte0, const chassis_msg::LOG_BYTE1::ConstPtr& byte1, const chassis_msg::LOG_BYTE2::ConstPtr& byte2);

void callback_fvt1(const mobileye_avante_msg::Obstacle_Data_1_A::ConstPtr& obstacle_data_1_a, const mobileye_avante_msg::Obstacle_Data_1_B::ConstPtr& obstacle_data_1_b, const mobileye_avante_msg::Obstacle_Data_1_C::ConstPtr& obstacle_data_1_c, const mobileye_avante_msg::Obstacle_Data_2_A::ConstPtr& obstacle_data_2_a, const mobileye_avante_msg::Obstacle_Data_2_B::ConstPtr& obstacle_data_2_b, const mobileye_avante_msg::Obstacle_Data_2_C::ConstPtr& obstacle_data_2_c, const mobileye_avante_msg::Obstacle_Data_3_A::ConstPtr& obstacle_data_3_a, const mobileye_avante_msg::Obstacle_Data_3_B::ConstPtr& obstacle_data_3_b, const mobileye_avante_msg::Obstacle_Data_3_C::ConstPtr& obstacle_data_3_c);
void callback_fvt2(const mobileye_avante_msg::Obstacle_Data_4_A::ConstPtr& obstacle_data_4_a, const mobileye_avante_msg::Obstacle_Data_4_B::ConstPtr& obstacle_data_4_b, const mobileye_avante_msg::Obstacle_Data_4_C::ConstPtr& obstacle_data_4_c, const mobileye_avante_msg::Obstacle_Data_5_A::ConstPtr& obstacle_data_5_a, const mobileye_avante_msg::Obstacle_Data_5_B::ConstPtr& obstacle_data_5_b, const mobileye_avante_msg::Obstacle_Data_5_C::ConstPtr& obstacle_data_5_c, const mobileye_avante_msg::Obstacle_Data_6_A::ConstPtr& obstacle_data_6_a, const mobileye_avante_msg::Obstacle_Data_6_B::ConstPtr& obstacle_data_6_b, const mobileye_avante_msg::Obstacle_Data_6_C::ConstPtr& obstacle_data_6_c);
void callback_fvt3(const mobileye_avante_msg::Obstacle_Data_7_A::ConstPtr& obstacle_data_7_a, const mobileye_avante_msg::Obstacle_Data_7_B::ConstPtr& obstacle_data_7_b, const mobileye_avante_msg::Obstacle_Data_7_C::ConstPtr& obstacle_data_7_c, const mobileye_avante_msg::Obstacle_Data_8_A::ConstPtr& obstacle_data_8_a, const mobileye_avante_msg::Obstacle_Data_8_B::ConstPtr& obstacle_data_8_b, const mobileye_avante_msg::Obstacle_Data_8_C::ConstPtr& obstacle_data_8_c, const mobileye_avante_msg::Obstacle_Data_9_A::ConstPtr& obstacle_data_9_a, const mobileye_avante_msg::Obstacle_Data_9_B::ConstPtr& obstacle_data_9_b, const mobileye_avante_msg::Obstacle_Data_9_C::ConstPtr& obstacle_data_9_c);
void callback_fvt4(const mobileye_avante_msg::Obstacle_Data_10_A::ConstPtr& obstacle_data_10_a, const mobileye_avante_msg::Obstacle_Data_10_B::ConstPtr& obstacle_data_10_b, const mobileye_avante_msg::Obstacle_Data_10_C::ConstPtr& obstacle_data_10_c, const mobileye_avante_msg::Obstacle_Additional_Data_1::ConstPtr& obstacle_additional_data_1);

void callback_fvlr(const mobileye_avante_msg::ME_Lane_Add_info_1::ConstPtr& me_lane_add_info_1, const mobileye_avante_msg::ME_Lane_Additional_Data_1::ConstPtr& me_lane_additional_data_1, const mobileye_avante_msg::ME_Lane_Additional_Data_3::ConstPtr& me_lane_additional_data_3, const mobileye_avante_msg::ME_Right_Lane_A::ConstPtr& me_right_lane_a, const mobileye_avante_msg::ME_Right_Lane_B::ConstPtr& me_right_lane_b);

void callback_fvll(const mobileye_avante_msg::ME_Lane_Add_info_1::ConstPtr& me_lane_add_info_1, const mobileye_avante_msg::ME_Lane_Additional_Data_1::ConstPtr& me_lane_additional_data_1, const mobileye_avante_msg::ME_Lane_Additional_Data_2::ConstPtr& me_lane_additional_data_2, const mobileye_avante_msg::ME_Left_Lane_A::ConstPtr& me_left_lane_a, const mobileye_avante_msg::ME_Left_Lane_B::ConstPtr& me_left_lane_b);

void callback_frt1(const radar_msg::Track1::ConstPtr& track1, const radar_msg::Track2::ConstPtr& track2, const radar_msg::Track3::ConstPtr& track3, const radar_msg::Track4::ConstPtr& track4, const radar_msg::Track5::ConstPtr& track5, const radar_msg::Track6::ConstPtr& track6, const radar_msg::Track7::ConstPtr& track7, const radar_msg::Track8::ConstPtr& track8);
void callback_frt2(const radar_msg::Track9::ConstPtr& track9, const radar_msg::Track10::ConstPtr& track10, const radar_msg::Track11::ConstPtr& track11, const radar_msg::Track12::ConstPtr& track12, const radar_msg::Track13::ConstPtr& track13, const radar_msg::Track14::ConstPtr& track14, const radar_msg::Track15::ConstPtr& track15, const radar_msg::Track16::ConstPtr& track16);
void callback_frt3(const radar_msg::Track17::ConstPtr& track17, const radar_msg::Track18::ConstPtr& track18, const radar_msg::Track19::ConstPtr& track19, const radar_msg::Track20::ConstPtr& track20, const radar_msg::Track21::ConstPtr& track21, const radar_msg::Track22::ConstPtr& track22, const radar_msg::Track23::ConstPtr& track23, const radar_msg::Track24::ConstPtr& track24);
void callback_frt4(const radar_msg::Track25::ConstPtr& track25, const radar_msg::Track26::ConstPtr& track26, const radar_msg::Track27::ConstPtr& track27, const radar_msg::Track28::ConstPtr& track28, const radar_msg::Track29::ConstPtr& track29, const radar_msg::Track30::ConstPtr& track30, const radar_msg::Track31::ConstPtr& track31, const radar_msg::Track32::ConstPtr& track32);

/* ******************* */
/* **** Variables **** */

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

volatile int check_run;

//#define FUSION_MEASURE

#ifdef FUSION_MEASURE
#include <sys/stat.h>
#define MEASUREMENT_CNT 1000
#define THRESHOLD 200
int meas_object[MEASUREMENT_CNT];
int meas_result[MEASUREMENT_CNT];
double meas_cycletime[MEASUREMENT_CNT];
double meas_exetime[MEASUREMENT_CNT];

int meas_cnt;

#define MEAS_PATH "./src/sensor_fusion/measure/"
#define MEAS_FILE "measure.csv"
#endif

void *run_function(void *data)
{
    ros::Publisher track_pub = *((ros::Publisher *)data);
    tracking_msg::Tracking tracking_m;
    tracking_msg::TrackingArray msg;
    
    static clock_t old_time = 0;
    while(1) {
        while(check_run != RUN_THREAD) { 
            std::this_thread::yield();
        }
#ifdef FUSION_MEASURE
        printf("=============== Start Processing #%d ===============\n", meas_cnt);
#else        
        printf("=============== Start Processing ===============\n");
#endif
        check_run = 0;
        clock_t start_run = clock();
        clock_t end_run = 0;

        // unit_conversion
        unit_conversion(in_vehicle_sensor, front_vision_track, front_vision_lane, front_radar_track,
            in_vehicle_sensor_unit, front_vision_track_unit, front_vision_lane_unit, front_radar_track_unit);
    
        // coordinate
        coordinate(in_vehicle_sensor_unit, front_vision_track_unit, front_vision_lane_unit, front_radar_track_unit,
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
        memcpy(association_map_in, association_map_management, sizeof(association_map_updated));
        memcpy(fusion_track_in, fusion_track_management, sizeof(fusion_track_management));

        // Publish
        tracking_m.header.stamp = ros::Time::now();
        for (int i=0;i<64;++i) {
            tracking_m.header.seq = i+1;
            tracking_m.Rel_Pos_Y = fusion_track_management[20*i+13];
            tracking_m.Rel_Pos_X = fusion_track_management[20*i+14];
            tracking_m.Width     = fusion_track_management[20*i+5];
            tracking_m.Length    = fusion_track_management[20*i+6];
//            tracking_m.Height    = fusion_track_management[
            tracking_m.Yaw       = fusion_track_management[20*i+7];
            tracking_m.ID        = fusion_track_management[20*i+8];
            tracking_m.Rel_Vel_Y = fusion_track_management[20*i+15];
            tracking_m.Rel_Vel_X = fusion_track_management[20*i+16];
            tracking_m.Life_Time = fusion_track_management[20*i+19];
//            tracking_m.Class     = fusion_track_management[

            msg.tracks.push_back(tracking_m);
        } 
        track_pub.publish(msg);
        printf(" - Publish Complete\n");
    
        memcpy(old_fusion_object, fusion_object, sizeof(fusion_object));
        memcpy(old_shape_id, shape_id, sizeof(shape_id));
        memcpy(old_fusion_track_management, fusion_track_management, sizeof(fusion_track_management));
        memcpy(old_association_map_management, association_map_management, sizeof(association_map_management));
        memcpy(old_p_fusion_track_management, p_fusion_track_management, sizeof(p_fusion_track_management));


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
/*    
        int tmp_size = 0;
        memcpy(environmental_sensors, in_vehicle_sensor_coor, sizeof(in_vehicle_sensor_coor));
        tmp_size = sizeof(in_vehicle_sensor_coor);
        memcpy(&environmental_sensors[tmp_size], front_vision_track_motion, sizeof(front_vision_track_motion));
        tmp_size += sizeof(front_vision_track_motion);
        memcpy(&environmental_sensors[tmp_size], front_vision_lane_coor, sizeof(front_vision_lane_coor));
        tmp_size += sizeof(front_vision_lane_coor);
        memcpy(&environmental_sensors[tmp_size], front_radar_track_motion, sizeof(front_radar_track_motion));
*/    
    
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


        end_run = clock();
                
#ifdef FUSION_MEASURE
        meas_cnt += 1;
        int tmp_cnt = meas_cnt - THRESHOLD;
        clock_t this_time = clock();
        clock_t cycle_time = this_time - old_time;
        old_time = this_time;

        printf("- Measure Count: %d\n", tmp_cnt);
        if(tmp_cnt>=0&&tmp_cnt<=MEASUREMENT_CNT) {
            meas_exetime[tmp_cnt] = (double)(end_run - start_run)/CLOCKS_PER_SEC;
            meas_cycletime[tmp_cnt] = (double)(cycle_time)/CLOCKS_PER_SEC;
        }
        
        if(tmp_cnt==MEASUREMENT_CNT) {
            int exist = 0;
            FILE *fp;
            char file_name[100] = "";
            
            strcat(file_name, MEAS_PATH);
            strcat(file_name, MEAS_FILE);
    
            fp = fopen(file_name, "w+");
            if(fp==NULL) {
                while(!exist) {
                    int result;
                    result = mkdir(MEAS_PATH, 0766);
                    if(result==0) {
                        exist = 1;
                        fp=fopen(file_name, "w+");
                    }
                }
            }
            fprintf(fp, "%s,%s\n", "Exe", "Cycle");
            for(int i =0;i<tmp_cnt;++i) {
                fprintf(fp, "%lf,%lf\n", meas_exetime[i]*1000, meas_cycletime[i]*1000);
            }
            fclose(fp);
            printf(" AES Measure , Complete\n");
        }
        printf("index: %d-th\n", meas_cnt);
        printf(" -     Cycle Time : %lf\n", (double)cycle_time/CLOCKS_PER_SEC);
#endif
        clock_t exe_time = end_run - start_run;
        printf(" - Execution Time : %lf\n", (double)exe_time/CLOCKS_PER_SEC);
        printf("================ End Processing ================\n\n\n");

    }
}



int main(int argc, char** argv) {
	cout << "[Sensor_Fusion]: Start node" << endl;

    pthread_t run_thread;

	ros::init(argc, argv, "sensor_fusion_node");
	ros::NodeHandle nh("");


    // Publish
    ros::Publisher track_pub = nh.advertise<tracking_msg::TrackingArray>("TrackingArray", 1);

	// In Vehicle Sensor
	message_filters::Subscriber<chassis_msg::LOG_BYTE0> byte0_sub(nh, "LOG_BYTE0", 1);
	message_filters::Subscriber<chassis_msg::LOG_BYTE1> byte1_sub(nh, "LOG_BYTE1", 1);
	message_filters::Subscriber<chassis_msg::LOG_BYTE2> byte2_sub(nh, "LOG_BYTE2", 1);

	typedef message_filters::sync_policies::ApproximateTime<chassis_msg::LOG_BYTE0, chassis_msg::LOG_BYTE1, chassis_msg::LOG_BYTE2> ivsPolicy;
	message_filters::Synchronizer<ivsPolicy> ivsSync(ivsPolicy(10), byte0_sub, byte1_sub, byte2_sub);

	ivsSync.registerCallback(boost::bind(&callback_ivs, _1, _2, _3));

	// Front Vision Track
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_1_A> obstacle_data_1a_sub(nh, "Obstacle_Data_1_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_1_B> obstacle_data_1b_sub(nh, "Obstacle_Data_1_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_1_C> obstacle_data_1c_sub(nh, "Obstacle_Data_1_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_2_A> obstacle_data_2a_sub(nh, "Obstacle_Data_2_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_2_B> obstacle_data_2b_sub(nh, "Obstacle_Data_2_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_2_C> obstacle_data_2c_sub(nh, "Obstacle_Data_2_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_3_A> obstacle_data_3a_sub(nh, "Obstacle_Data_3_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_3_B> obstacle_data_3b_sub(nh, "Obstacle_Data_3_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_3_C> obstacle_data_3c_sub(nh, "Obstacle_Data_3_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_4_A> obstacle_data_4a_sub(nh, "Obstacle_Data_4_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_4_B> obstacle_data_4b_sub(nh, "Obstacle_Data_4_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_4_C> obstacle_data_4c_sub(nh, "Obstacle_Data_4_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_5_A> obstacle_data_5a_sub(nh, "Obstacle_Data_5_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_5_B> obstacle_data_5b_sub(nh, "Obstacle_Data_5_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_5_C> obstacle_data_5c_sub(nh, "Obstacle_Data_5_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_6_A> obstacle_data_6a_sub(nh, "Obstacle_Data_6_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_6_B> obstacle_data_6b_sub(nh, "Obstacle_Data_6_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_6_C> obstacle_data_6c_sub(nh, "Obstacle_Data_6_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_7_A> obstacle_data_7a_sub(nh, "Obstacle_Data_7_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_7_B> obstacle_data_7b_sub(nh, "Obstacle_Data_7_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_7_C> obstacle_data_7c_sub(nh, "Obstacle_Data_7_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_8_A> obstacle_data_8a_sub(nh, "Obstacle_Data_8_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_8_B> obstacle_data_8b_sub(nh, "Obstacle_Data_8_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_8_C> obstacle_data_8c_sub(nh, "Obstacle_Data_8_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_9_A> obstacle_data_9a_sub(nh, "Obstacle_Data_9_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_9_B> obstacle_data_9b_sub(nh, "Obstacle_Data_9_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_9_C> obstacle_data_9c_sub(nh, "Obstacle_Data_9_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_10_A> obstacle_data_10a_sub(nh, "Obstacle_Data_10_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_10_B> obstacle_data_10b_sub(nh, "Obstacle_Data_10_B", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Data_10_C> obstacle_data_10c_sub(nh, "Obstacle_Data_10_C", 1);
	message_filters::Subscriber<mobileye_avante_msg::Obstacle_Additional_Data_1> obstacle_additional_data_1_sub(nh, "Obstacle_Additional_Data_1", 1);
	
	typedef message_filters::sync_policies::ApproximateTime<mobileye_avante_msg::Obstacle_Data_1_A, mobileye_avante_msg::Obstacle_Data_1_B, mobileye_avante_msg::Obstacle_Data_1_C, mobileye_avante_msg::Obstacle_Data_2_A, mobileye_avante_msg::Obstacle_Data_2_B, mobileye_avante_msg::Obstacle_Data_2_C, mobileye_avante_msg::Obstacle_Data_3_A, mobileye_avante_msg::Obstacle_Data_3_B, mobileye_avante_msg::Obstacle_Data_3_C> fvt1Policy;
	typedef message_filters::sync_policies::ApproximateTime<mobileye_avante_msg::Obstacle_Data_4_A, mobileye_avante_msg::Obstacle_Data_4_B, mobileye_avante_msg::Obstacle_Data_4_C, mobileye_avante_msg::Obstacle_Data_5_A, mobileye_avante_msg::Obstacle_Data_5_B, mobileye_avante_msg::Obstacle_Data_5_C, mobileye_avante_msg::Obstacle_Data_6_A, mobileye_avante_msg::Obstacle_Data_6_B, mobileye_avante_msg::Obstacle_Data_6_C> fvt2Policy;
	typedef message_filters::sync_policies::ApproximateTime<mobileye_avante_msg::Obstacle_Data_7_A, mobileye_avante_msg::Obstacle_Data_7_B, mobileye_avante_msg::Obstacle_Data_7_C, mobileye_avante_msg::Obstacle_Data_8_A, mobileye_avante_msg::Obstacle_Data_8_B, mobileye_avante_msg::Obstacle_Data_8_C, mobileye_avante_msg::Obstacle_Data_9_A, mobileye_avante_msg::Obstacle_Data_9_B, mobileye_avante_msg::Obstacle_Data_9_C> fvt3Policy;
	typedef message_filters::sync_policies::ApproximateTime<mobileye_avante_msg::Obstacle_Data_10_A, mobileye_avante_msg::Obstacle_Data_10_B, mobileye_avante_msg::Obstacle_Data_10_C, mobileye_avante_msg::Obstacle_Additional_Data_1> fvt4Policy;

	message_filters::Synchronizer<fvt1Policy> fvt1Sync(fvt1Policy(10), obstacle_data_1a_sub, obstacle_data_1b_sub, obstacle_data_1c_sub, obstacle_data_2a_sub, obstacle_data_2b_sub, obstacle_data_2c_sub, obstacle_data_3a_sub, obstacle_data_3b_sub, obstacle_data_3c_sub);
	message_filters::Synchronizer<fvt2Policy> fvt2Sync(fvt2Policy(10), obstacle_data_4a_sub, obstacle_data_4b_sub, obstacle_data_4c_sub, obstacle_data_5a_sub, obstacle_data_5b_sub, obstacle_data_5c_sub, obstacle_data_6a_sub, obstacle_data_6b_sub, obstacle_data_6c_sub); 
	message_filters::Synchronizer<fvt3Policy> fvt3Sync(fvt3Policy(10), obstacle_data_7a_sub, obstacle_data_7b_sub, obstacle_data_7c_sub, obstacle_data_8a_sub, obstacle_data_8b_sub, obstacle_data_8c_sub, obstacle_data_9a_sub, obstacle_data_9b_sub, obstacle_data_9c_sub); 
	message_filters::Synchronizer<fvt4Policy> fvt4Sync(fvt4Policy(10), obstacle_data_10a_sub, obstacle_data_10b_sub, obstacle_data_10c_sub, obstacle_additional_data_1_sub); 

	fvt1Sync.registerCallback(boost::bind(&callback_fvt1, _1, _2, _3, _4, _5, _6, _7, _8, _9));
	fvt2Sync.registerCallback(boost::bind(&callback_fvt2, _1, _2, _3, _4, _5, _6, _7, _8, _9));
	fvt3Sync.registerCallback(boost::bind(&callback_fvt3, _1, _2, _3, _4, _5, _6, _7, _8, _9));
	fvt4Sync.registerCallback(boost::bind(&callback_fvt4, _1, _2, _3, _4));

	// Front Vision Lane Right
	message_filters::Subscriber<mobileye_avante_msg::ME_Lane_Add_info_1> me_lane_add_info_1_sub(nh, "ME_Lane_Add_info_1", 1);
	message_filters::Subscriber<mobileye_avante_msg::ME_Lane_Additional_Data_1> me_lane_additional_data_1_sub(nh, "ME_Lane_Additional_Data_1", 1);
	message_filters::Subscriber<mobileye_avante_msg::ME_Lane_Additional_Data_3> me_lane_additional_data_3_sub(nh, "ME_Lane_Additional_Data_3", 1);
	message_filters::Subscriber<mobileye_avante_msg::ME_Right_Lane_A> me_right_lane_a_sub(nh, "ME_Right_Lane_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::ME_Right_Lane_B> me_right_lane_b_sub(nh, "ME_Right_Lane_B", 1);
	
	typedef message_filters::sync_policies::ApproximateTime<mobileye_avante_msg::ME_Lane_Add_info_1, mobileye_avante_msg::ME_Lane_Additional_Data_1, mobileye_avante_msg::ME_Lane_Additional_Data_3, mobileye_avante_msg::ME_Right_Lane_A, mobileye_avante_msg::ME_Right_Lane_B> fvlrPolicy;
	message_filters::Synchronizer<fvlrPolicy> fvlrSync(fvlrPolicy(10), me_lane_add_info_1_sub, me_lane_additional_data_1_sub, me_lane_additional_data_3_sub, me_right_lane_a_sub, me_right_lane_b_sub);

	fvlrSync.registerCallback(boost::bind(&callback_fvlr, _1, _2, _3, _4, _5));

	// Front Vision Lane Left
	//message_filters::Subscriber<mobileye_avante_msg::ME_Lane_Add_info_1> me_lane_add_info_1_sub(nh, "ME_Lane_Add_info_1", 1);
	//message_filters::Subscriber<mobileye_avante_msg::ME_Lane_Additional_Data_1> me_lane_additional_data_1_sub(nh, "ME_Lane_Additional_Data_1", 1);
	message_filters::Subscriber<mobileye_avante_msg::ME_Lane_Additional_Data_2> me_lane_additional_data_2_sub(nh, "ME_Lane_Additional_Data_2", 1);
	message_filters::Subscriber<mobileye_avante_msg::ME_Left_Lane_A> me_left_lane_a_sub(nh, "ME_Left_Lane_A", 1);
	message_filters::Subscriber<mobileye_avante_msg::ME_Left_Lane_B> me_left_lane_b_sub(nh, "ME_Left_Lane_B", 1);
	
	typedef message_filters::sync_policies::ApproximateTime<mobileye_avante_msg::ME_Lane_Add_info_1, mobileye_avante_msg::ME_Lane_Additional_Data_1, mobileye_avante_msg::ME_Lane_Additional_Data_2, mobileye_avante_msg::ME_Left_Lane_A, mobileye_avante_msg::ME_Left_Lane_B> fvllPolicy;
	message_filters::Synchronizer<fvllPolicy> fvllSync(fvllPolicy(10), me_lane_add_info_1_sub, me_lane_additional_data_1_sub, me_lane_additional_data_2_sub, me_left_lane_a_sub, me_left_lane_b_sub);

	fvllSync.registerCallback(boost::bind(&callback_fvll, _1, _2, _3, _4, _5));

	// Front Radar Track
	message_filters::Subscriber<radar_msg::Track1> track1_sub(nh, "Track1", 1);
	message_filters::Subscriber<radar_msg::Track2> track2_sub(nh, "Track2", 1);
	message_filters::Subscriber<radar_msg::Track3> track3_sub(nh, "Track3", 1);
	message_filters::Subscriber<radar_msg::Track4> track4_sub(nh, "Track4", 1);
	message_filters::Subscriber<radar_msg::Track5> track5_sub(nh, "Track5", 1);
	message_filters::Subscriber<radar_msg::Track6> track6_sub(nh, "Track6", 1);
	message_filters::Subscriber<radar_msg::Track7> track7_sub(nh, "Track7", 1);
	message_filters::Subscriber<radar_msg::Track8> track8_sub(nh, "Track8", 1);
	message_filters::Subscriber<radar_msg::Track9> track9_sub(nh, "Track9", 1);
	message_filters::Subscriber<radar_msg::Track10> track10_sub(nh, "Track10", 1);
	message_filters::Subscriber<radar_msg::Track11> track11_sub(nh, "Track11", 1);
	message_filters::Subscriber<radar_msg::Track12> track12_sub(nh, "Track12", 1);
	message_filters::Subscriber<radar_msg::Track13> track13_sub(nh, "Track13", 1);
	message_filters::Subscriber<radar_msg::Track14> track14_sub(nh, "Track14", 1);
	message_filters::Subscriber<radar_msg::Track15> track15_sub(nh, "Track15", 1);
	message_filters::Subscriber<radar_msg::Track16> track16_sub(nh, "Track16", 1);
	message_filters::Subscriber<radar_msg::Track17> track17_sub(nh, "Track17", 1);
	message_filters::Subscriber<radar_msg::Track18> track18_sub(nh, "Track18", 1);
	message_filters::Subscriber<radar_msg::Track19> track19_sub(nh, "Track19", 1);
	message_filters::Subscriber<radar_msg::Track20> track20_sub(nh, "Track20", 1);
	message_filters::Subscriber<radar_msg::Track21> track21_sub(nh, "Track21", 1);
	message_filters::Subscriber<radar_msg::Track22> track22_sub(nh, "Track22", 1);
	message_filters::Subscriber<radar_msg::Track23> track23_sub(nh, "Track23", 1);
	message_filters::Subscriber<radar_msg::Track24> track24_sub(nh, "Track24", 1);
	message_filters::Subscriber<radar_msg::Track25> track25_sub(nh, "Track25", 1);
	message_filters::Subscriber<radar_msg::Track26> track26_sub(nh, "Track26", 1);
	message_filters::Subscriber<radar_msg::Track27> track27_sub(nh, "Track27", 1);
	message_filters::Subscriber<radar_msg::Track28> track28_sub(nh, "Track28", 1);
	message_filters::Subscriber<radar_msg::Track29> track29_sub(nh, "Track29", 1);
	message_filters::Subscriber<radar_msg::Track30> track30_sub(nh, "Track30", 1);
	message_filters::Subscriber<radar_msg::Track31> track31_sub(nh, "Track31", 1);
	message_filters::Subscriber<radar_msg::Track32> track32_sub(nh, "Track32", 1);

	typedef message_filters::sync_policies::ApproximateTime<radar_msg::Track1, radar_msg::Track2, radar_msg::Track3, radar_msg::Track4, radar_msg::Track5, radar_msg::Track6, radar_msg::Track7, radar_msg::Track8> frt1Policy;
	typedef message_filters::sync_policies::ApproximateTime<radar_msg::Track9, radar_msg::Track10, radar_msg::Track11, radar_msg::Track12, radar_msg::Track13, radar_msg::Track14, radar_msg::Track15, radar_msg::Track16> frt2Policy;
	typedef message_filters::sync_policies::ApproximateTime<radar_msg::Track17, radar_msg::Track18, radar_msg::Track19, radar_msg::Track20, radar_msg::Track21, radar_msg::Track22, radar_msg::Track23, radar_msg::Track24> frt3Policy;
	typedef message_filters::sync_policies::ApproximateTime<radar_msg::Track25, radar_msg::Track26, radar_msg::Track27, radar_msg::Track28, radar_msg::Track29, radar_msg::Track30, radar_msg::Track31, radar_msg::Track32> frt4Policy;

	message_filters::Synchronizer<frt1Policy> frt1Sync(frt1Policy(10), track1_sub, track2_sub, track3_sub, track4_sub, track5_sub, track6_sub, track7_sub, track8_sub); 
	message_filters::Synchronizer<frt2Policy> frt2Sync(frt2Policy(10), track9_sub, track10_sub, track11_sub, track12_sub, track13_sub, track14_sub, track15_sub, track16_sub); 
	message_filters::Synchronizer<frt3Policy> frt3Sync(frt3Policy(10), track17_sub, track18_sub, track19_sub, track20_sub, track21_sub, track22_sub, track23_sub, track24_sub); 
	message_filters::Synchronizer<frt4Policy> frt4Sync(frt4Policy(10), track25_sub, track26_sub, track27_sub, track28_sub, track29_sub, track30_sub, track31_sub, track32_sub); 

	frt1Sync.registerCallback(boost::bind(&callback_frt1, _1, _2, _3, _4, _5, _6, _7, _8));
	frt2Sync.registerCallback(boost::bind(&callback_frt2, _1, _2, _3, _4, _5, _6, _7, _8));
	frt3Sync.registerCallback(boost::bind(&callback_frt3, _1, _2, _3, _4, _5, _6, _7, _8));
	frt4Sync.registerCallback(boost::bind(&callback_frt4, _1, _2, _3, _4, _5, _6, _7, _8));

    int thr_id = pthread_create(&run_thread, NULL, run_function, (void *)&track_pub);

	ros::spin();

	cout << "[Sensor_Fusion]: End node" << endl;

	return 0;
}


void callback_ivs(const chassis_msg::LOG_BYTE0::ConstPtr& byte0, const chassis_msg::LOG_BYTE1::ConstPtr& byte1, const chassis_msg::LOG_BYTE2::ConstPtr& byte2) {
    in_vehicle_sensor[0] = byte1->LAT_ACCEL;
    in_vehicle_sensor[1] = byte1->LONG_ACCEL;
    in_vehicle_sensor[2] = byte2->SAS_Angle;
    in_vehicle_sensor[3] = byte2->SAS_Speed;
    in_vehicle_sensor[4] = byte0->WHL_SPD_FL;
    in_vehicle_sensor[5] = byte0->WHL_SPD_FR;
    in_vehicle_sensor[6] = byte0->WHL_SPD_RL;
    in_vehicle_sensor[7] = byte0->WHL_SPD_RR;
    in_vehicle_sensor[8] = byte1->YAW_RATE;

    check_run |= IVS;

}

void callback_fvt1(const mobileye_avante_msg::Obstacle_Data_1_A::ConstPtr& d1_a, const mobileye_avante_msg::Obstacle_Data_1_B::ConstPtr& d1_b, const mobileye_avante_msg::Obstacle_Data_1_C::ConstPtr& d1_c, const mobileye_avante_msg::Obstacle_Data_2_A::ConstPtr& d2_a, const mobileye_avante_msg::Obstacle_Data_2_B::ConstPtr& d2_b, const mobileye_avante_msg::Obstacle_Data_2_C::ConstPtr& d2_c, const mobileye_avante_msg::Obstacle_Data_3_A::ConstPtr& d3_a, const mobileye_avante_msg::Obstacle_Data_3_B::ConstPtr& d3_b, const mobileye_avante_msg::Obstacle_Data_3_C::ConstPtr& d3_c) {

    front_vision_track[0] = d1_a->Object_Class; 
    front_vision_track[1] = d1_a->Longitudinal_Distance; 
    front_vision_track[2] = d1_a->Motion_Category; 
    front_vision_track[3] = d1_a->Lateral_Distance; 
    front_vision_track[4] = d1_a->Absolute_Long_Velocity; 
    front_vision_track[5] = d1_a->Absolute_Lateral_Velocity; 
    front_vision_track[6] = d1_a->ID; 

    front_vision_track[7] = d1_b->Predicted_Object; 
    front_vision_track[8] = d1_b->Angle_Right; 
    front_vision_track[9] = d1_b->Motion_Orientation; 
    front_vision_track[10] = d1_b->Angle_Rate_Mean; 
    front_vision_track[11] = d1_b->Absolute_Long_Acc; 

    front_vision_track[12] = d1_c->Lane_Assignment; 
    front_vision_track[13] = d1_c->Length; 
    front_vision_track[14] = d1_c->Brake_Light; 
    front_vision_track[15] = d1_c->Width; 
    front_vision_track[16] = d1_c->AliveCounter; 
    front_vision_track[17] = d1_c->Turn_Indicator_Left; 
    front_vision_track[18] = d1_c->Turn_Indicator_Right; 
    front_vision_track[19] = d1_c->Obstacle_Heading; 
    
    
    front_vision_track[24] = d2_a->Object_Class; 
    front_vision_track[25] = d2_a->Longitudinal_Distance; 
    front_vision_track[26] = d2_a->Motion_Category; 
    front_vision_track[27] = d2_a->Lateral_Distance; 
    front_vision_track[28] = d2_a->Absolute_Long_Velocity; 
    front_vision_track[29] = d2_a->Absolute_Lateral_Velocity; 
    front_vision_track[30] = d2_a->ID; 

    front_vision_track[31] = d2_b->Predicted_Object; 
    front_vision_track[32] = d2_b->Angle_Right; 
    front_vision_track[33] = d2_b->Motion_Orientation; 
    front_vision_track[34] = d2_b->Angle_Rate_Mean; 
    front_vision_track[35] = d2_b->Absolute_Long_Acc; 

    front_vision_track[36] = d2_c->Lane_Assignment; 
    front_vision_track[37] = d2_c->Length; 
    front_vision_track[38] = d2_c->Brake_Light; 
    front_vision_track[39] = d2_c->Width; 
    front_vision_track[40] = d2_c->AliveCounter; 
    front_vision_track[41] = d2_c->Turn_Indicator_Left; 
    front_vision_track[42] = d2_c->Turn_Indicator_Right; 
    front_vision_track[43] = d2_c->Obstacle_Heading; 
    
    
    front_vision_track[48] = d3_a->Object_Class; 
    front_vision_track[49] = d3_a->Longitudinal_Distance; 
    front_vision_track[50] = d3_a->Motion_Category; 
    front_vision_track[51] = d3_a->Lateral_Distance; 
    front_vision_track[52] = d3_a->Absolute_Long_Velocity; 
    front_vision_track[53] = d3_a->Absolute_Lateral_Velocity; 
    front_vision_track[54] = d3_a->ID; 

    front_vision_track[55] = d3_b->Predicted_Object; 
    front_vision_track[56] = d3_b->Angle_Right; 
    front_vision_track[57] = d3_b->Motion_Orientation; 
    front_vision_track[58] = d3_b->Angle_Rate_Mean; 
    front_vision_track[59] = d3_b->Absolute_Long_Acc; 

    front_vision_track[60] = d3_c->Lane_Assignment; 
    front_vision_track[61] = d3_c->Length; 
    front_vision_track[62] = d3_c->Brake_Light; 
    front_vision_track[63] = d3_c->Width; 
    front_vision_track[64] = d3_c->AliveCounter; 
    front_vision_track[65] = d3_c->Turn_Indicator_Left; 
    front_vision_track[66] = d3_c->Turn_Indicator_Right; 
    front_vision_track[67] = d3_c->Obstacle_Heading; 

    check_run |= FVT1;

}

void callback_fvt2(const mobileye_avante_msg::Obstacle_Data_4_A::ConstPtr& d4_a, const mobileye_avante_msg::Obstacle_Data_4_B::ConstPtr& d4_b, const mobileye_avante_msg::Obstacle_Data_4_C::ConstPtr& d4_c, const mobileye_avante_msg::Obstacle_Data_5_A::ConstPtr& d5_a, const mobileye_avante_msg::Obstacle_Data_5_B::ConstPtr& d5_b, const mobileye_avante_msg::Obstacle_Data_5_C::ConstPtr& d5_c, const mobileye_avante_msg::Obstacle_Data_6_A::ConstPtr& d6_a, const mobileye_avante_msg::Obstacle_Data_6_B::ConstPtr& d6_b, const mobileye_avante_msg::Obstacle_Data_6_C::ConstPtr& d6_c) {

    front_vision_track[72] = d4_a->Object_Class; 
    front_vision_track[73] = d4_a->Longitudinal_Distance; 
    front_vision_track[74] = d4_a->Motion_Category; 
    front_vision_track[75] = d4_a->Lateral_Distance; 
    front_vision_track[76] = d4_a->Absolute_Long_Velocity; 
    front_vision_track[77] = d4_a->Absolute_Lateral_Velocity; 
    front_vision_track[78] = d4_a->ID; 

    front_vision_track[79] = d4_b->Predicted_Object; 
    front_vision_track[80] = d4_b->Angle_Right; 
    front_vision_track[81] = d4_b->Motion_Orientation; 
    front_vision_track[82] = d4_b->Angle_Rate_Mean; 
    front_vision_track[83] = d4_b->Absolute_Long_Acc; 

    front_vision_track[84] = d4_c->Lane_Assignment; 
    front_vision_track[85] = d4_c->Length; 
    front_vision_track[86] = d4_c->Brake_Light; 
    front_vision_track[87] = d4_c->Width; 
    front_vision_track[88] = d4_c->AliveCounter; 
    front_vision_track[89] = d4_c->Turn_Indicator_Left; 
    front_vision_track[90] = d4_c->Turn_Indicator_Right; 
    front_vision_track[91] = d4_c->Obstacle_Heading; 


    front_vision_track[96] = d5_a->Object_Class; 
    front_vision_track[97] = d5_a->Longitudinal_Distance; 
    front_vision_track[98] = d5_a->Motion_Category; 
    front_vision_track[99] = d5_a->Lateral_Distance; 
    front_vision_track[100] = d5_a->Absolute_Long_Velocity; 
    front_vision_track[101] = d5_a->Absolute_Lateral_Velocity; 
    front_vision_track[102] = d5_a->ID; 

    front_vision_track[103] = d5_b->Predicted_Object; 
    front_vision_track[104] = d5_b->Angle_Right; 
    front_vision_track[105] = d5_b->Motion_Orientation; 
    front_vision_track[106] = d5_b->Angle_Rate_Mean; 
    front_vision_track[107] = d5_b->Absolute_Long_Acc; 

    front_vision_track[108] = d5_c->Lane_Assignment; 
    front_vision_track[109] = d5_c->Length; 
    front_vision_track[110] = d5_c->Brake_Light; 
    front_vision_track[111] = d5_c->Width; 
    front_vision_track[112] = d5_c->AliveCounter; 
    front_vision_track[113] = d5_c->Turn_Indicator_Left; 
    front_vision_track[114] = d5_c->Turn_Indicator_Right; 
    front_vision_track[115] = d5_c->Obstacle_Heading; 


    front_vision_track[120] = d6_a->Object_Class; 
    front_vision_track[121] = d6_a->Longitudinal_Distance; 
    front_vision_track[122] = d6_a->Motion_Category; 
    front_vision_track[123] = d6_a->Lateral_Distance; 
    front_vision_track[124] = d6_a->Absolute_Long_Velocity; 
    front_vision_track[125] = d6_a->Absolute_Lateral_Velocity; 
    front_vision_track[126] = d6_a->ID; 

    front_vision_track[127] = d6_b->Predicted_Object; 
    front_vision_track[128] = d6_b->Angle_Right; 
    front_vision_track[129] = d6_b->Motion_Orientation; 
    front_vision_track[120] = d6_b->Angle_Rate_Mean; 
    front_vision_track[131] = d6_b->Absolute_Long_Acc; 

    front_vision_track[132] = d6_c->Lane_Assignment; 
    front_vision_track[133] = d6_c->Length; 
    front_vision_track[134] = d6_c->Brake_Light; 
    front_vision_track[135] = d6_c->Width; 
    front_vision_track[136] = d6_c->AliveCounter; 
    front_vision_track[137] = d6_c->Turn_Indicator_Left; 
    front_vision_track[138] = d6_c->Turn_Indicator_Right; 
    front_vision_track[139] = d6_c->Obstacle_Heading; 

    check_run |= FVT2;
}

void callback_fvt3(const mobileye_avante_msg::Obstacle_Data_7_A::ConstPtr& d7_a, const mobileye_avante_msg::Obstacle_Data_7_B::ConstPtr& d7_b, const mobileye_avante_msg::Obstacle_Data_7_C::ConstPtr& d7_c, const mobileye_avante_msg::Obstacle_Data_8_A::ConstPtr& d8_a, const mobileye_avante_msg::Obstacle_Data_8_B::ConstPtr& d8_b, const mobileye_avante_msg::Obstacle_Data_8_C::ConstPtr& d8_c, const mobileye_avante_msg::Obstacle_Data_9_A::ConstPtr& d9_a, const mobileye_avante_msg::Obstacle_Data_9_B::ConstPtr& d9_b, const mobileye_avante_msg::Obstacle_Data_9_C::ConstPtr& d9_c) {

    front_vision_track[144] = d7_a->Object_Class; 
    front_vision_track[145] = d7_a->Longitudinal_Distance; 
    front_vision_track[146] = d7_a->Motion_Category; 
    front_vision_track[147] = d7_a->Lateral_Distance; 
    front_vision_track[148] = d7_a->Absolute_Long_Velocity; 
    front_vision_track[149] = d7_a->Absolute_Lateral_Velocity; 
    front_vision_track[150] = d7_a->ID; 

    front_vision_track[151] = d7_b->Predicted_Object; 
    front_vision_track[152] = d7_b->Angle_Right; 
    front_vision_track[153] = d7_b->Motion_Orientation; 
    front_vision_track[154] = d7_b->Angle_Rate_Mean; 
    front_vision_track[155] = d7_b->Absolute_Long_Acc; 

    front_vision_track[156] = d7_c->Lane_Assignment; 
    front_vision_track[157] = d7_c->Length; 
    front_vision_track[158] = d7_c->Brake_Light; 
    front_vision_track[159] = d7_c->Width; 
    front_vision_track[160] = d7_c->AliveCounter; 
    front_vision_track[161] = d7_c->Turn_Indicator_Left; 
    front_vision_track[162] = d7_c->Turn_Indicator_Right; 
    front_vision_track[163] = d7_c->Obstacle_Heading; 


    front_vision_track[168] = d8_a->Object_Class; 
    front_vision_track[169] = d8_a->Longitudinal_Distance; 
    front_vision_track[170] = d8_a->Motion_Category; 
    front_vision_track[171] = d8_a->Lateral_Distance; 
    front_vision_track[172] = d8_a->Absolute_Long_Velocity; 
    front_vision_track[173] = d8_a->Absolute_Lateral_Velocity; 
    front_vision_track[174] = d8_a->ID; 

    front_vision_track[175] = d8_b->Predicted_Object; 
    front_vision_track[176] = d8_b->Angle_Right; 
    front_vision_track[177] = d8_b->Motion_Orientation; 
    front_vision_track[178] = d8_b->Angle_Rate_Mean; 
    front_vision_track[179] = d8_b->Absolute_Long_Acc; 

    front_vision_track[180] = d8_c->Lane_Assignment; 
    front_vision_track[181] = d8_c->Length; 
    front_vision_track[182] = d8_c->Brake_Light; 
    front_vision_track[183] = d8_c->Width; 
    front_vision_track[184] = d8_c->AliveCounter; 
    front_vision_track[185] = d8_c->Turn_Indicator_Left; 
    front_vision_track[186] = d8_c->Turn_Indicator_Right; 
    front_vision_track[187] = d8_c->Obstacle_Heading; 


    front_vision_track[192] = d9_a->Object_Class; 
    front_vision_track[193] = d9_a->Longitudinal_Distance; 
    front_vision_track[194] = d9_a->Motion_Category; 
    front_vision_track[195] = d9_a->Lateral_Distance; 
    front_vision_track[196] = d9_a->Absolute_Long_Velocity; 
    front_vision_track[197] = d9_a->Absolute_Lateral_Velocity; 
    front_vision_track[198] = d9_a->ID; 

    front_vision_track[199] = d9_b->Predicted_Object; 
    front_vision_track[200] = d9_b->Angle_Right; 
    front_vision_track[201] = d9_b->Motion_Orientation; 
    front_vision_track[202] = d9_b->Angle_Rate_Mean; 
    front_vision_track[203] = d9_b->Absolute_Long_Acc; 

    front_vision_track[204] = d9_c->Lane_Assignment; 
    front_vision_track[205] = d9_c->Length; 
    front_vision_track[206] = d9_c->Brake_Light; 
    front_vision_track[207] = d9_c->Width; 
    front_vision_track[208] = d9_c->AliveCounter; 
    front_vision_track[209] = d9_c->Turn_Indicator_Left; 
    front_vision_track[210] = d9_c->Turn_Indicator_Right; 
    front_vision_track[211] = d9_c->Obstacle_Heading; 

    check_run |= FVT3;
}

void callback_fvt4(const mobileye_avante_msg::Obstacle_Data_10_A::ConstPtr& d10_a, const mobileye_avante_msg::Obstacle_Data_10_B::ConstPtr& d10_b, const mobileye_avante_msg::Obstacle_Data_10_C::ConstPtr& d10_c, const mobileye_avante_msg::Obstacle_Additional_Data_1::ConstPtr& ad_1) {

    front_vision_track[216] = d10_a->Object_Class; 
    front_vision_track[217] = d10_a->Longitudinal_Distance; 
    front_vision_track[218] = d10_a->Motion_Category; 
    front_vision_track[219] = d10_a->Lateral_Distance; 
    front_vision_track[220] = d10_a->Absolute_Long_Velocity; 
    front_vision_track[221] = d10_a->Absolute_Lateral_Velocity; 
    front_vision_track[222] = d10_a->ID; 

    front_vision_track[223] = d10_b->Predicted_Object; 
    front_vision_track[224] = d10_b->Angle_Right; 
    front_vision_track[225] = d10_b->Motion_Orientation; 
    front_vision_track[226] = d10_b->Angle_Rate_Mean; 
    front_vision_track[227] = d10_b->Absolute_Long_Acc; 

    front_vision_track[228] = d10_c->Lane_Assignment; 
    front_vision_track[229] = d10_c->Length; 
    front_vision_track[230] = d10_c->Brake_Light; 
    front_vision_track[231] = d10_c->Width; 
    front_vision_track[232] = d10_c->AliveCounter; 
    front_vision_track[233] = d10_c->Turn_Indicator_Left; 
    front_vision_track[234] = d10_c->Turn_Indicator_Right; 
    front_vision_track[235] = d10_c->Obstacle_Heading; 

    for (int i=1; i<=10; ++i) {
        front_vision_track[24*i-4] = ad_1->Obstacle_Height_1;
        front_vision_track[24*i-3] = ad_1->Obstacle_Side_1;
        front_vision_track[24*i-2] = ad_1->Obstacle_Height_2;
        front_vision_track[24*i-1] = ad_1->Obstacle_Side_2;
    }

    check_run |= FVT4;

}

void callback_fvlr(const mobileye_avante_msg::ME_Lane_Add_info_1::ConstPtr& me_i1, const mobileye_avante_msg::ME_Lane_Additional_Data_1::ConstPtr& me_a1, const mobileye_avante_msg::ME_Lane_Additional_Data_3::ConstPtr& me_a3, const mobileye_avante_msg::ME_Right_Lane_A::ConstPtr& me_ra, const mobileye_avante_msg::ME_Right_Lane_B::ConstPtr& me_rb) {

    front_vision_lane[0] = me_i1->Rh_View_Start_Longitudinal_Dist;
    front_vision_lane[1] = me_i1->Rh_View_End_Longitudinal_Dist;
    front_vision_lane[2] = me_i1->LaneMark_Confidence_Rn_ME;
    front_vision_lane[3] = me_i1->LaneMark_Confidence_Rn_ME;
    front_vision_lane[4] = me_i1->RightLanePrediction;

    front_vision_lane[5] = me_a1->Rh_Neightbor_Avail;
    front_vision_lane[6] = me_a1->Rh_Neightbor_Type;
    front_vision_lane[7] = me_a1->Rh_Guardrail;
    front_vision_lane[8] = me_a1->Highway_Merge_Right;
    front_vision_lane[9] = me_a1->Highway_Exit_Right;
    front_vision_lane[10] = me_a1->RightLaneColorInfo;
    front_vision_lane[11] = me_a1->Rh_ViewRange_StartPoint;

    front_vision_lane[12] = me_a3->Rh_Neighbor_LaneMark_Pos_C0;
    front_vision_lane[13] = me_a3->Rh_Neighbor_LaneMark_Model_B_C1;
    front_vision_lane[14] = me_a3->Rh_Neighbor_LaneMark_Model_A_C2;
    front_vision_lane[15] = me_a3->Rh_Neighbor_LaneMark_Model_dA_C3;

    front_vision_lane[16] = me_ra->Classification_Rh_ME;
    front_vision_lane[17] = me_ra->Quality_Rh_ME;
    front_vision_lane[18] = me_ra->Marker_Width_Rh_ME;
    front_vision_lane[19] = me_ra->LaneMarkPosition_C0_Rh_ME;
    front_vision_lane[20] = me_rb->LaneMarkHeadingAngle_C1_Rh_ME;
    front_vision_lane[21] = me_ra->LaneMarkModelA_C2_Rh_ME;
    front_vision_lane[22] = me_rb->LaneMarkModelDerivA_C3_Rh_ME;

    front_vision_lane[23] = me_a1->Construction_Area_Detected;

    front_vision_lane[24] = me_ra->LDW_System_Availability_Rh_ME;
    front_vision_lane[25] = me_ra->LDW_Warning_Status_Rh_ME;


    check_run |= FVLR;
    
}

void callback_fvll(const mobileye_avante_msg::ME_Lane_Add_info_1::ConstPtr& me_i1, const mobileye_avante_msg::ME_Lane_Additional_Data_1::ConstPtr& me_a1, const mobileye_avante_msg::ME_Lane_Additional_Data_2::ConstPtr& me_a2, const mobileye_avante_msg::ME_Left_Lane_A::ConstPtr& me_la, const mobileye_avante_msg::ME_Left_Lane_B::ConstPtr& me_lb) {
    
    front_vision_lane[26] = me_i1->Lh_View_Start_Longitudinal_Dist;
    front_vision_lane[27] = me_i1->Lh_View_End_Longitudinal_Dist;
    front_vision_lane[28] = me_i1->LaneMark_Confidence_Ln_ME;
    front_vision_lane[29] = me_i1->LaneMark_Confidence_Ln_ME;
    front_vision_lane[30] = me_i1->LeftLanePrediction;

    front_vision_lane[31] = me_a1->Lh_Neightbor_Avail;
    front_vision_lane[32] = me_a1->Lh_Neightbor_Type;
    front_vision_lane[33] = me_a1->Lh_Guardrail;
    front_vision_lane[34] = me_a1->Highway_Merge_Left;
    front_vision_lane[35] = me_a1->Highway_Exit_Left;
    front_vision_lane[36] = me_a1->LeftLaneColorInfo;
    front_vision_lane[37] = me_a1->Lh_ViewRange_StartPoint;

    front_vision_lane[38] = me_a2->Lh_Neighbor_LaneMark_Pos_C0;
    front_vision_lane[39] = me_a2->Lh_Neighbor_LaneMark_Model_B_C1;
    front_vision_lane[40] = me_a2->Lh_Neighbor_LaneMark_Model_A_C2;
    front_vision_lane[41] = me_a2->Lh_Neighbor_LaneMark_Model_dA_C3;

    front_vision_lane[42] = me_la->Classification_Lh_ME;
    front_vision_lane[43] = me_la->Quality_Lh_ME;
    front_vision_lane[44] = me_la->Marker_Width_Lh_ME;
    front_vision_lane[45] = me_la->LaneMarkPosition_C0_Lh_ME;
    front_vision_lane[46] = me_lb->LaneMarkHeadingAngle_C1_Lh_ME;
    front_vision_lane[47] = me_la->LaneMarkModelA_C2_Lh_ME;
    front_vision_lane[48] = me_lb->LaneMarkModelDerivA_C3_Lh_ME;

    front_vision_lane[49] = me_a1->Construction_Area_Detected;

    front_vision_lane[50] = me_la->LDW_System_Availability_Lh_ME;
    front_vision_lane[51] = me_la->LDW_Warning_Status_Lh_ME;

    check_run |= FVLL;
}

void callback_frt1(const radar_msg::Track1::ConstPtr& track1, const radar_msg::Track2::ConstPtr& track2, const radar_msg::Track3::ConstPtr& track3, const radar_msg::Track4::ConstPtr& track4, const radar_msg::Track5::ConstPtr& track5, const radar_msg::Track6::ConstPtr& track6, const radar_msg::Track7::ConstPtr& track7, const radar_msg::Track8::ConstPtr& track8) {

    front_radar_track[0] = track1->Track_Angle;
    front_radar_track[1] = track1->Track_Range;
    front_radar_track[2] = track1->Track_Range_Accel;
    front_radar_track[3] = track1->Track_Range_Rate;
    front_radar_track[4] = track1->Track_Status;
    front_radar_track[5] = track1->Track_Width;
    
    front_radar_track[6] = track2->Track_Angle;
    front_radar_track[7] = track2->Track_Range;
    front_radar_track[8] = track2->Track_Range_Accel;
    front_radar_track[9] = track2->Track_Range_Rate;
    front_radar_track[10] = track2->Track_Status;
    front_radar_track[11] = track2->Track_Width;

    front_radar_track[12] = track3->Track_Angle;
    front_radar_track[13] = track3->Track_Range;
    front_radar_track[14] = track3->Track_Range_Accel;
    front_radar_track[15] = track3->Track_Range_Rate;
    front_radar_track[16] = track3->Track_Status;
    front_radar_track[17] = track3->Track_Width;

    front_radar_track[18] = track4->Track_Angle;
    front_radar_track[19] = track4->Track_Range;
    front_radar_track[20] = track4->Track_Range_Accel;
    front_radar_track[21] = track4->Track_Range_Rate;
    front_radar_track[22] = track4->Track_Status;
    front_radar_track[23] = track4->Track_Width;

    front_radar_track[24] = track5->Track_Angle;
    front_radar_track[25] = track5->Track_Range;
    front_radar_track[26] = track5->Track_Range_Accel;
    front_radar_track[27] = track5->Track_Range_Rate;
    front_radar_track[28] = track5->Track_Status;
    front_radar_track[29] = track5->Track_Width;

    front_radar_track[30] = track6->Track_Angle;
    front_radar_track[31] = track6->Track_Range;
    front_radar_track[32] = track6->Track_Range_Accel;
    front_radar_track[33] = track6->Track_Range_Rate;
    front_radar_track[34] = track6->Track_Status;
    front_radar_track[35] = track6->Track_Width;

    front_radar_track[36] = track7->Track_Angle;
    front_radar_track[37] = track7->Track_Range;
    front_radar_track[38] = track7->Track_Range_Accel;
    front_radar_track[39] = track7->Track_Range_Rate;
    front_radar_track[40] = track7->Track_Status;
    front_radar_track[41] = track7->Track_Width;

    front_radar_track[42] = track8->Track_Angle;
    front_radar_track[43] = track8->Track_Range;
    front_radar_track[44] = track8->Track_Range_Accel;
    front_radar_track[45] = track8->Track_Range_Rate;
    front_radar_track[46] = track8->Track_Status;
    front_radar_track[47] = track8->Track_Width;


    check_run |= FRT1;
    

}

void callback_frt2(const radar_msg::Track9::ConstPtr& track9, const radar_msg::Track10::ConstPtr& track10, const radar_msg::Track11::ConstPtr& track11, const radar_msg::Track12::ConstPtr& track12, const radar_msg::Track13::ConstPtr& track13, const radar_msg::Track14::ConstPtr& track14, const radar_msg::Track15::ConstPtr& track15, const radar_msg::Track16::ConstPtr& track16) {

    front_radar_track[48] = track9->Track_Angle;
    front_radar_track[49] = track9->Track_Range;
    front_radar_track[50] = track9->Track_Range_Accel;
    front_radar_track[51] = track9->Track_Range_Rate;
    front_radar_track[52] = track9->Track_Status;
    front_radar_track[53] = track9->Track_Width;
    
    front_radar_track[54] = track10->Track_Angle;
    front_radar_track[55] = track10->Track_Range;
    front_radar_track[56] = track10->Track_Range_Accel;
    front_radar_track[57] = track10->Track_Range_Rate;
    front_radar_track[58] = track10->Track_Status;
    front_radar_track[59] = track10->Track_Width;

    front_radar_track[60] = track11->Track_Angle;
    front_radar_track[61] = track11->Track_Range;
    front_radar_track[62] = track11->Track_Range_Accel;
    front_radar_track[63] = track11->Track_Range_Rate;
    front_radar_track[64] = track11->Track_Status;
    front_radar_track[65] = track11->Track_Width;

    front_radar_track[66] = track12->Track_Angle;
    front_radar_track[67] = track12->Track_Range;
    front_radar_track[68] = track12->Track_Range_Accel;
    front_radar_track[69] = track12->Track_Range_Rate;
    front_radar_track[70] = track12->Track_Status;
    front_radar_track[71] = track12->Track_Width;

    front_radar_track[72] = track13->Track_Angle;
    front_radar_track[73] = track13->Track_Range;
    front_radar_track[74] = track13->Track_Range_Accel;
    front_radar_track[75] = track13->Track_Range_Rate;
    front_radar_track[76] = track13->Track_Status;
    front_radar_track[77] = track13->Track_Width;

    front_radar_track[78] = track14->Track_Angle;
    front_radar_track[79] = track14->Track_Range;
    front_radar_track[80] = track14->Track_Range_Accel;
    front_radar_track[81] = track14->Track_Range_Rate;
    front_radar_track[82] = track14->Track_Status;
    front_radar_track[83] = track14->Track_Width;

    front_radar_track[84] = track15->Track_Angle;
    front_radar_track[85] = track15->Track_Range;
    front_radar_track[86] = track15->Track_Range_Accel;
    front_radar_track[87] = track15->Track_Range_Rate;
    front_radar_track[88] = track15->Track_Status;
    front_radar_track[89] = track15->Track_Width;

    front_radar_track[90] = track16->Track_Angle;
    front_radar_track[91] = track16->Track_Range;
    front_radar_track[92] = track16->Track_Range_Accel;
    front_radar_track[93] = track16->Track_Range_Rate;
    front_radar_track[94] = track16->Track_Status;
    front_radar_track[95] = track16->Track_Width;

    check_run |= FRT2;
    
}

void callback_frt3(const radar_msg::Track17::ConstPtr& track17, const radar_msg::Track18::ConstPtr& track18, const radar_msg::Track19::ConstPtr& track19, const radar_msg::Track20::ConstPtr& track20, const radar_msg::Track21::ConstPtr& track21, const radar_msg::Track22::ConstPtr& track22, const radar_msg::Track23::ConstPtr& track23, const radar_msg::Track24::ConstPtr& track24) {

    front_radar_track[96] = track17->Track_Angle;
    front_radar_track[97] = track17->Track_Range;
    front_radar_track[98] = track17->Track_Range_Accel;
    front_radar_track[99] = track17->Track_Range_Rate;
    front_radar_track[100] = track17->Track_Status;
    front_radar_track[101] = track17->Track_Width;
    
    front_radar_track[102] = track18->Track_Angle;
    front_radar_track[103] = track18->Track_Range;
    front_radar_track[104] = track18->Track_Range_Accel;
    front_radar_track[105] = track18->Track_Range_Rate;
    front_radar_track[106] = track18->Track_Status;
    front_radar_track[107] = track18->Track_Width;

    front_radar_track[108] = track19->Track_Angle;
    front_radar_track[109] = track19->Track_Range;
    front_radar_track[110] = track19->Track_Range_Accel;
    front_radar_track[111] = track19->Track_Range_Rate;
    front_radar_track[112] = track19->Track_Status;
    front_radar_track[113] = track19->Track_Width;

    front_radar_track[114] = track20->Track_Angle;
    front_radar_track[115] = track20->Track_Range;
    front_radar_track[116] = track20->Track_Range_Accel;
    front_radar_track[117] = track20->Track_Range_Rate;
    front_radar_track[118] = track20->Track_Status;
    front_radar_track[119] = track20->Track_Width;

    front_radar_track[120] = track21->Track_Angle;
    front_radar_track[121] = track21->Track_Range;
    front_radar_track[122] = track21->Track_Range_Accel;
    front_radar_track[123] = track21->Track_Range_Rate;
    front_radar_track[124] = track21->Track_Status;
    front_radar_track[125] = track21->Track_Width;

    front_radar_track[126] = track22->Track_Angle;
    front_radar_track[127] = track22->Track_Range;
    front_radar_track[128] = track22->Track_Range_Accel;
    front_radar_track[129] = track22->Track_Range_Rate;
    front_radar_track[130] = track22->Track_Status;
    front_radar_track[131] = track22->Track_Width;

    front_radar_track[132] = track23->Track_Angle;
    front_radar_track[133] = track23->Track_Range;
    front_radar_track[134] = track23->Track_Range_Accel;
    front_radar_track[135] = track23->Track_Range_Rate;
    front_radar_track[136] = track23->Track_Status;
    front_radar_track[137] = track23->Track_Width;

    front_radar_track[138] = track24->Track_Angle;
    front_radar_track[139] = track24->Track_Range;
    front_radar_track[140] = track24->Track_Range_Accel;
    front_radar_track[141] = track24->Track_Range_Rate;
    front_radar_track[142] = track24->Track_Status;
    front_radar_track[143] = track24->Track_Width;

    check_run |= FRT3;
}

void callback_frt4(const radar_msg::Track25::ConstPtr& track25, const radar_msg::Track26::ConstPtr& track26, const radar_msg::Track27::ConstPtr& track27, const radar_msg::Track28::ConstPtr& track28, const radar_msg::Track29::ConstPtr& track29, const radar_msg::Track30::ConstPtr& track30, const radar_msg::Track31::ConstPtr& track31, const radar_msg::Track32::ConstPtr& track32) {

    front_radar_track[144] = track25->Track_Angle;
    front_radar_track[145] = track25->Track_Range;
    front_radar_track[146] = track25->Track_Range_Accel;
    front_radar_track[147] = track25->Track_Range_Rate;
    front_radar_track[148] = track25->Track_Status;
    front_radar_track[149] = track25->Track_Width;
    
    front_radar_track[150] = track26->Track_Angle;
    front_radar_track[151] = track26->Track_Range;
    front_radar_track[152] = track26->Track_Range_Accel;
    front_radar_track[153] = track26->Track_Range_Rate;
    front_radar_track[154] = track26->Track_Status;
    front_radar_track[155] = track26->Track_Width;

    front_radar_track[156] = track27->Track_Angle;
    front_radar_track[157] = track27->Track_Range;
    front_radar_track[158] = track27->Track_Range_Accel;
    front_radar_track[159] = track27->Track_Range_Rate;
    front_radar_track[160] = track27->Track_Status;
    front_radar_track[161] = track27->Track_Width;

    front_radar_track[162] = track28->Track_Angle;
    front_radar_track[163] = track28->Track_Range;
    front_radar_track[164] = track28->Track_Range_Accel;
    front_radar_track[165] = track28->Track_Range_Rate;
    front_radar_track[166] = track28->Track_Status;
    front_radar_track[167] = track28->Track_Width;

    front_radar_track[168] = track29->Track_Angle;
    front_radar_track[169] = track29->Track_Range;
    front_radar_track[170] = track29->Track_Range_Accel;
    front_radar_track[171] = track29->Track_Range_Rate;
    front_radar_track[172] = track29->Track_Status;
    front_radar_track[173] = track29->Track_Width;

    front_radar_track[174] = track30->Track_Angle;
    front_radar_track[175] = track30->Track_Range;
    front_radar_track[176] = track30->Track_Range_Accel;
    front_radar_track[177] = track30->Track_Range_Rate;
    front_radar_track[178] = track30->Track_Status;
    front_radar_track[179] = track30->Track_Width;

    front_radar_track[180] = track31->Track_Angle;
    front_radar_track[181] = track31->Track_Range;
    front_radar_track[182] = track31->Track_Range_Accel;
    front_radar_track[183] = track31->Track_Range_Rate;
    front_radar_track[184] = track31->Track_Status;
    front_radar_track[185] = track31->Track_Width;

    front_radar_track[186] = track32->Track_Angle;
    front_radar_track[187] = track32->Track_Range;
    front_radar_track[188] = track32->Track_Range_Accel;
    front_radar_track[189] = track32->Track_Range_Rate;
    front_radar_track[190] = track32->Track_Status;
    front_radar_track[191] = track32->Track_Width;

    check_run |= FRT4;
}




