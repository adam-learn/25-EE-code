/**
 * @file shoot.h
 * @author sethome
 * @brief 发射模块
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __SHOOT_H__
#define __SHOOT_H__

#include "cover_headerfile_h.h"

#define FULL_BULLETS 250
#define SHOOT_MOTOR1 CAN_2_2
#define SHOOT_MOTOR2 CAN_2_4
#define TRIGGER_MOTOR CAN_2_7
#define A_BULLET_ANGEL 42

enum shoot_speed // 发射机构速度，此处为步兵定制
{
		SHOOT_BEGIN = 5000,
    SHOOT_STOP = 0,
    SHOOT_30 =-8100, //27.5
};

enum trigger_status_e // 拨弹轮控制模式
{
    LOCATIONS = 0,
    SPEEDS,
};

typedef struct
{	
	pid_t trigger_speed_pid;
	pid_t trigger_location_pid;

	pid_t shoot1_speed_pid;
	pid_t shoot2_speed_pid;
   /* data */
	enum shoot_speed speed_level;
	float shoot_speed[2]; // 摩擦轮速度
	enum trigger_status_e trigger_status;
	float trigger_speed; // 拨弹电机速度	
	int remainingBullets;		
	struct
	{/* data */
		float now;
		float set;
		float off_set;
	}trigger_location; // 拨弹电机位置
	
  float set_trigger_speed;
  float trigger_given_current; 		
}	shoot_t;

extern shoot_t shoot;

// 外部调用
void shoot_init(void);    // 初始化

void shoot_update(void);  // 更新拨弹电机速度等

void shoot_pid_cal(void); // 计算pid

void shoot_speed_limit(void);//依据裁判系统更新速度限幅

void trigger_anti_kill_and_set_speed(float set);

void shoot_trigger_online(void);//PC操作

void shoot_set_trigger_location(int n);

int shoot_Bullets(int n); // 发射N颗子弹

void shoot_set_back(void);

void shoot_reload(void);  // 子弹重新计数


#endif




// end of file
