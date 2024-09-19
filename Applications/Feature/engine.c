#include "cover_headerfile_h.h"
#include "engine.h"
 
struct Engine_status ENGINE_LOVE_5;
uint32_t sinf_test_time;
int16_t sinf_number;

void ENGINE_LOVE_5_init(void)
{
	
		pid_set(&ENGINE_LOVE_5.Lifting_L_speed_pid,5.0f, 0.0f, 0.0f, 16000.0f, 300.0f);
    pid_set(&ENGINE_LOVE_5.Lifting_L_location_pid,220.0f, 0.0f, 20.0f, 6000.0f, 0.0f);	

		pid_set(&ENGINE_LOVE_5.Lifting_R_speed_pid,5.0f, 0.0f, 0.0f, 16000.0f, 300.0f);
    pid_set(&ENGINE_LOVE_5.Lifting_R_location_pid,220.0f, 0.0f, 20.0f, 6000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Traverse_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
    pid_set(&ENGINE_LOVE_5.Traverse_location_pid,50.0f, 0.0f, 0.0f, 2000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Impel_L_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
    pid_set(&ENGINE_LOVE_5.Impel_L_location_pid,50.0f, 0.0f, 0.0f, 5000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Impel_R_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
    pid_set(&ENGINE_LOVE_5.Impel_R_location_pid,50.0f, 0.0f, 0.0f, 5000.0f, 0.0f);
	
    pid_set(&ENGINE_LOVE_5.Pitch_Root_speed_pid, 15.0f, 0.0f, 5.0f, 16000.0f, 0.0f);	
	  pid_set(&ENGINE_LOVE_5.Pitch_Root_location_pid, 200.0f, 0.0f, 0.0f, 4000.0f, 0.0f);	

		pid_set(&ENGINE_LOVE_5.Roll_speed_pid, 1.0f, 0.0f, 1.0f, 30000.0f, 300.0f);
    pid_set(&ENGINE_LOVE_5.Roll_location_pid, 1000.0f, 0.0f, 0.0f, 20000.0f, 0.0f);
		
		pid_set(&ENGINE_LOVE_5.End_L_speed_pid,8.0f, 0.0f, 1.0f, 10000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.End_L_location_pid,120.0f, 0.0f, 5.0f, 5000.0f, 0.0f);				

		pid_set(&ENGINE_LOVE_5.End_R_speed_pid,8.0f, 0.0f, 1.0f, 10000.0f, 0.0f);
	  pid_set(&ENGINE_LOVE_5.End_R_location_pid,120.0f, 0.0f, 5.0f, 5000.0f, 0.0f);

		pid_set(&ENGINE_LOVE_5.small_Impel_L_speed_pid,10.0f, 0.0f, 1.0f, 14000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.small_Impel_L_location_pid,125.0f, 0.0f, 5.0f, 6000.0f, 0.0f);		
		
		pid_set(&ENGINE_LOVE_5.small_Impel_R_speed_pid,10.0f, 0.0f, 1.0f, 14000.0f, 0.0f);
	  pid_set(&ENGINE_LOVE_5.small_Impel_R_location_pid,125.0f, 0.0f, 5.0f, 6000.0f, 0.0f);


		ENGINE_LOVE_5.End_L_set.now = 0;
		ENGINE_LOVE_5.End_L_set.set = 0;
		ENGINE_LOVE_5.End_L_set.offset = 0;
		ENGINE_LOVE_5.End_L_set_speed= 0;
		ENGINE_LOVE_5.End_L_set_status= ENGINE_LOCATION;

		ENGINE_LOVE_5.End_R_set.now = 0;
		ENGINE_LOVE_5.End_R_set.set = 0;
		ENGINE_LOVE_5.End_R_set.offset = 0;
		ENGINE_LOVE_5.End_R_set_speed= 0;	
		ENGINE_LOVE_5.End_R_set_status= ENGINE_LOCATION;		

		ENGINE_LOVE_5.Roll_set.now = 0;
		ENGINE_LOVE_5.Roll_set.set = 0;
		ENGINE_LOVE_5.Roll_set.offset = 63.50f;
		ENGINE_LOVE_5.Roll_speed = 0;		
		ENGINE_LOVE_5.Roll_set_status= ENGINE_LOCATION;	

		ENGINE_LOVE_5.Pitch_Root_set.now = 0;
		ENGINE_LOVE_5.Pitch_Root_set.set = 0;
		ENGINE_LOVE_5.Pitch_Root_set.offset = 0;
		ENGINE_LOVE_5.Pitch_Root_speed = 0;	
		ENGINE_LOVE_5.Pitch_Root_set_status= ENGINE_LOCATION;			

		ENGINE_LOVE_5.Traverse_set.now = 0;
		ENGINE_LOVE_5.Traverse_set.set = 0;
		ENGINE_LOVE_5.Traverse_set.offset = 0;
		ENGINE_LOVE_5.Traverse_speed = 0;	
		ENGINE_LOVE_5.Pitch_Root_set_status= ENGINE_LOCATION;			

		ENGINE_LOVE_5.Impel_L__set.now = 0;
		ENGINE_LOVE_5.Impel_L__set.set = 0;
		ENGINE_LOVE_5.Impel_L__set.offset = 0;
		ENGINE_LOVE_5.Impel_L_speed = 0;	
		ENGINE_LOVE_5.Impel_L_set__status= ENGINE_LOCATION;			

		ENGINE_LOVE_5.Impel_R__set.now = 0;
		ENGINE_LOVE_5.Impel_R__set.set = 0;
		ENGINE_LOVE_5.Impel_R__set.offset = 0;
		ENGINE_LOVE_5.Impel_R_speed = 0;
		ENGINE_LOVE_5.Impel_R_set__status= ENGINE_LOCATION;					

		ENGINE_LOVE_5.Lifting_L__set.now = 0;
		ENGINE_LOVE_5.Lifting_L__set.set = 0;
		ENGINE_LOVE_5.Lifting_L__set.offset = 0;
		ENGINE_LOVE_5.Lifting_L_speed = 0;
		ENGINE_LOVE_5.Lifting_L_set__status= ENGINE_LOCATION;			

		ENGINE_LOVE_5.Lifting_R__set.now = 0;
		ENGINE_LOVE_5.Lifting_R__set.set = 0;
		ENGINE_LOVE_5.Lifting_R__set.offset = 0.0f;
		ENGINE_LOVE_5.Lifting_R_set__status= ENGINE_LOCATION;		


		ENGINE_LOVE_5.small_Impel_L__set.now = 0;
		ENGINE_LOVE_5.small_Impel_L__set.set = 0;
		ENGINE_LOVE_5.small_Impel_L__set.offset = 0;
		ENGINE_LOVE_5.small_Impel_L_speed = 0;	
		ENGINE_LOVE_5.small_Impel_L_set__status= ENGINE_LOCATION;			

		ENGINE_LOVE_5.small_Impel_R__set.now = 0;
		ENGINE_LOVE_5.small_Impel_R__set.set = 0;
		ENGINE_LOVE_5.small_Impel_R__set.offset = 0;
		ENGINE_LOVE_5.small_Impel_R_speed = 0;
		ENGINE_LOVE_5.small_Impel_R_set__status= ENGINE_LOCATION;	


}

void ENGINE_pid_cal(void)
{
	
	if(Global.PID_mode==PID_NORMAL)
	{
		pid_set(&ENGINE_LOVE_5.Lifting_L_speed_pid,5.0f, 0.0f, 0.0f, 16000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Lifting_L_location_pid,250.0f, 0.0f, 20.0f, 6000.0f, 0.0f);	

		pid_set(&ENGINE_LOVE_5.Lifting_R_speed_pid,5.0f, 0.0f, 0.0f, 16000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Lifting_R_location_pid,250.0f, 0.0f, 20.0f, 6000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Traverse_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Traverse_location_pid,50.0f, 0.0f, 0.0f, 2000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Impel_L_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Impel_L_location_pid,50.0f, 0.0f, 0.0f, 5000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Impel_R_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Impel_R_location_pid,50.0f, 0.0f, 0.0f, 5000.0f, 0.0f);;	
	

		pid_set(&ENGINE_LOVE_5.Pitch_Root_speed_pid, 15.0f, 0.0f, 5.0f, 16000.0f, 0.0f);	
		pid_set(&ENGINE_LOVE_5.Pitch_Root_location_pid, 200.0f, 0.0f, 0.0f, 6000.0f, 0.0f);	

		pid_set(&ENGINE_LOVE_5.Roll_speed_pid, 1.0f, 0.0f, 1.0f, 30000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Roll_location_pid, 1000.0f, 0.0f, 0.0f, 20000.0f, 0.0f);

		pid_set(&ENGINE_LOVE_5.End_L_speed_pid,8.0f, 0.0f, 1.0f, 10000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.End_L_location_pid,120.0f, 0.0f, 5.0f, 5000.0f, 0.0f);						

		pid_set(&ENGINE_LOVE_5.End_R_speed_pid,8.0f, 0.0f, 1.0f, 10000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.End_R_location_pid,120.0f, 0.0f, 5.0f, 5000.0f, 0.0f);

		pid_set(&ENGINE_LOVE_5.small_Impel_L_speed_pid,10.0f, 0.0f, 1.0f, 14000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.small_Impel_L_location_pid,125.0f, 0.0f, 5.0f, 6000.0f, 0.0f);		
		
		pid_set(&ENGINE_LOVE_5.small_Impel_R_speed_pid,10.0f, 0.0f, 1.0f, 14000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.small_Impel_R_location_pid,125.0f, 0.0f, 5.0f, 6000.0f, 0.0f);
	}
	else if(Global.PID_mode==PID_Auto)
	{
		pid_set(&ENGINE_LOVE_5.Lifting_L_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Lifting_L_location_pid,200.0f, 0.0f, 20.0f, 2000.0f, 0.0f);	

		pid_set(&ENGINE_LOVE_5.Lifting_R_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Lifting_R_location_pid,200.0f, 0.0f, 20.0f, 2000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Traverse_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Traverse_location_pid,50.0f, 0.0f, 0.0f, 2000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Impel_L_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Impel_L_location_pid,30.0f, 0.0f, 0.0f, 1500.0f, 0.0f);
	
		pid_set(&ENGINE_LOVE_5.Impel_R_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Impel_R_location_pid,30.0f, 0.0f, 0.0f, 1500.0f, 0.0f);	
	

		pid_set(&ENGINE_LOVE_5.Pitch_Root_speed_pid, 15.0f, 0.0f, 5.0f, 16000.0f, 0.0f);	
		pid_set(&ENGINE_LOVE_5.Pitch_Root_location_pid, 125.0f, 0.0f, 0.0f, 1000.0f, 0.0f);	

		pid_set(&ENGINE_LOVE_5.Roll_speed_pid, 40.0f, 0.0f, 5.0f, 25000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Roll_location_pid, 25.0f, 0.0f, 0.0f, 2000.0f, 0.0f);

		pid_set(&ENGINE_LOVE_5.End_L_speed_pid,8.0f, 0.0f, 1.0f, 10000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.End_L_location_pid,85.0f, 0.0f, 5.0f, 2500.0f, 0.0f);					
		pid_set(&ENGINE_LOVE_5.End_R_speed_pid,8.0f, 0.0f, 1.0f, 10000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.End_R_location_pid,85.0f, 0.0f, 5.0f, 2500.0f, 0.0f);

		pid_set(&ENGINE_LOVE_5.small_Impel_L_speed_pid,10.0f, 0.0f, 1.0f, 14000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.small_Impel_L_location_pid,125.0f, 0.0f, 5.0f, 6000.0f, 0.0f);		
		
		pid_set(&ENGINE_LOVE_5.small_Impel_R_speed_pid,10.0f, 0.0f, 1.0f, 14000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.small_Impel_R_location_pid,125.0f, 0.0f, 5.0f, 6000.0f, 0.0f);
	}
	else 
	{
		pid_set(&ENGINE_LOVE_5.Lifting_L_speed_pid,5.0f, 0.0f, 0.0f, 16000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Lifting_L_location_pid,250.0f, 0.0f, 20.0f, 6000.0f, 0.0f);	

		pid_set(&ENGINE_LOVE_5.Lifting_R_speed_pid,5.0f, 0.0f, 0.0f, 16000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Lifting_R_location_pid,250.0f, 0.0f, 20.0f, 6000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Traverse_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Traverse_location_pid,50.0f, 0.0f, 0.0f, 2000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Impel_L_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Impel_L_location_pid,50.0f, 0.0f, 0.0f, 5000.0f, 0.0f);	
	
		pid_set(&ENGINE_LOVE_5.Impel_R_speed_pid,5.0f, 0.0f, 0.0f, 15000.0f, 0.0f);		
		pid_set(&ENGINE_LOVE_5.Impel_R_location_pid,50.0f, 0.0f, 0.0f, 5000.0f, 0.0f);;	
	

		pid_set(&ENGINE_LOVE_5.Pitch_Root_speed_pid, 15.0f, 0.0f, 5.0f, 16000.0f, 0.0f);	
		pid_set(&ENGINE_LOVE_5.Pitch_Root_location_pid, 200.0f, 0.0f, 0.0f, 6000.0f, 0.0f);	

		pid_set(&ENGINE_LOVE_5.Roll_speed_pid, 1.0f, 0.0f, 1.0f, 30000.0f, 300.0f);
		pid_set(&ENGINE_LOVE_5.Roll_location_pid, 1000.0f, 0.0f, 0.0f, 20000.0f, 0.0f);

		pid_set(&ENGINE_LOVE_5.End_L_speed_pid,8.0f, 0.0f, 1.0f, 10000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.End_L_location_pid,120.0f, 0.0f, 5.0f, 5000.0f, 0.0f);					

		pid_set(&ENGINE_LOVE_5.End_R_speed_pid,8.0f, 0.0f, 1.0f, 10000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.End_R_location_pid,120.0f, 0.0f, 5.0f, 5000.0f, 0.0f);

		pid_set(&ENGINE_LOVE_5.small_Impel_L_speed_pid,10.0f, 0.0f, 1.0f, 14000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.small_Impel_L_location_pid,125.0f, 0.0f, 5.0f, 6000.0f, 0.0f);		
		
		pid_set(&ENGINE_LOVE_5.small_Impel_R_speed_pid,10.0f, 0.0f, 1.0f, 14000.0f, 0.0f);
		pid_set(&ENGINE_LOVE_5.small_Impel_R_location_pid,125.0f, 0.0f, 5.0f, 6000.0f, 0.0f);
	}
		


	if(ENGINE_LOVE_5.End_L_set_status== ENGINE_LOCATION)
		ENGINE_LOVE_5.End_L_set_speed = pid_cal(&ENGINE_LOVE_5.End_L_location_pid, ENGINE_LOVE_5.End_L_set.now, ENGINE_LOVE_5.End_L_set.set);
	if(ENGINE_LOVE_5.End_R_set_status== ENGINE_LOCATION)
		ENGINE_LOVE_5.End_R_set_speed = pid_cal(&ENGINE_LOVE_5.End_R_location_pid, ENGINE_LOVE_5.End_R_set.now, ENGINE_LOVE_5.End_R_set.set);

	if(ENGINE_LOVE_5.Roll_set_status== ENGINE_LOCATION)
		ENGINE_LOVE_5.Roll_set_speed = pid_cal(&ENGINE_LOVE_5.Roll_location_pid, ENGINE_LOVE_5.Roll_set.now, ENGINE_LOVE_5.Roll_set.set);

	if(ENGINE_LOVE_5.Pitch_Root_set_status== ENGINE_LOCATION)
		ENGINE_LOVE_5.Pitch_Root_set_speed = pid_cal(&ENGINE_LOVE_5.Pitch_Root_location_pid, ENGINE_LOVE_5.Pitch_Root_set.now, ENGINE_LOVE_5.Pitch_Root_set.set);		

	if(ENGINE_LOVE_5.Traverse_set_status== ENGINE_LOCATION)
		ENGINE_LOVE_5.Traverse_set_speed = pid_cal(&ENGINE_LOVE_5.Traverse_location_pid, ENGINE_LOVE_5.Traverse_set.now, ENGINE_LOVE_5.Traverse_set.set);		

	if(ENGINE_LOVE_5.Impel_L_set__status == ENGINE_LOCATION)
		ENGINE_LOVE_5.Impel_L_set_speed = pid_cal(&ENGINE_LOVE_5.Impel_L_location_pid, ENGINE_LOVE_5.Impel_L__set.now, ENGINE_LOVE_5.Impel_L__set.set);		
	if(ENGINE_LOVE_5.Impel_R_set__status == ENGINE_LOCATION)
		ENGINE_LOVE_5.Impel_R_set_speed = pid_cal(&ENGINE_LOVE_5.Impel_R_location_pid, ENGINE_LOVE_5.Impel_R__set.now, ENGINE_LOVE_5.Impel_R__set.set);	//

	if(ENGINE_LOVE_5.Lifting_L_set__status== ENGINE_LOCATION)
		ENGINE_LOVE_5.Lifting_L_set_speed = pid_cal(&ENGINE_LOVE_5.Lifting_L_location_pid, ENGINE_LOVE_5.Lifting_L__set.now, ENGINE_LOVE_5.Lifting_L__set.set);		
	if(ENGINE_LOVE_5.Lifting_R_set__status== ENGINE_LOCATION)
		ENGINE_LOVE_5.Lifting_R_set_speed = pid_cal(&ENGINE_LOVE_5.Lifting_R_location_pid, ENGINE_LOVE_5.Lifting_R__set.now, (ENGINE_LOVE_5.Lifting_R__set.set+10.0f));	//+25.0f  +12.50f  +18.75f    12.5f

	if(ENGINE_LOVE_5.small_Impel_L_set__status == ENGINE_LOCATION)
		ENGINE_LOVE_5.small_Impel_L_set_speed = pid_cal(&ENGINE_LOVE_5.small_Impel_L_location_pid, ENGINE_LOVE_5.small_Impel_L__set.now, ENGINE_LOVE_5.small_Impel_L__set.set);		
	if(ENGINE_LOVE_5.small_Impel_R_set__status == ENGINE_LOCATION)
		ENGINE_LOVE_5.small_Impel_R_set_speed = pid_cal(&ENGINE_LOVE_5.small_Impel_R_location_pid, ENGINE_LOVE_5.small_Impel_R__set.now, ENGINE_LOVE_5.small_Impel_R__set.set);			

	

	if(robot_status.power_management_gimbal_output==1&&Global.mode==NORMAL)//								if(Global.mode==NORMAL)		 sinf_number
	{
		set_motor((pid_cal(&ENGINE_LOVE_5.End_L_speed_pid, get_motor_data(End_L_MOTOR).speed_rpm, ENGINE_LOVE_5.End_L_set_speed)+ sinf_number), End_L_MOTOR);
		set_motor((pid_cal(&ENGINE_LOVE_5.End_R_speed_pid, get_motor_data(End_R_MOTOR).speed_rpm, ENGINE_LOVE_5.End_R_set_speed)+ sinf_number), End_R_MOTOR);

		set_motor(pid_cal(&ENGINE_LOVE_5.Roll_speed_pid, get_motor_data(Roll_MOTOR).speed_rpm, ENGINE_LOVE_5.Roll_set_speed), Roll_MOTOR);

		set_motor(pid_cal(&ENGINE_LOVE_5.Pitch_Root_speed_pid, get_motor_data(Pitch_Root_MOTOR).speed_rpm, ENGINE_LOVE_5.Pitch_Root_set_speed), Pitch_Root_MOTOR);

		set_motor(pid_cal(&ENGINE_LOVE_5.Traverse_speed_pid, get_motor_data(Traverse_MOTOR).speed_rpm, ENGINE_LOVE_5.Traverse_set_speed), Traverse_MOTOR);

		set_motor(pid_cal(&ENGINE_LOVE_5.Impel_L_speed_pid, get_motor_data(Impel_L__MOTOR).speed_rpm, ENGINE_LOVE_5.Impel_L_set_speed), Impel_L__MOTOR);
		set_motor(pid_cal(&ENGINE_LOVE_5.Impel_R_speed_pid, get_motor_data(Impel_R__MOTOR).speed_rpm, ENGINE_LOVE_5.Impel_R_set_speed), Impel_R__MOTOR);

		set_motor(pid_cal(&ENGINE_LOVE_5.Lifting_L_speed_pid, get_motor_data(Lifting_L__MOTOR).speed_rpm, ENGINE_LOVE_5.Lifting_L_set_speed), Lifting_L__MOTOR);
		set_motor(pid_cal(&ENGINE_LOVE_5.Lifting_R_speed_pid, get_motor_data(Lifting_R__MOTOR).speed_rpm, ENGINE_LOVE_5.Lifting_R_set_speed), Lifting_R__MOTOR);		

		set_motor((pid_cal(&ENGINE_LOVE_5.small_Impel_L_speed_pid, get_motor_data(small_Impel_L__MOTOR).speed_rpm, ENGINE_LOVE_5.small_Impel_L_set_speed) + sinf_number), small_Impel_L__MOTOR);
		set_motor((pid_cal(&ENGINE_LOVE_5.small_Impel_R_speed_pid, get_motor_data(small_Impel_R__MOTOR).speed_rpm, ENGINE_LOVE_5.small_Impel_R_set_speed) + sinf_number), small_Impel_R__MOTOR);	
	}
	else if(robot_status.power_management_gimbal_output==0||Global.mode==LOCK)//								else if(Global.mode==LOCK)		
	{
		set_motor(0, End_L_MOTOR);
		set_motor(0, End_R_MOTOR);
		set_motor(0, Roll_MOTOR);
		set_motor(0, Pitch_Root_MOTOR);
		set_motor(0, Traverse_MOTOR);
		set_motor(0, Impel_L__MOTOR);
		set_motor(0, Impel_R__MOTOR);
		set_motor(0, Lifting_L__MOTOR);
		set_motor(0, Lifting_R__MOTOR);		
		set_motor(0, small_Impel_L__MOTOR);
		set_motor(0, small_Impel_R__MOTOR);
	}

	
}

void ENGINE_updata(void)
{
		decode_as_2006_pitch_end(End_L_MOTOR);
		ENGINE_LOVE_5.End_L_set.now = (get_motor_data(End_L_MOTOR).angle_cnt) - ENGINE_LOVE_5.End_L_set.offset;
		ENGINE_LOVE_5.End_L_speed = get_motor_data(End_L_MOTOR).speed_rpm;
    ENGINE_LOVE_5.End_L_set.set = ENGINE_LOVE_5.End_L_set.set_a_0 + ENGINE_LOVE_5.End_L_set.set_a_1 + ENGINE_LOVE_5.End_L_set.set_b_0 + ENGINE_LOVE_5.End_L_set.set_b_1;
	  decode_as_2006_pitch_end(End_R_MOTOR);
		ENGINE_LOVE_5.End_R_set.now = (get_motor_data(End_R_MOTOR).angle_cnt) - ENGINE_LOVE_5.End_R_set.offset;
		ENGINE_LOVE_5.End_R_speed = get_motor_data(End_R_MOTOR).speed_rpm;
    ENGINE_LOVE_5.End_R_set.set = ENGINE_LOVE_5.End_R_set.set_a_0 + ENGINE_LOVE_5.End_R_set.set_a_1 + ENGINE_LOVE_5.End_R_set.set_b_0 + ENGINE_LOVE_5.End_R_set.set_b_1;	

	
		decode_as_6020(Roll_MOTOR);
		ENGINE_LOVE_5.Roll_set.now = (get_motor_data(Roll_MOTOR).angle_cnt) - ENGINE_LOVE_5.Roll_set.offset;
		ENGINE_LOVE_5.Roll_speed=get_motor_data(Roll_MOTOR).speed_rpm;	
		ENGINE_LOVE_5.Roll_set.set = ENGINE_LOVE_5.Roll_set.set_0 + ENGINE_LOVE_5.Roll_set.set_1;


		decode_as_3508_Pitch_Root(Pitch_Root_MOTOR);//19*70.03/22.28
		ENGINE_LOVE_5.Pitch_Root_set.now = (get_motor_data(Pitch_Root_MOTOR).angle_cnt) - ENGINE_LOVE_5.Pitch_Root_set.offset;
		ENGINE_LOVE_5.Pitch_Root_speed=get_motor_data(Pitch_Root_MOTOR).speed_rpm;
		ENGINE_LOVE_5.Pitch_Root_set.set = ENGINE_LOVE_5.Pitch_Root_set.set_0 + ENGINE_LOVE_5.Pitch_Root_set.set_1;

		decode_as_3508(Traverse_MOTOR);
		ENGINE_LOVE_5.Traverse_set.now = (get_motor_data(Traverse_MOTOR).angle_cnt) - ENGINE_LOVE_5.Traverse_set.offset;
		ENGINE_LOVE_5.Traverse_speed=get_motor_data(Traverse_MOTOR).speed_rpm;
		ENGINE_LOVE_5.Traverse_set.set = ENGINE_LOVE_5.Traverse_set.set_0 + ENGINE_LOVE_5.Traverse_set.set_1;

		decode_as_3508(Impel_L__MOTOR);	
		ENGINE_LOVE_5.Impel_L__set.now = (get_motor_data(Impel_L__MOTOR).angle_cnt) - ENGINE_LOVE_5.Impel_L__set.offset;
		ENGINE_LOVE_5.Impel_L_speed=get_motor_data(Impel_L__MOTOR).speed_rpm;
		ENGINE_LOVE_5.Impel_L__set.set = ENGINE_LOVE_5.Impel_L__set.set_0 + ENGINE_LOVE_5.Impel_L__set.set_1;
	  decode_as_3508(Impel_R__MOTOR);	
		ENGINE_LOVE_5.Impel_R__set.now = (get_motor_data(Impel_R__MOTOR).angle_cnt) - ENGINE_LOVE_5.Impel_R__set.offset;
		ENGINE_LOVE_5.Impel_R_speed=get_motor_data(Impel_R__MOTOR).speed_rpm;
		ENGINE_LOVE_5.Impel_R__set.set = ENGINE_LOVE_5.Impel_R__set.set_0 + ENGINE_LOVE_5.Impel_R__set.set_1;

		decode_as_3508(Lifting_L__MOTOR);	
		ENGINE_LOVE_5.Lifting_L__set.now = (get_motor_data(Lifting_L__MOTOR).angle_cnt) - ENGINE_LOVE_5.Lifting_L__set.offset;
		ENGINE_LOVE_5.Lifting_L_speed=get_motor_data(Lifting_L__MOTOR).speed_rpm;
		ENGINE_LOVE_5.Lifting_L__set.set = ENGINE_LOVE_5.Lifting_L__set.set_0 + ENGINE_LOVE_5.Lifting_L__set.set_1;
		decode_as_3508(Lifting_R__MOTOR);	
		ENGINE_LOVE_5.Lifting_R__set.now = (get_motor_data(Lifting_R__MOTOR).angle_cnt) - ENGINE_LOVE_5.Lifting_R__set.offset;
		ENGINE_LOVE_5.Lifting_R_speed=get_motor_data(Lifting_R__MOTOR).speed_rpm;
		ENGINE_LOVE_5.Lifting_R__set.set = ENGINE_LOVE_5.Lifting_R__set.set_0 + ENGINE_LOVE_5.Lifting_R__set.set_1;


		decode_as_2006(small_Impel_L__MOTOR);	
		ENGINE_LOVE_5.small_Impel_L__set.now = (get_motor_data(small_Impel_L__MOTOR).angle_cnt) - ENGINE_LOVE_5.small_Impel_L__set.offset;
		ENGINE_LOVE_5.small_Impel_L_speed=get_motor_data(small_Impel_L__MOTOR).speed_rpm;
		ENGINE_LOVE_5.small_Impel_L__set.set = ENGINE_LOVE_5.small_Impel_L__set.set_0 + ENGINE_LOVE_5.small_Impel_L__set.set_1;
	  decode_as_2006(small_Impel_R__MOTOR);	
		ENGINE_LOVE_5.small_Impel_R__set.now = (get_motor_data(small_Impel_R__MOTOR).angle_cnt) - ENGINE_LOVE_5.small_Impel_R__set.offset;
		ENGINE_LOVE_5.small_Impel_R_speed=get_motor_data(small_Impel_R__MOTOR).speed_rpm;
		ENGINE_LOVE_5.small_Impel_R__set.set = ENGINE_LOVE_5.small_Impel_R__set.set_0 + ENGINE_LOVE_5.small_Impel_R__set.set_1;
}



//void ENGINE_Lifting_drive(int altitude,int delay_time_ms,float change_num)
//{

//	static uint32_t last_time =0;
//	static float _r_set=0,_l_set=0;
//	const int max=0; 
//	const int min=-860;
//	
//	if(Get_sys_time_ms() - last_time > delay_time_ms)
//   {
//		last_time = Get_sys_time_ms();
//		if(_l_set>=-max&&_l_set<=-min&&_r_set<=max&&_r_set>=min)
//		{
//			if(altitude > 0&&_l_set!=-max&&_r_set!=max)
//			{
//				_l_set -=change_num;
//				_r_set +=change_num;
//			}
//			if(altitude < 0&&_l_set!=-min&&_r_set!=min)
//			{
//				_l_set +=change_num;
//				_r_set -=change_num;
//			}
//		}
//		else if(_l_set<-max&&_r_set>max)
//		{
//			_l_set=-max;
//			_r_set= max;
//		}
//		else if(_l_set>-min&&_r_set<min)
//		{
//			_l_set=-min;
//			_r_set= min;	
//		}

//		ENGINE_LOVE_5.Lifting_L__set.set_0 = -_l_set;
//		ENGINE_LOVE_5.Lifting_R__set.set_0 = -_r_set;
//	}
//}


void ENGINE_Lifting_drive(int altitude,int delay_time_ms,float change_num)
{
	static uint32_t last_time =0;
//	static float _r_set=0,_l_set=0;
	const int max=0; 
	const int min=-860;////860
	
	if(Get_sys_time_ms() - last_time > delay_time_ms)
   {
		last_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.Lifting_L__set.set_0<=max&&ENGINE_LOVE_5.Lifting_L__set.set_0>=min&&ENGINE_LOVE_5.Lifting_R__set.set_0>=-max&&ENGINE_LOVE_5.Lifting_R__set.set_0<=-min)
		{
			if(altitude > 0&&ENGINE_LOVE_5.Lifting_L__set.set_0!=max&&ENGINE_LOVE_5.Lifting_R__set.set_0!=-max)
			{
				ENGINE_LOVE_5.Lifting_L__set.set_0 +=change_num;
				ENGINE_LOVE_5.Lifting_R__set.set_0 -=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.Lifting_L__set.set_0!=min&&ENGINE_LOVE_5.Lifting_R__set.set_0!=-min)
			{
				ENGINE_LOVE_5.Lifting_L__set.set_0 -=change_num;
				ENGINE_LOVE_5.Lifting_R__set.set_0 +=change_num;
			}
		}
		else if(ENGINE_LOVE_5.Lifting_L__set.set_0>max&&ENGINE_LOVE_5.Lifting_R__set.set_0<-max)
		{
			ENGINE_LOVE_5.Lifting_L__set.set_0=  max;
			ENGINE_LOVE_5.Lifting_R__set.set_0= -max;
		}
		else if(ENGINE_LOVE_5.Lifting_L__set.set_0<min&&ENGINE_LOVE_5.Lifting_R__set.set_0>-min)
		{
			ENGINE_LOVE_5.Lifting_L__set.set_0=  min;
			ENGINE_LOVE_5.Lifting_R__set.set_0= -min;	
		}
//		-ENGINE_LOVE_5.Lifting_L__set.set_0 = _l_set;
//		-ENGINE_LOVE_5.Lifting_R__set.set_0 = _r_set;
	}
}







//void ENGINE_Impel_drive(int altitude,int delay_time_ms,float change_num)
//{
//	static uint32_t last_time =0;	
//	static float _r_set=0,_l_set=0;	
//	const int max=1580;  const int min=0;		
//  if (Get_sys_time_ms() - last_time > delay_time_ms)
//  {
//			last_time = Get_sys_time_ms();
//		if(_r_set>=-max&&_r_set<=-min&&_l_set<=max&&_l_set>=min)
//		{
//			if(altitude > 0&&_r_set!=-max&&_l_set!=max)
//			{
//				_l_set +=change_num;				
//				_r_set -=change_num;
//			}
//			if(altitude < 0&&_r_set!=-min&&_l_set!=min)
//			{
//				_l_set -=change_num;
//				_r_set +=change_num;
//			}
//		}
//		else if(_r_set<-max&&_l_set>max)
//		{
//			_l_set=max;			
//			_r_set=-max;
//		}
//		else if(_r_set>-min&&_l_set<min)
//		{
//			_l_set=min;				
//			_r_set=-min;
//		}
//		ENGINE_LOVE_5.Impel_L__set.set_0 = _l_set;			
//		ENGINE_LOVE_5.Impel_R__set.set_0 = _r_set;		
//	}

//}



void ENGINE_Impel_drive(int altitude,int delay_time_ms,float change_num)
{
	static uint32_t last_time =0;	
//	static float _r_set=0,_l_set=0;	
	const int max=1725;  const int min=0;		//1770
  if (Get_sys_time_ms() - last_time > delay_time_ms)
  {
			last_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.Impel_R__set.set_0>=-max&&ENGINE_LOVE_5.Impel_R__set.set_0<=-min&&ENGINE_LOVE_5.Impel_L__set.set_0<=max&&ENGINE_LOVE_5.Impel_L__set.set_0>=min)
		{
			if(altitude > 0&&ENGINE_LOVE_5.Impel_R__set.set_0!=-max&&ENGINE_LOVE_5.Impel_L__set.set_0!=max)
			{
				ENGINE_LOVE_5.Impel_L__set.set_0 +=change_num;				
				ENGINE_LOVE_5.Impel_R__set.set_0 -=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.Impel_R__set.set_0!=-min&&ENGINE_LOVE_5.Impel_L__set.set_0!=min)
			{
				ENGINE_LOVE_5.Impel_L__set.set_0 -=change_num;
				ENGINE_LOVE_5.Impel_R__set.set_0 +=change_num;
			}
		}
		else if(ENGINE_LOVE_5.Impel_R__set.set_0<-max&&ENGINE_LOVE_5.Impel_L__set.set_0>max)
		{
			ENGINE_LOVE_5.Impel_L__set.set_0=max;			
			ENGINE_LOVE_5.Impel_R__set.set_0=-max;
		}
		else if(ENGINE_LOVE_5.Impel_R__set.set_0>-min&&ENGINE_LOVE_5.Impel_L__set.set_0<min)
		{
			ENGINE_LOVE_5.Impel_L__set.set_0=min;				
			ENGINE_LOVE_5.Impel_R__set.set_0=-min;
		}
//		ENGINE_LOVE_5.Impel_L__set.set_0 = _l_set;			
//		ENGINE_LOVE_5.Impel_R__set.set_0 = _r_set;		
	}

}


//void ENGINE_small_Impel_drive_0(int altitude,int delay_time_ms,float change_num)
//{
//	static uint32_t last_time =0;	
//	static float _r_set=0,_l_set=0;	
//	const int max=765;  const int min=0;		
//  if (Get_sys_time_ms() - last_time > delay_time_ms)
//  {
//			last_time = Get_sys_time_ms();
//		if(_l_set>=-max&&_l_set<=-min&&_r_set<=max&&_r_set>=min)
//		{
//			if(altitude > 0&&_l_set!=-max&&_r_set!=max)
//			{
//				_r_set +=change_num;				
//				_l_set -=change_num;
//			}
//			if(altitude < 0&&_l_set!=-min&&_r_set!=min)
//			{
//				_r_set -=change_num;
//				_l_set +=change_num;
//			}
//		}
//		else if(_l_set<-max&&_r_set>max)
//		{
//			_r_set=max;			
//			_l_set=-max;
//		}
//		else if(_l_set>-min&&_r_set<min)
//		{
//			_r_set=min;				
//			_l_set=-min;
//		}
//		ENGINE_LOVE_5.small_Impel_R__set.set_0 = _r_set;			
//		ENGINE_LOVE_5.small_Impel_L__set.set_0 = _l_set;		
//	}

//}


//void ENGINE_small_Impel_drive_1(int altitude,int delay_time_ms,float change_num)
//{
//	static uint32_t last_time =0;	
//	static float _r_set=0,_l_set=0;	
//	const int max=580;  const int min=0;		
//  if (Get_sys_time_ms() - last_time > delay_time_ms)
//  {
//			last_time = Get_sys_time_ms();
//		if(_l_set>=-max&&_l_set<=-min&&_r_set<=max&&_r_set>=min)
//		{
//			if(altitude > 0&&_l_set!=-max&&_r_set!=max)
//			{
//				_r_set +=change_num;				
//				_l_set -=change_num;
//			}
//			if(altitude < 0&&_l_set!=-min&&_r_set!=min)
//			{
//				_r_set -=change_num;
//				_l_set +=change_num;
//			}
//		}
//		else if(_l_set<-max&&_r_set>max)
//		{
//			_r_set=max;			
//			_l_set=-max;
//		}
//		else if(_l_set>-min&&_r_set<min)
//		{
//			_r_set=min;				
//			_l_set=-min;
//		}
//		ENGINE_LOVE_5.small_Impel_R__set.set_1 = _r_set;			
//		ENGINE_LOVE_5.small_Impel_L__set.set_1 = _l_set;		
//	}

//}



void ENGINE_small_Impel_drive_0(int altitude,int delay_time_ms,float change_num)
{
	static uint32_t last_time =0;	
//	static float _r_set=0,_l_set=0;	
	const int max=1500;  const int min=0;		//765  +  580   = 
  if (Get_sys_time_ms() - last_time > delay_time_ms)
  {
			last_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.small_Impel_L__set.set_0>=-max&&ENGINE_LOVE_5.small_Impel_L__set.set_0<=-min&&ENGINE_LOVE_5.small_Impel_R__set.set_0<=max&&ENGINE_LOVE_5.small_Impel_R__set.set_0>=min)
		{
			if(altitude > 0&&ENGINE_LOVE_5.small_Impel_L__set.set_0!=-max&&ENGINE_LOVE_5.small_Impel_R__set.set_0!=max)
			{
				ENGINE_LOVE_5.small_Impel_R__set.set_0 +=change_num;				
				ENGINE_LOVE_5.small_Impel_L__set.set_0 -=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.small_Impel_L__set.set_0!=-min&&ENGINE_LOVE_5.small_Impel_R__set.set_0!=min)
			{
				ENGINE_LOVE_5.small_Impel_R__set.set_0 -=change_num;
				ENGINE_LOVE_5.small_Impel_L__set.set_0 +=change_num;
			}
		}
		else if(ENGINE_LOVE_5.small_Impel_L__set.set_0<-max&&ENGINE_LOVE_5.small_Impel_R__set.set_0>max)
		{
			ENGINE_LOVE_5.small_Impel_R__set.set_0= max;			
			ENGINE_LOVE_5.small_Impel_L__set.set_0=-max;
		}
		else if(ENGINE_LOVE_5.small_Impel_L__set.set_0>-min&&ENGINE_LOVE_5.small_Impel_R__set.set_0<min)
		{
			ENGINE_LOVE_5.small_Impel_R__set.set_0= min;				
			ENGINE_LOVE_5.small_Impel_L__set.set_0=-min;
		}
//		ENGINE_LOVE_5.small_Impel_R__set.set_0 = _r_set;			
//		ENGINE_LOVE_5.small_Impel_L__set.set_0 = _l_set;		
	}

}


