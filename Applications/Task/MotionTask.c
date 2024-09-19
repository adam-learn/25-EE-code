#include "cover_headerfile_h.h"
#include "MotionTask.h"

MotionTask_data_t MotionTask_data;

void LockModeTask(void)
{
	memset((void*)&Global.input,0,30);
}

void NormalModeTask(void)
{
	
}

void FlowModeTask(void)
{
		decode_as_6020(YAW_MOTOR);
		MotionTask_data.relative_angle = get_motor_data(YAW_MOTOR).angle_cnt - gimbal.yaw.offset;
		MotionTask_data.cos_beta = sinf(degree2rad(MotionTask_data.relative_angle)); // 输入弧度，输出对应的角度sin，cos对应值
		MotionTask_data.cos_beta = cosf(degree2rad(MotionTask_data.relative_angle));

		chassis.speed.vx = Global.input.x_s * MotionTask_data.cos_beta - MotionTask_data.sin_beta * Global.input.y_s; // 运动分解
		chassis.speed.vy = Global.input.x_s * MotionTask_data.sin_beta + Global.input.y_s * MotionTask_data.cos_beta;

		if (fabs(Global.input.pitch) > 0.0f)
			gimbal.pitch.set -= Global.input.pitch ;
	
		if (gimbal.pitch.set >= 0.52f) // 0.52上下限幅
			gimbal.pitch.set = 0.52f;
		else if (gimbal.pitch.set <= -0.52f) //-0.58
			gimbal.pitch.set = -0.52f;

		if (fabs(Global.input.yaw) > 0.0f)
			gimbal.yaw.set -= Global.input.yaw * 1.2f;

		
		MotionTask_data.mul = abs((int)MotionTask_data.relative_angle) / 180;
		if (MotionTask_data.relative_angle > 180.0f)
		{
			if (MotionTask_data.mul % 2 == 1) // 处于-180度
				MotionTask_data.relative_angle -= (MotionTask_data.mul + 1) * 180;
			else // 处于180度
				MotionTask_data.relative_angle -= MotionTask_data.mul * 180;
		}
		if (MotionTask_data.relative_angle < -180.0f)
		{
			if (MotionTask_data.mul % 2 == 1) // 处于180度
				MotionTask_data.relative_angle += (MotionTask_data.mul + 1) * 180;
			else // 处于-180度
				MotionTask_data.relative_angle += MotionTask_data.mul * 180;
		}
		if (fabs(MotionTask_data.relative_angle) > 0.05f) //
			chassis.speed.vw = pid_cal(&MotionTask_data.chassis_rapid, degree2rad(MotionTask_data.relative_angle), 0.0f);
		else
			chassis.speed.vw = 0.0;		
}	
	

void TankModeTask(void)
{
		chassis.speed.vx = Global.input.x_s;
		chassis.speed.vy = Global.input.y_s;

		if (fabs(Global.input.yaw) > 0.0f)
			gimbal.yaw.set -= Global.input.yaw * 4.0f;

		if (fabs(Global.input.pitch) > 0.0f)
			gimbal.pitch.set -= Global.input.pitch * 1.2f;

		if (gimbal.pitch.set >= 0.52f)
			gimbal.pitch.set = 0.52f;
		else if (gimbal.pitch.set <= -0.52f)
			gimbal.pitch.set = -0.52f;
}



