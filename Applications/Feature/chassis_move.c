/**
 * @file chassis_move.c
 * @author sethome
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "cover_headerfile_h.h"  
#include "chassis_move.h"

////底盘各轮子速度chassis.wheel_rpm和底盘三个轴方向实际速度chassis.speed.now_已代入正确解算，
////默认云台为底盘正中心，底盘为全向轮步兵规则底盘，具体参数可更改以下#define
/* 
			motorID 

	 1 %++++++% 0
			 ++++
			 ++++
	 2 %++++++% 3 
					 
*/	

#define chassis_FR CAN_1_1
#define chassis_FL CAN_1_2
#define chassis_BL CAN_1_3
#define chassis_BR CAN_1_4

// wheel conf
#define WHEEL_RADIUS 0.007f // m 全向轮步兵车轮半径
#define PI_t 3.1415926f

// car conf   
#define ROLLER_DISTANCE 0.315f // m 全向轮步兵底盘轴距
#define WHEELS_DISTANCE 0.315f // m 全向轮步兵底盘轮距
#define GIMBAL_OFFSET   0//     云台点偏移
#define RADIAN_COEF     57.3f//(rad/s)/57.3 = deg/s//弧度转角度
#define CHASSIS_DECELE_RATIO 19//减速比
#define PERIMETER  0.957557//m  车轮周长   2*PI*WHEEL_RADIUS
//（轴距+轮距）/2 /57.3

//底盘按照正方形计算，轮距等于轴距，云台点偏移为0
static float rotate_ratio_f = ((ROLLER_DISTANCE+WHEELS_DISTANCE)/2.0f - GIMBAL_OFFSET)/RADIAN_COEF;
static float rotate_ratio_b = ((ROLLER_DISTANCE+WHEELS_DISTANCE)/2.0f + GIMBAL_OFFSET)/RADIAN_COEF;
static float wheel_rpm_ratio = 60.0f/(PERIMETER*CHASSIS_DECELE_RATIO);//m/s = 60/(轮子周长*减速比) rpm

struct chassis_status chassis;

//最大速度
#define MAX_VX_SPEED 8 // m/s
#define MAX_VY_SPEED 8
#define MAX_VR_SPEED 4


//限制值
void val_limit(int16_t *val, float MAX)
{
	if (fabs(*val) > MAX)
	{
		if (*val > 0)
			*val = MAX;
		else
			*val = -MAX;
	}
}

//限制变化量
void change_limit(float last, float *now, float limit)
{
	float change = *now - last;
	if (fabs(change) > limit)
	{
		if (change > 0)
			*now = last + limit;
		else
			*now = last - limit;
	}
}	


 void chassis_move_init(void)
 {
	 
	chassis.power_limit.Plimit = 1.0f;
	chassis.power_limit.Engerny_buffer = REFEREE_DATA.Buffer_Energy;
	chassis.power_limit.a  = 1.23e-07;	 // k1
	chassis.power_limit.k2 = 1.453e-07; // k2	
	chassis.power_limit.constant = 4.081f;

	chassis.speed.max_x = 5.0f; // m/s 
	chassis.speed.max_y = 1000.0f; 	 
	chassis.speed.max_w = 6.0f;	
	 
 
 	pid_set(&chassis.motor_speed[chassis_FR], 10000, 0, 1200, 15000, 0);
 	pid_set(&chassis.motor_speed[chassis_FL], 10000, 0, 1200, 15000, 0);
 	pid_set(&chassis.motor_speed[chassis_BL], 10000, 0, 1200, 15000, 0);
 	pid_set(&chassis.motor_speed[chassis_BR], 10000, 0, 1200, 15000, 0);		 
	 	 
 }
 


float power_limit(int16_t wheel_current[4])
{
		chassis.power_limit.Plimit = 1.0f;
		chassis.power_limit.Engerny_buffer = REFEREE_DATA.Buffer_Energy;
		chassis.power_limit.a  = 1.23e-07;	 // k1
		chassis.power_limit.k2 = 1.453e-07; // k2	
		chassis.power_limit.constant = 4.081f;	
	//适配新步兵修改电机减速比参数，没修改直接用后边注释的参数
		chassis.power_limit.toque_coefficient = (20.0f / 16384.0f) * (0.22f) * (187.0f / 3591.0f) / 9.55f; // (20/16384)*(0.3)*(187/3591)/9.55=1.99688994e-6f P19	
	
	if (cap.remain_vol <= 5)
		chassis.power_limit.max_p = REFEREE_DATA.Chassis_Power_Limit - 2.0f; // 2w余量
	else if (cap.remain_vol > 5)
	{
		chassis.power_limit.max_p = REFEREE_DATA.Chassis_Power_Limit + 100; // 超电最大功率 = 超电电压 * 14A 线圈最大电流 
	}
	
	if(chassis.power_limit.max_p >= REFEREE_DATA.Chassis_Power_Limit + cap.remain_vol * 14)
		chassis.power_limit.max_p = REFEREE_DATA.Chassis_Power_Limit + cap.remain_vol * 14;
	


	for (int i = 0; i < 4; i++)
	{
		// 估算功率
		// 西交利物浦：https://github.com/MaxwellDemonLin/Motor-modeling-and-power-control/blob/master/chassis_power_control.c#L89
		chassis.power_limit.now_p += fabs((wheel_current[i]) * chassis.power_limit.toque_coefficient * (float)(get_motor_data(i).speed_rpm) +
					  chassis.power_limit.k2 * (float)(get_motor_data(i).speed_rpm) * (float)(get_motor_data(i).speed_rpm) +
					  chassis.power_limit.a * (wheel_current[i]) * (wheel_current[i]) + chassis.power_limit.constant) / 0.80f;
	}

	chassis.power_limit.percentage = chassis.power_limit.max_p / chassis.power_limit.now_p;
	
	if(chassis.power_limit.percentage > 1.0f)
		return 1.0f;
	return chassis.power_limit.percentage - chassis.power_limit.b;
}