void ENGINE_small_Impel_drive_1(int altitude,int delay_time_ms,float change_num)
{
	static uint32_t last_time =0;	
//	static float _r_set=0,_l_set=0;	
	const int max=580;  const int min=0;		
  if (Get_sys_time_ms() - last_time > delay_time_ms)
  {
			last_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.small_Impel_L__set.set_1>=-max&&ENGINE_LOVE_5.small_Impel_L__set.set_1<=-min&&ENGINE_LOVE_5.small_Impel_R__set.set_1<=max&&ENGINE_LOVE_5.small_Impel_R__set.set_1>=min)
		{
			if(altitude > 0&&ENGINE_LOVE_5.small_Impel_L__set.set_1!=-max&&ENGINE_LOVE_5.small_Impel_R__set.set_1!=max)
			{
				ENGINE_LOVE_5.small_Impel_R__set.set_1 +=change_num;				
				ENGINE_LOVE_5.small_Impel_L__set.set_1 -=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.small_Impel_L__set.set_1!=-min&&ENGINE_LOVE_5.small_Impel_R__set.set_1!=min)
			{
				ENGINE_LOVE_5.small_Impel_R__set.set_1 -=change_num;
				ENGINE_LOVE_5.small_Impel_L__set.set_1 +=change_num;
			}
		}
		else if(ENGINE_LOVE_5.small_Impel_L__set.set_1<-max&&ENGINE_LOVE_5.small_Impel_R__set.set_1>max)
		{
			ENGINE_LOVE_5.small_Impel_R__set.set_1=max;			
			ENGINE_LOVE_5.small_Impel_L__set.set_1=-max;
		}
		else if(ENGINE_LOVE_5.small_Impel_L__set.set_1>-min&&ENGINE_LOVE_5.small_Impel_R__set.set_1<min)
		{
			ENGINE_LOVE_5.small_Impel_R__set.set_1=min;				
			ENGINE_LOVE_5.small_Impel_L__set.set_1=-min;
		}
//		ENGINE_LOVE_5.small_Impel_R__set.set_1 = _r_set;			
//		ENGINE_LOVE_5.small_Impel_L__set.set_1 = _l_set;		
	}

}