void SpinModeTask(void)
{
		MotionTask_data.relative_angle = get_motor_data(YAW_MOTOR).angle_cnt - gimbal.yaw.offset + 22.5f;
		MotionTask_data.sin_beta = sinf(degree2rad(MotionTask_data.relative_angle)); // 输入弧度，输出对应的角度sin，cos对应值
		MotionTask_data.cos_beta = cosf(degree2rad(MotionTask_data.relative_angle));

		chassis.speed.vx  = Global.input.x_s * MotionTask_data.cos_beta - Global.input.y_s * MotionTask_data.sin_beta; // 运动分解
		chassis.speed.vy = Global.input.x_s * MotionTask_data.sin_beta + Global.input.y_s * MotionTask_data.cos_beta;
			
		if(REFEREE_DATA.Chassis_Power_Limit>= 40&&REFEREE_DATA.Chassis_Power_Limit< 60)
			chassis.speed.vw = 1.8f;
		else if(REFEREE_DATA.Chassis_Power_Limit>= 60&&REFEREE_DATA.Chassis_Power_Limit< 80)
			chassis.speed.vw = 2.1f; 
		else if(REFEREE_DATA.Chassis_Power_Limit>= 80&&REFEREE_DATA.Chassis_Power_Limit<= 150)
			chassis.speed.vw = 2.5f; 	
		else
			chassis.speed.vw = 1.8f;		
		
		if (Global.input.yaw > 0.0f)
			gimbal.yaw.set -= Global.input.yaw * 3.0f;
		else if (Global.input.yaw < 0.0f)
			gimbal.yaw.set -= Global.input.yaw * 3.0f;

		if (fabs(Global.input.pitch) > 0.0f)
			gimbal.pitch.set -= Global.input.pitch;

		if (gimbal.pitch.set >= 0.52f)
			gimbal.pitch.set = 0.52f;
		else if (gimbal.pitch.set <= -0.52f)
			gimbal.pitch.set = -0.52f;
}


void LeanModeTask(void)
{
		decode_as_6020(YAW_MOTOR);
		MotionTask_data.relative_angle = get_motor_data(YAW_MOTOR).angle_cnt - gimbal.yaw.offset + 45.0f;
		MotionTask_data.sin_beta = sinf(degree2rad(MotionTask_data.relative_angle - 45)); // 输入弧度，输出对应的角度sin，cos对应值
		MotionTask_data.cos_beta = cosf(degree2rad(MotionTask_data.relative_angle - 45));

		chassis.speed.vx = Global.input.x_s * MotionTask_data.cos_beta - MotionTask_data.sin_beta * Global.input.y_s; // 运动分解
		chassis.speed.vy = Global.input.x_s * MotionTask_data.sin_beta + Global.input.y_s * MotionTask_data.cos_beta;

		MotionTask_data.mul = abs((int)MotionTask_data.relative_angle) / 180;
		if (MotionTask_data.relative_angle > 180.0f)
		{
			if (MotionTask_data.mul % 2 == 1) // 处于-180度
				MotionTask_data.relative_angle -= (MotionTask_data.mul + 1) * 180;
			else // 处于180度
				MotionTask_data.relative_angle -= MotionTask_data.mul * 180;
		}
		if (MotionTask_data.relative_angle < -180.0f)
		{
			if (MotionTask_data.mul % 2 == 1) // 处于180度
				MotionTask_data.relative_angle += (MotionTask_data.mul + 1) * 180;
			else // 处于-180度
				MotionTask_data.relative_angle += MotionTask_data.mul * 180;
		}

		if (fabs(MotionTask_data.relative_angle) > 0.1f) //
			chassis.speed.vw = pid_cal(&MotionTask_data.chassis_rapid, degree2rad(MotionTask_data.relative_angle), 0.0f);
		else
			chassis.speed.vw = 0.0;

		
		if (fabs(Global.input.yaw) > 0.0f)
			gimbal.yaw.set -= Global.input.yaw / 2.0f;

		if (fabs(Global.input.pitch) > 0.0f)
			gimbal.pitch.set -= Global.input.pitch;

		if (gimbal.pitch.set >= 0.52f)
			gimbal.pitch.set = 0.52f;
		else if (gimbal.pitch.set <= -0.52f)
			gimbal.pitch.set = -0.52f;
	
}


void MotionTask_mode_choose(uint8_t status)
{
	// 底盘跟随PID
	pid_set(&MotionTask_data.chassis_rapid, 2.0, 0, 0, 8, 0);

	switch (status)
	 {
//		 case NORMAL:		 		
//			break;
//		 
//		 case LOCK:	 
//			break;
		 
		 case FLOW:
			FlowModeTask();
		break;
		 
		 case TANK:
			TankModeTask();
		break;		 

		 case SPIN:
			SpinModeTask();
		break;	

		 case LEAN:
			LeanModeTask();
		break;	

//		 default:	
//			break;			
	 }
	 
}