//计算底盘马达速度
void chassis_moto_speed_calc(int16_t vx, int16_t vy, int16_t vw)
{
	//最大速度限制
	val_limit(&vx, MAX_VX_SPEED);
	val_limit(&vy, MAX_VY_SPEED);
	val_limit(&vw, MAX_VR_SPEED);

	decode_as_3508(chassis_FR);
	decode_as_3508(chassis_FL);
	decode_as_3508(chassis_BL);
	decode_as_3508(chassis_BR);

	chassis.speed.vx = vx;
	chassis.speed.vy = vy;
	chassis.speed.vw = vw;

	//计算速度分量
	chassis.wheel_rpm[chassis_FR] = (+chassis.speed.vx - chassis.speed.vy - chassis.speed.vw*rotate_ratio_f)*wheel_rpm_ratio;
	chassis.wheel_rpm[chassis_FL] = (+chassis.speed.vx + chassis.speed.vy - chassis.speed.vw*rotate_ratio_f)*wheel_rpm_ratio;
	chassis.wheel_rpm[chassis_BL] = (-chassis.speed.vx + chassis.speed.vy - chassis.speed.vw*rotate_ratio_b)*wheel_rpm_ratio;
	chassis.wheel_rpm[chassis_BR] = (-chassis.speed.vx - chassis.speed.vy - chassis.speed.vw*rotate_ratio_b)*wheel_rpm_ratio;

	chassis.speed.now_x = (chassis.wheel_rpm[chassis_FL] / 2 - chassis.wheel_rpm[chassis_BL] / 2)/wheel_rpm_ratio;
	chassis.speed.now_y = (chassis.wheel_rpm[chassis_FL] / 2 - chassis.wheel_rpm[chassis_FR] / 2)/wheel_rpm_ratio;
	chassis.speed.now_w = (chassis.wheel_rpm[chassis_FR] / 2 + chassis.wheel_rpm[chassis_BL] / 2)/(rotate_ratio_b*wheel_rpm_ratio);
	
	//计算马达电流
	chassis.wheel_current[chassis_FR] = pid_cal(&chassis.motor_speed[chassis_FR], 2*get_motor_data(chassis_FR).round_speed * WHEEL_RADIUS * PI_t, chassis.wheel_rpm[chassis_FR]);
	chassis.wheel_current[chassis_FL] = pid_cal(&chassis.motor_speed[chassis_FL], 2*get_motor_data(chassis_FL).round_speed * WHEEL_RADIUS * PI_t, chassis.wheel_rpm[chassis_FL]);
	chassis.wheel_current[chassis_BL] = pid_cal(&chassis.motor_speed[chassis_BL], 2*get_motor_data(chassis_BL).round_speed * WHEEL_RADIUS * PI_t, chassis.wheel_rpm[chassis_BL]);
	chassis.wheel_current[chassis_BR] = pid_cal(&chassis.motor_speed[chassis_BR], 2*get_motor_data(chassis_BR).round_speed * WHEEL_RADIUS * PI_t, chassis.wheel_rpm[chassis_BR]);

////	chassis.power_limit.Plimit = power_limit(chassis.wheel_current);


		if(robot_status.power_management_chassis_output==1&&Global.mode==NORMAL) //	 if(Global.mode==NORMAL)
		{
				//发送马达电流 （应在freeRTOS发送）
			set_motor(chassis.power_limit.Plimit*chassis.wheel_current[chassis_FR], CAN_1_1);
			set_motor(chassis.power_limit.Plimit*chassis.wheel_current[chassis_FL], CAN_1_2);
			set_motor(chassis.power_limit.Plimit*chassis.wheel_current[chassis_BL], CAN_1_3);
			set_motor(chassis.power_limit.Plimit*chassis.wheel_current[chassis_BR], CAN_1_4);	
//				//发送马达电流 （应在freeRTOS发送）
//			set_motor(chassis.wheel_current[chassis_FR], CAN_1_1);
//			set_motor(chassis.wheel_current[chassis_FL], CAN_1_2);
//			set_motor(chassis.wheel_current[chassis_BL], CAN_1_3);
//			set_motor(chassis.wheel_current[chassis_BR], CAN_1_4);				
		}
		else if(robot_status.power_management_chassis_output==0||Global.mode==LOCK) //		else if(Global.mode==LOCK)
		{
			//发送马达电流 （应在freeRTOS发送）
			set_motor(0, CAN_1_1);
			set_motor(0, CAN_1_2);
			set_motor(0, CAN_1_3);
			set_motor(0, CAN_1_4);							
		}

		
}