//void ENGINE_Traverse_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *Traverse_set)
//{
//	static uint32_t last_time =0;
//	
//  if (Get_sys_time_ms() - last_time > delay_time_ms)
//  {
//		last_time = Get_sys_time_ms();
//		if(*Traverse_set<=max&&*Traverse_set>=min)
//		{
//			if(altitude > 0&&*Traverse_set!=max)
//			{
//				*Traverse_set +=change_num;
//			}
//			if(altitude < 0&&*Traverse_set!=min)
//			{
//				*Traverse_set -=change_num;
//			}
//		}
//		else if(*Traverse_set>max)
//		{
//			*Traverse_set=max;
//		}
//		else if(*Traverse_set<min)
//		{
//			*Traverse_set=min;	
//		}
//			ENGINE_LOVE_5.Traverse_set.set_0 = *Traverse_set;
//	}
//}



void ENGINE_Traverse_drive(int altitude,int delay_time_ms,float change_num,int min,int max)
{
	static uint32_t last_time =0;
	
  if (Get_sys_time_ms() - last_time > delay_time_ms)
  {
		last_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.Traverse_set.set_0<=max&&ENGINE_LOVE_5.Traverse_set.set_0>=min)
		{
			if(altitude > 0&&ENGINE_LOVE_5.Traverse_set.set_0!=max)
			{
				ENGINE_LOVE_5.Traverse_set.set_0 +=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.Traverse_set.set_0!=min)
			{
				ENGINE_LOVE_5.Traverse_set.set_0 -=change_num;
			}
		}
		else if(ENGINE_LOVE_5.Traverse_set.set_0>max)
		{
			ENGINE_LOVE_5.Traverse_set.set_0=max;
		}
		else if(ENGINE_LOVE_5.Traverse_set.set_0<min)
		{
			ENGINE_LOVE_5.Traverse_set.set_0=min;	
		}
//			ENGINE_LOVE_5.Traverse_set.set_0 = *Traverse_set;
	}
}



