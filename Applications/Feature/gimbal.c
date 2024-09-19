/**
 * @file gimbal.c
 * @author sethome
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "cover_headerfile_h.h" 
#include "gimbal.h"


struct gimbal_status gimbal;

//云台初始化
void gimbal_init(void)
{
  pid_set(&gimbal.pitch.pitch_speed_pid, 4500.0f, 0.0, 2250.0f, 30000.0f, 20000.0f); //4500   2250  7500 0 2500
	pid_set(&gimbal.pitch.pitch_location_pid, 20.0f, 0.0f,0.0f, 8000.0f, 0.01f);//20	  25 
		
	pid_set(&gimbal.yaw.yaw_speed_pid, 50, 0, 3000.0, 25000.0f, 3600.0f);//50  3000
  pid_set(&gimbal.yaw.yaw_location_pid, 27, 0, 120, 8000.0f, 0.0f);		//25
	
  gimbal.pitch.now = 0;
  gimbal.pitch.set = 0;
//  gimbal.pitch.offset = 0;
  gimbal.pitch.set_pitch_speed = 0;

  gimbal.yaw.now = 0;
  gimbal.yaw.set = 0;
//  gimbal.yaw.offset = 0;
  gimbal.yaw.set_yaw_speed = 0;
	
  gimbal.yaw.yaw_status = gimbal.pitch.pitch_status = LOCATION; // 默认为位置控制模式
}


void gimbal_set_offset(float pitch, float yaw)
{
  gimbal.pitch.offset = pitch;
  gimbal.yaw.offset = yaw;
}

void gimbal_updata(void)
{
  // 从陀螺仪或电机获取数据
	
  // yaw轴更新
  decode_as_6020(YAW_MOTOR);
	gimbal.yaw.now = rad2degree(IMU_data.AHRS.yaw_rad_cnt);	
	gimbal.yaw.yaw_speed = (get_motor_data(YAW_MOTOR).ecd - get_motor_data(YAW_MOTOR).last_ecd) / ECD_MAX;

  // pitch轴更新
  decode_as_6020(PITCH_MOTOR);
  gimbal.pitch.now = degree2rad(get_motor_data(PITCH_MOTOR).angle - gimbal.pitch.offset); // 角度转为弧度
  gimbal.pitch.pitch_speed = IMU_data.gyro[1]; //获取y转轴（对应pitch轴）角速度，做闭环用。	
}

// 设定角度
void gimbal_set(float pitch, float yaw)
{
  gimbal.yaw.yaw_status = gimbal.pitch.pitch_status = LOCATION; // 以位置模式控制

//  // 范围限定 防止超出机械限位
//  if (fabs(pitch) < 15)
    gimbal.pitch.set = pitch;
  gimbal.yaw.set = yaw;
}

void gimbal_set_pitch(float pitch)
{
  gimbal.pitch.pitch_status = LOCATION; // 以位置模式控制

  if (fabs(pitch) < 20)
    gimbal.pitch.set = pitch;
}

// 设定速度
void gimbal_set_speed(float pitch, float yaw)
{
  gimbal.yaw.yaw_status = gimbal.pitch.pitch_status = SPEED; // 以速度模式控制

  gimbal.pitch.set_pitch_speed = pitch;
  gimbal.yaw.set_yaw_speed = yaw;
}
void gimbal_set_yaw_speed(float yaw)
{
  gimbal.yaw.yaw_status = SPEED; // 以速度模式控制

  gimbal.yaw.set_yaw_speed = yaw;
}

void gimbal_pid_cal(void)
{
  // 位置环 （位置控制模式下）
  if (gimbal.yaw.yaw_status == LOCATION)
  {
			gimbal.yaw.set_yaw_speed = pid_cal(&gimbal.yaw.yaw_location_pid, gimbal.yaw.now, gimbal.yaw.set);
  }
  else
    gimbal.yaw.set_yaw_speed = gimbal.yaw.yaw_speed;


  if (gimbal.pitch.pitch_status == LOCATION)
  {
    gimbal.pitch.set_pitch_speed = pid_cal(&gimbal.pitch.pitch_location_pid, gimbal.pitch.now, gimbal.pitch.set);
  }
  else
    gimbal.pitch.set_pitch_speed=gimbal.pitch.pitch_speed;

    
  // 速度环
		if(robot_status.power_management_gimbal_output==1&&Global.mode==NORMAL) //	 if(Global.mode==NORMAL)
		{
			set_motor(pid_cal(&gimbal.yaw.yaw_speed_pid, gimbal.yaw.yaw_speed, gimbal.yaw.set_yaw_speed), YAW_MOTOR);
			set_motor(pid_cal(&gimbal.pitch.pitch_speed_pid, gimbal.pitch.pitch_speed, gimbal.pitch.set_pitch_speed), PITCH_MOTOR);
		}
		else if(robot_status.power_management_gimbal_output==0||Global.mode==LOCK) //		else if(Global.mode==LOCK)
		{
			set_motor(0, YAW_MOTOR);
			set_motor(0, PITCH_MOTOR);							
		}

}

void gimbal_clear_cnt(void)
{
  clear_motor_cnt(YAW_MOTOR);
}
