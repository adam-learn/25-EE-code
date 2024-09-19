/**
 * @file gimbal.h
 * @author sethome
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __GIMBAL_H__
#define __GIMBAL_H__


#include "cover_headerfile_h.h"

//��̨�������
#define PITCH_MOTOR CAN_2_6
#define YAW_MOTOR CAN_2_5


enum gimbal_status_e
{
    LOCATION = 0,
    SPEED,
    zero_force,
};

struct gimbal_status
{				
		struct
    {
			enum gimbal_status_e pitch_status;			
			float set, now, last, offset;
			float set_pitch_speed,pitch_speed;
			pid_t pitch_location_pid;				
			pid_t pitch_speed_pid;	
    } pitch;
    struct
    {
			enum gimbal_status_e yaw_status;			
			float set, now, last, offset;
			float set_yaw_speed,yaw_speed;			
			pid_t yaw_location_pid;	
			pid_t yaw_speed_pid;
    } yaw;
};
extern struct gimbal_status gimbal;

//�ⲿ����
void gimbal_init(void);                         //��ʼ����̨
void gimbal_set_offset(float pitch, float yaw); //��ʼ�����

void gimbal_set(float pitch, float yaw); //���ýǶ�
void gimbal_set_pitch(float pitch);      //�趨picth�Ƕ�

void gimbal_set_speed(float pitch, float yaw); //�趨�ٶ�
void gimbal_set_yaw_speed(float yaw);          //�趨yaw�ٶ�

void gimbal_pid_cal(void); //��̨PID����
void gimbal_updata(void);  //������̨����
void gimbal_clear_cnt(void);

// end of file

#endif