//void ENGINE_Roll_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *roll_set)
//{
//	static uint32_t last_time =0;
//  if (Get_sys_time_ms() - last_time > delay_time_ms)
//  {
//		last_time = Get_sys_time_ms();
//		if(*roll_set<=max&&*roll_set>=min)
//		{
//			if(altitude > 0&&*roll_set!=max)
//			{
//				*roll_set +=change_num;
//			}
//			if(altitude < 0&&*roll_set!=min)
//			{
//				*roll_set -=change_num;
//			}
//		}
//		else if(*roll_set>max)
//		{
//			*roll_set=max;
//		}
//		else if(*roll_set<min)
//		{
//			*roll_set=min;	
//		}
//			ENGINE_LOVE_5.Roll_set.set_0 = *roll_set;	
//	}
//}


void ENGINE_Roll_drive(int altitude,int delay_time_ms,float change_num,int min,int max)
{
	static uint32_t last_time =0;
  if (Get_sys_time_ms() - last_time > delay_time_ms)
  {
		last_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.Roll_set.set_0<=max&&ENGINE_LOVE_5.Roll_set.set_0>=min)
		{
			if(altitude > 0&&ENGINE_LOVE_5.Roll_set.set_0!=max)
			{
				ENGINE_LOVE_5.Roll_set.set_0 +=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.Roll_set.set_0!=min)
			{
				ENGINE_LOVE_5.Roll_set.set_0 -=change_num;
			}
		}
		else if(ENGINE_LOVE_5.Roll_set.set_0>max)
		{
			ENGINE_LOVE_5.Roll_set.set_0=max;
		}
		else if(ENGINE_LOVE_5.Roll_set.set_0<min)
		{
			ENGINE_LOVE_5.Roll_set.set_0=min;	
		}
//			ENGINE_LOVE_5.Roll_set.set_0 = *roll_set;	
	}
}




