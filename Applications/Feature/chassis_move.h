/**
 * @file chassis_move.h
 * @author sethome
 * @brief 底盘控制文件
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */
 

#ifndef __CHASSIS_MOVE_H__
#define __CHASSIS_MOVE_H__

#include "cover_headerfile_h.h" 


/* motorID 
				1 %++++++% 0
						++++
						++++
				2 %++++++% 3 
*/
				
#define chassis_FR CAN_1_1
#define chassis_FL CAN_1_2
#define chassis_BL CAN_1_3
#define chassis_BR CAN_1_4



struct chassis_status
{
	//马达速度环PID
	pid_t motor_speed[4];	
	int16_t wheel_rpm[4]; // 底盘速度数组
	int16_t wheel_current[4]; // PID输出的电调电流	
	
	struct
	{
		float vx, vy, vw;
		float now_x, now_y, now_w;
		float max_x, max_y, max_w; // m/s
	} speed;
	
//	struct
//	{
//		float now_x, now_y, now_w;
//		float max_x, max_y, max_w; // m/s^2
//	} acc;
	
	struct
	{
		float Plimit; // 等比系数
		float Power;
		uint16_t Engerny_buffer;
		float max_p;
		float max_c;
		double percentage;
		double now_p;
		float b;
		float e;
	
		float a;// 1.23e-07;	// k1
		float k2; // 1.453e-07; // k2
		float constant;
		float toque_coefficient;
	} power_limit;	
	
};
extern struct chassis_status chassis;


void chassis_move_init(void);//底盘移动初始化
void chassis_moto_speed_calc(int16_t vx, int16_t vy, int16_t vw);//计算马达速度

float power_limit(int16_t wheel_current[4]);

#endif




// end of file
