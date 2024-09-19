#ifndef __ENGINE_H__ 
#define __ENGINE_H__

#include "cover_headerfile_h.h" 

#define End_L_MOTOR 	       CAN_3_1 
#define End_R_MOTOR          CAN_3_2  
#define Traverse_MOTOR       CAN_3_3
#define Pitch_Root_MOTOR     CAN_3_4  
#define Roll_MOTOR 	         CAN_3_5	

#define small_Impel_L__MOTOR   	   CAN_3_6 
#define small_Impel_R__MOTOR       CAN_3_7 

#define Lifting_L__MOTOR   	 CAN_1_5 
#define Lifting_R__MOTOR     CAN_1_6 
#define Impel_L__MOTOR   	   CAN_1_7 
#define Impel_R__MOTOR       CAN_1_8  

extern uint32_t sinf_test_time;
extern int16_t sinf_number;

enum Engine_status_e
{
   ENGINE_LOCATION = 0,
   ENGINE_SPEED,
};

enum engine_mode_e
{
	return_to_zero = 0,
	grab_silver_mineral,
	grab_gold_mineral,
	grab_ground_mineral,
};

struct Engine_status
{
		enum engine_mode_e  Engine_mode;
	
		pid_t End_L_speed_pid;
		pid_t End_L_location_pid;

		pid_t End_R_speed_pid;
		pid_t End_R_location_pid;

		pid_t Roll_speed_pid;
		pid_t Roll_location_pid;

		pid_t Pitch_Root_speed_pid;
		pid_t Pitch_Root_location_pid;

		pid_t Traverse_speed_pid;
		pid_t Traverse_location_pid;

		pid_t Impel_L_speed_pid;
		pid_t Impel_L_location_pid;

		pid_t Impel_R_speed_pid;
		pid_t Impel_R_location_pid;

		pid_t Lifting_L_speed_pid;
		pid_t Lifting_L_location_pid;

		pid_t Lifting_R_speed_pid;
		pid_t Lifting_R_location_pid;

		pid_t small_Impel_L_speed_pid;
		pid_t small_Impel_L_location_pid;

		pid_t small_Impel_R_speed_pid;
		pid_t small_Impel_R_location_pid;

		enum Engine_status_e End_L_set_status;
    struct
    {
        float set, set_a_0, set_a_1, set_b_0, set_b_1, now, last, offset;
    } End_L_set;
    float End_L_speed;
    float End_L_set_speed;			
	

		enum Engine_status_e End_R_set_status;
    struct
    {
        float set, set_a_0, set_a_1, set_b_0, set_b_1, now, last, offset;
    } End_R_set;
    float End_R_speed;
    float End_R_set_speed;		


		enum Engine_status_e Roll_set_status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } Roll_set;
    float Roll_speed;
		float Roll_set_speed;


		enum Engine_status_e Pitch_Root_set_status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } Pitch_Root_set;
    float Pitch_Root_speed;
		float Pitch_Root_set_speed;


		enum Engine_status_e Traverse_set_status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } Traverse_set;
    float Traverse_speed;
		float Traverse_set_speed;


		enum Engine_status_e Impel_L_set__status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } Impel_L__set;
    float Impel_L_speed;
		float Impel_L_set_speed;


		enum Engine_status_e Impel_R_set__status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } Impel_R__set;
    float Impel_R_speed;
		float Impel_R_set_speed;


		enum Engine_status_e Lifting_L_set__status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } Lifting_L__set;
    float Lifting_L_speed;
		float Lifting_L_set_speed;


		enum Engine_status_e Lifting_R_set__status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } Lifting_R__set;
    float Lifting_R_speed;
		float Lifting_R_set_speed;

		
		enum Engine_status_e small_Impel_L_set__status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } small_Impel_L__set;
    float small_Impel_L_speed;
		float small_Impel_L_set_speed;


		enum Engine_status_e small_Impel_R_set__status;
    struct
    {
        float set, set_0, set_1,  now, last, offset;
    } small_Impel_R__set;
    float small_Impel_R_speed;
		float small_Impel_R_set_speed;		
	
};

extern struct Engine_status ENGINE_LOVE_5;


void ENGINE_LOVE_5_init(void);
void ENGINE_pid_cal(void);
void ENGINE_updata(void);

void ENGINE_Lifting_drive(int altitude,int delay_time_ms,float change_num);
void ENGINE_Impel_drive(int altitude,int delay_time_ms,float change_num);


void ENGINE_small_Impel_drive_0(int altitude,int delay_time_ms,float change_num);
void ENGINE_small_Impel_drive_1(int altitude,int delay_time_ms,float change_num);


//void ENGINE_Traverse_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *Traverse_set);
//void ENGINE_Roll_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *roll_set);
//void ENGINE_Pitch_Root_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *pitch_root_set);

//void ENGINE_END_pitch_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *l_set,float *r_set);
//void ENGINE_END_roll_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *l_set,float *r_set);

void ENGINE_Traverse_drive(int altitude,int delay_time_ms,float change_num,int min,int max);
void ENGINE_Roll_drive(int altitude,int delay_time_ms,float change_num,int min,int max);
void ENGINE_Pitch_Root_drive(int altitude,int delay_time_ms,float change_num,int min,int max);

void ENGINE_END_pitch_drive(int altitude,int delay_time_ms,float change_num,int min,int max);
void ENGINE_END_roll_drive(int altitude,int delay_time_ms,float change_num,int min,int max);



void Automatic_return_to_zero(void);//一键归位升降加50
void Automatic_return_to_second_zero(void);//一键归第二零点
void Automatic_grabbing_silver_mineral(void);//一键调整到抓取银矿的姿态
void Automatic_grabbing_3_silver_mineral(void);//一键调整到抓取3银矿的姿态   //-512   512
void Automatic_grabbing_gold_mineral(void);//一键调整到抓取金矿的姿态
void Automatic_grabbing_ground_mineral(void);//一键调整到抓取地面矿的姿态
void Automatic_fetch_Ore_reserves(void);//一键存矿
void Automatic_fetch_Ore_reserves_2(void);//一键取矿




#endif