//void ENGINE_Pitch_Root_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *pitch_root_set)
//{
//	static uint32_t last_time =0;
//	
//  if (Get_sys_time_ms() - last_time > delay_time_ms)
//  {
//		last_time = Get_sys_time_ms();
//		if(*pitch_root_set<=max&&*pitch_root_set>=min)
//		{
//			if(altitude > 0&&*pitch_root_set!=max)
//			{
//				*pitch_root_set +=change_num;
//			}
//			if(altitude < 0&&*pitch_root_set!=min)
//			{
//				*pitch_root_set -=change_num;
//			}
//		}
//		else if(*pitch_root_set>max)
//		{
//			*pitch_root_set=max;
//		}
//		else if(*pitch_root_set<min)
//		{
//			*pitch_root_set=min;	
//		}
//			ENGINE_LOVE_5.Pitch_Root_set.set_0 = *pitch_root_set;	
//	}
//}


void ENGINE_Pitch_Root_drive(int altitude,int delay_time_ms,float change_num,int min,int max)
{
	static uint32_t last_time =0;
	
  if (Get_sys_time_ms() - last_time > delay_time_ms)
  {
		last_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.Pitch_Root_set.set_0<=max&&ENGINE_LOVE_5.Pitch_Root_set.set_0>=min)
		{
			if(altitude > 0&&ENGINE_LOVE_5.Pitch_Root_set.set_0!=max)
			{
				ENGINE_LOVE_5.Pitch_Root_set.set_0 +=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.Pitch_Root_set.set_0!=min)
			{
				ENGINE_LOVE_5.Pitch_Root_set.set_0 -=change_num;
			}
		}
		else if(ENGINE_LOVE_5.Pitch_Root_set.set_0>max)
		{
			ENGINE_LOVE_5.Pitch_Root_set.set_0=max;
		}
		else if(ENGINE_LOVE_5.Pitch_Root_set.set_0<min)
		{
			ENGINE_LOVE_5.Pitch_Root_set.set_0=min;	
		}
//			ENGINE_LOVE_5.Pitch_Root_set.set_0 = *pitch_root_set;	
	}
}



