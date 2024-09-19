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

//云台电机数据
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

//外部调用
void gimbal_init(void);                         //初始化云台
void gimbal_set_offset(float pitch, float yaw); //初始化零点

void gimbal_set(float pitch, float yaw); //设置角度
void gimbal_set_pitch(float pitch);      //设定picth角度

void gimbal_set_speed(float pitch, float yaw); //设定速度
void gimbal_set_yaw_speed(float yaw);          //设定yaw速度

void gimbal_pid_cal(void); //云台PID计算
void gimbal_updata(void);  //更新云台数据
void gimbal_clear_cnt(void);

// end of file

#endif



