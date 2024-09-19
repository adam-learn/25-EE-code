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

//��̨��ʼ��
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
	
  gimbal.yaw.yaw_status = gimbal.pitch.pitch_status = LOCATION; // Ĭ��Ϊλ�ÿ���ģʽ
}


void gimbal_set_offset(float pitch, float yaw)
{
  gimbal.pitch.offset = pitch;
  gimbal.yaw.offset = yaw;
}

void gimbal_updata(void)
{
  // �������ǻ�����ȡ����
	
  // yaw�����
  decode_as_6020(YAW_MOTOR);
	gimbal.yaw.now = rad2degree(IMU_data.AHRS.yaw_rad_cnt);	
	gimbal.yaw.yaw_speed = (get_motor_data(YAW_MOTOR).ecd - get_motor_data(YAW_MOTOR).last_ecd) / ECD_MAX;

  // pitch�����
  decode_as_6020(PITCH_MOTOR);
  gimbal.pitch.now = degree2rad(get_motor_data(PITCH_MOTOR).angle - gimbal.pitch.offset); // �Ƕ�תΪ����
  gimbal.pitch.pitch_speed = IMU_data.gyro[1]; //��ȡyת�ᣨ��Ӧpitch�ᣩ���ٶȣ����ջ��á�	
}

// �趨�Ƕ�
void gimbal_set(float pitch, float yaw)
{
  gimbal.yaw.yaw_status = gimbal.pitch.pitch_status = LOCATION; // ��λ��ģʽ����

//  // ��Χ�޶� ��ֹ������е��λ
//  if (fabs(pitch) < 15)
    gimbal.pitch.set = pitch;
  gimbal.yaw.set = yaw;
}

void gimbal_set_pitch(float pitch)
{
  gimbal.pitch.pitch_status = LOCATION; // ��λ��ģʽ����

  if (fabs(pitch) < 20)
    gimbal.pitch.set = pitch;
}

// �趨�ٶ�
void gimbal_set_speed(float pitch, float yaw)
{
  gimbal.yaw.yaw_status = gimbal.pitch.pitch_status = SPEED; // ���ٶ�ģʽ����

  gimbal.pitch.set_pitch_speed = pitch;
  gimbal.yaw.set_yaw_speed = yaw;
}
void gimbal_set_yaw_speed(float yaw)
{
  gimbal.yaw.yaw_status = SPEED; // ���ٶ�ģʽ����

  gimbal.yaw.set_yaw_speed = yaw;
}

void gimbal_pid_cal(void)
{
  // λ�û� ��λ�ÿ���ģʽ�£�
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

    
  // �ٶȻ�
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