//void ENGINE_END_pitch_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *l_set,float *r_set)
//{
//	static uint32_t last_time =0;
//	
//  if (Get_sys_time_ms() - last_time > delay_time_ms)
//  {
//		last_time = Get_sys_time_ms();
//		if(*l_set>=-max&&*l_set<=-min&&*r_set<=max&&*r_set>=min)
//		{
//			if(altitude > 0&&*l_set!=-max&&*r_set!=max)
//			{
//				*l_set -=change_num;
//				*r_set +=change_num;
//			}
//			if(altitude < 0&&*l_set!=-min&&*r_set!=min)
//			{
//				*l_set +=change_num;
//				*r_set -=change_num;
//			}
//		}
//		else if(*l_set<-max&&*r_set>max)
//		{
//			*l_set=-max;
//			*r_set=max;
//		}
//		else if(*l_set>-min&&*r_set<min)
//		{
//			*l_set=-min;
//			*r_set=min;	
//		}
//		
//			ENGINE_LOVE_5.End_L_set.set_a_0 = *l_set;		
//			ENGINE_LOVE_5.End_R_set.set_a_0 = *r_set;			
//	}

//}


void ENGINE_END_pitch_drive(int altitude,int delay_time_ms,float change_num,int min,int max)
{
	static uint32_t last_time =0;
	
  if (Get_sys_time_ms() - last_time > delay_time_ms)
  {
		last_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.End_L_set.set_a_0>=-max&&ENGINE_LOVE_5.End_L_set.set_a_0<=-min&&ENGINE_LOVE_5.End_R_set.set_a_0<=max&&ENGINE_LOVE_5.End_R_set.set_a_0>=min)
		{
			if(altitude > 0&&ENGINE_LOVE_5.End_L_set.set_a_0!=-max&&ENGINE_LOVE_5.End_R_set.set_a_0!=max)
			{
				ENGINE_LOVE_5.End_L_set.set_a_0 -=change_num;
				ENGINE_LOVE_5.End_R_set.set_a_0 +=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.End_L_set.set_a_0!=-min&&ENGINE_LOVE_5.End_R_set.set_a_0!=min)
			{
				ENGINE_LOVE_5.End_L_set.set_a_0 +=change_num;
				ENGINE_LOVE_5.End_R_set.set_a_0 -=change_num;
			}
		}
		else if(ENGINE_LOVE_5.End_L_set.set_a_0<-max&&ENGINE_LOVE_5.End_R_set.set_a_0>max)
		{
			ENGINE_LOVE_5.End_L_set.set_a_0=-max;
			ENGINE_LOVE_5.End_R_set.set_a_0=max;
		}
		else if(ENGINE_LOVE_5.End_L_set.set_a_0>-min&&ENGINE_LOVE_5.End_R_set.set_a_0<min)
		{
			ENGINE_LOVE_5.End_L_set.set_a_0=-min;
			ENGINE_LOVE_5.End_R_set.set_a_0=min;	
		}
		
//			ENGINE_LOVE_5.End_L_set.set_a_0 = *l_set;		
//			ENGINE_LOVE_5.End_R_set.set_a_0 = *r_set;			
	}

}


//void ENGINE_END_roll_drive(int altitude,int delay_time_ms,float change_num,int min,int max,float *l_set,float *r_set)
//{
//	static uint32_t last_gimbal_pitch_anti_time =0;
//  if (Get_sys_time_ms() - last_gimbal_pitch_anti_time > delay_time_ms)
//  {
//		last_gimbal_pitch_anti_time = Get_sys_time_ms();
//		if(*l_set>=min&&*l_set<=max&&*r_set>=min&&*r_set<=max)
//		{
//			if(altitude > 0&&*l_set!=max&&*r_set!=max)
//			{
//				*l_set +=change_num;
//				*r_set +=change_num;
//			}
//			if(altitude < 0&&*l_set!=min&&*r_set!=min)
//			{
//				*l_set -=change_num;
//				*r_set -=change_num;
//			}						
//		}
//		else if(*l_set>max&&*r_set>max)
//		{
//			*l_set = max;
//			*r_set = max;
//		}
//		else if(*l_set < min&&*r_set<min)
//		{
//			*l_set = min;
//			*r_set = min;
//		}		
//			ENGINE_LOVE_5.End_L_set.set_b_0 = *l_set;		
//			ENGINE_LOVE_5.End_R_set.set_b_0 = *r_set;			
//	 }
//}

void ENGINE_END_roll_drive(int altitude,int delay_time_ms,float change_num,int min,int max)
{
	static uint32_t last_gimbal_pitch_anti_time =0;
  if (Get_sys_time_ms() - last_gimbal_pitch_anti_time > delay_time_ms)
  {
		last_gimbal_pitch_anti_time = Get_sys_time_ms();
		if(ENGINE_LOVE_5.End_L_set.set_b_0>=min&&ENGINE_LOVE_5.End_L_set.set_b_0<=max&&ENGINE_LOVE_5.End_R_set.set_b_0>=min&&ENGINE_LOVE_5.End_R_set.set_b_0<=max)
		{
			if(altitude > 0&&ENGINE_LOVE_5.End_L_set.set_b_0!=max&&ENGINE_LOVE_5.End_R_set.set_b_0!=max)
			{
				ENGINE_LOVE_5.End_L_set.set_b_0 +=change_num;
				ENGINE_LOVE_5.End_R_set.set_b_0 +=change_num;
			}
			if(altitude < 0&&ENGINE_LOVE_5.End_L_set.set_b_0!=min&&ENGINE_LOVE_5.End_R_set.set_b_0!=min)
			{
				ENGINE_LOVE_5.End_L_set.set_b_0 -=change_num;
				ENGINE_LOVE_5.End_R_set.set_b_0 -=change_num;
			}						
		}
		else if(ENGINE_LOVE_5.End_L_set.set_b_0>max&&ENGINE_LOVE_5.End_R_set.set_b_0>max)
		{
			ENGINE_LOVE_5.End_L_set.set_b_0 = max;
			ENGINE_LOVE_5.End_R_set.set_b_0 = max;
		}
		else if(ENGINE_LOVE_5.End_L_set.set_b_0 < min&&ENGINE_LOVE_5.End_R_set.set_b_0<min)
		{
			ENGINE_LOVE_5.End_L_set.set_b_0 = min;
			ENGINE_LOVE_5.End_R_set.set_b_0 = min;
		}		
//			ENGINE_LOVE_5.End_L_set.set_b_0 = *l_set;		
//			ENGINE_LOVE_5.End_R_set.set_b_0 = *r_set;			
	 }
}






void Automatic_return_to_zero(void)//一键归位 升降加50
{
		ENGINE_LOVE_5.Lifting_L__set.set_0 = -600;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  600;			
		osDelay(1200);				

		ENGINE_LOVE_5.Roll_set.set_0 = 0;
		osDelay(800);	

		ENGINE_LOVE_5.Pitch_Root_set.set_0 = 0;
		osDelay(800);

		ENGINE_LOVE_5.Impel_L__set.set_0 =  0;			
		ENGINE_LOVE_5.Impel_R__set.set_0 =  0;

		ENGINE_LOVE_5.small_Impel_R__set.set_0= 0;			
		ENGINE_LOVE_5.small_Impel_L__set.set_0= 0;		

		osDelay(1200);	

		ENGINE_LOVE_5.End_L_set.set_a_0 = 0;
		ENGINE_LOVE_5.End_R_set.set_a_0 = 0;					
		ENGINE_LOVE_5.End_L_set.set_b_0 = 0;					
		ENGINE_LOVE_5.End_R_set.set_b_0 = 0;			
		osDelay(800);

		ENGINE_LOVE_5.Traverse_set.set_0 = 0; 
		osDelay(500);

		ENGINE_LOVE_5.Lifting_L__set.set_0 = -50;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  50;	
		osDelay(1500);	

		Global.PID_mode = PID_NORMAL;	
		Global.BOOM_mode = BOOM_OFF;				
}


void Automatic_return_to_second_zero(void)//一键归第二零点
{
		ENGINE_LOVE_5.Lifting_L__set.set_0 = -600;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  600;			
		osDelay(1200);				

		ENGINE_LOVE_5.Roll_set.set_0 = 0;
		osDelay(800);	

		ENGINE_LOVE_5.Pitch_Root_set.set_0 = 173;
			osDelay(800);

		ENGINE_LOVE_5.Impel_L__set.set_0 =  700;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = -700;


		ENGINE_LOVE_5.small_Impel_R__set.set_0= 0;			
		ENGINE_LOVE_5.small_Impel_L__set.set_0= 0;		
		osDelay(1200);	

		ENGINE_LOVE_5.End_L_set.set_a_0 = 0;
		ENGINE_LOVE_5.End_R_set.set_a_0 = 0;					
		ENGINE_LOVE_5.End_L_set.set_b_0 = 0;					
		ENGINE_LOVE_5.End_R_set.set_b_0 = 0;			
		osDelay(800);

		ENGINE_LOVE_5.Traverse_set.set_0 = 0; 
		osDelay(500);

		ENGINE_LOVE_5.Lifting_L__set.set_0 = -340;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  340;	
		osDelay(1500);	

		Global.PID_mode = PID_NORMAL;			
		Global.BOOM_mode = BOOM_ON;				
}


void Automatic_grabbing_silver_mineral(void)//一键调整到抓取银矿的姿态 
{
		ENGINE_LOVE_5.Lifting_L__set.set_0 = -600;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  600;			
		osDelay(1200);				

		ENGINE_LOVE_5.Roll_set.set_0 = 0;
		osDelay(800);	

		ENGINE_LOVE_5.Pitch_Root_set.set_0 = 169;
		osDelay(800);

		ENGINE_LOVE_5.Impel_L__set.set_0 = 0;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = 0;
		osDelay(1200);	

		ENGINE_LOVE_5.End_L_set.set_a_0 = 0;
		ENGINE_LOVE_5.End_R_set.set_a_0 = 0;					
		ENGINE_LOVE_5.End_L_set.set_b_0 = 0;					
		ENGINE_LOVE_5.End_R_set.set_b_0 = 0;			
		osDelay(800);

		ENGINE_LOVE_5.Traverse_set.set_0 = 0; 
		osDelay(500);

		ENGINE_LOVE_5.Lifting_L__set.set_0 = -512;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  512;	
		osDelay(1500);	

		Global.PID_mode = PID_NORMAL;	
		Global.BOOM_mode = BOOM_ON;				
	
}


void Automatic_grabbing_3_silver_mineral(void)//一键调整到抓取3银矿的姿态   //-512   512
{
		ENGINE_LOVE_5.Lifting_L__set.set_0 = -600;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  600;			
		osDelay(1200);				

		ENGINE_LOVE_5.Roll_set.set_0 = 0;
		osDelay(800);	

		ENGINE_LOVE_5.Pitch_Root_set.set_0 = 169;
		osDelay(800);

		ENGINE_LOVE_5.Impel_L__set.set_0 = 0;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = 0;
		
		ENGINE_LOVE_5.small_Impel_R__set.set_0= 1500;			
		ENGINE_LOVE_5.small_Impel_L__set.set_0=-1500;		

		osDelay(1200);	

		ENGINE_LOVE_5.End_L_set.set_a_0 = 0;
		ENGINE_LOVE_5.End_R_set.set_a_0 = 0;					
		ENGINE_LOVE_5.End_L_set.set_b_0 = 0;					
		ENGINE_LOVE_5.End_R_set.set_b_0 = 0;			
		osDelay(800);

		ENGINE_LOVE_5.Traverse_set.set_0 = 0; 
		osDelay(500);

		ENGINE_LOVE_5.Lifting_L__set.set_0 = -512;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  512;	
		osDelay(1500);	

		Global.PID_mode = PID_NORMAL;	
		Global.BOOM_mode = BOOM_ON;				
}



void Automatic_grabbing_gold_mineral(void)//一键调整到抓取金矿的姿态
{
		ENGINE_LOVE_5.Lifting_L__set.set_0 = -600;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  600;			
		osDelay(1200);				

		ENGINE_LOVE_5.Roll_set.set_0 = 0;
		osDelay(800);	

		ENGINE_LOVE_5.Pitch_Root_set.set_0 = 173;
		osDelay(800);

		ENGINE_LOVE_5.Impel_L__set.set_0 =  1125;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = -1125;
		osDelay(1200);	

		ENGINE_LOVE_5.End_L_set.set_a_0 = 0;
		ENGINE_LOVE_5.End_R_set.set_a_0 = 0;					
		ENGINE_LOVE_5.End_L_set.set_b_0 = 0;					
		ENGINE_LOVE_5.End_R_set.set_b_0 = 0;			
		osDelay(800);

		ENGINE_LOVE_5.Traverse_set.set_0 = 0; 
		osDelay(500);

		ENGINE_LOVE_5.Lifting_L__set.set_0 = -128;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  128;	
		osDelay(1500);	

		Global.PID_mode = PID_NORMAL;	
		Global.BOOM_mode = BOOM_ON;			
}


void Automatic_grabbing_ground_mineral(void)//一键调整到抓取地面矿的姿态
{
		ENGINE_LOVE_5.Lifting_L__set.set_0 = -740;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  740;			
		osDelay(1200);				

		ENGINE_LOVE_5.Impel_L__set.set_0 =  1180;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = -1180;
		osDelay(1200);		

		ENGINE_LOVE_5.Roll_set.set_0 = 0;
		osDelay(800);	

		ENGINE_LOVE_5.Pitch_Root_set.set_0 = 83;
		osDelay(800);	

		ENGINE_LOVE_5.End_L_set.set_a_0 = 0;
		ENGINE_LOVE_5.End_R_set.set_a_0 = 0;					
		ENGINE_LOVE_5.End_L_set.set_b_0 = 0;					
		ENGINE_LOVE_5.End_R_set.set_b_0 = 0;			
		osDelay(800);

		ENGINE_LOVE_5.Traverse_set.set_0 = 0; 
		osDelay(500);

		ENGINE_LOVE_5.Lifting_L__set.set_0 = -310;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  310;	
		osDelay(1500);	

		Global.PID_mode = PID_NORMAL;	
		Global.BOOM_mode = BOOM_ON;		
}	


void Automatic_fetch_Ore_reserves(void)//一键存矿
{
		ENGINE_LOVE_5.Lifting_L__set.set_0 = -800;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  800;			
		osDelay(1200);				

		ENGINE_LOVE_5.Impel_L__set.set_0 =  1580;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = -1580;

		ENGINE_LOVE_5.small_Impel_R__set.set_0= 0;			
		ENGINE_LOVE_5.small_Impel_L__set.set_0= 0;		
		osDelay(1200);						


		ENGINE_LOVE_5.Roll_set.set_0 = 0;
		osDelay(800);

		ENGINE_LOVE_5.Pitch_Root_set.set_0 = 37;
		osDelay(800);


		ENGINE_LOVE_5.End_L_set.set_a_0 = 80;
		ENGINE_LOVE_5.End_R_set.set_a_0 = -80;					
		ENGINE_LOVE_5.End_L_set.set_b_0 = 0;					
		ENGINE_LOVE_5.End_R_set.set_b_0 = 0;			
		osDelay(800);

		ENGINE_LOVE_5.Traverse_set.set_0 = 0; 
		osDelay(500);

		ENGINE_LOVE_5.Impel_L__set.set_0 =  370;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = -370;
		osDelay(1800);//原先是1200，需延长

		ENGINE_LOVE_5.Lifting_L__set.set_0 = -204;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  204;	
		osDelay(1500);		

		Global.PID_mode = PID_NORMAL;		
//			Global.BOOM_mode = BOOM_ON;			
}


void Automatic_fetch_Ore_reserves_2(void)//一键取矿
{
		ENGINE_LOVE_5.Lifting_L__set.set_0 = -800;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  800;			
		osDelay(1200);				

		ENGINE_LOVE_5.Impel_L__set.set_0 =  1580;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = -1580;
		osDelay(1200);						

		ENGINE_LOVE_5.Roll_set.set_0 = 0;
		osDelay(800);

		ENGINE_LOVE_5.Pitch_Root_set.set_0 = 40;
		osDelay(800);

		ENGINE_LOVE_5.End_L_set.set_a_0 = 80;
		ENGINE_LOVE_5.End_R_set.set_a_0 = -80;					
		ENGINE_LOVE_5.End_L_set.set_b_0 = 0;					
		ENGINE_LOVE_5.End_R_set.set_b_0 = 0;			
		osDelay(800);

		ENGINE_LOVE_5.Traverse_set.set_0 = 0; 
		osDelay(500);

		ENGINE_LOVE_5.Impel_L__set.set_0 =  725;			
		ENGINE_LOVE_5.Impel_R__set.set_0 = -725;
		osDelay(1800);////原先是1200，需延长

		ENGINE_LOVE_5.Lifting_L__set.set_0 = -204;
		ENGINE_LOVE_5.Lifting_R__set.set_0 =  204;	
		osDelay(1500);		

		Global.PID_mode = PID_NORMAL;	
		Global.BOOM_mode = BOOM_ON;			
}


