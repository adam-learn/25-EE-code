
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
 

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"

#include "math.h"
#include "CAN_receive&send.h" 
#include "chassis_move.h"
#include "referee_handle_pack.h"
#include "cap_ctl.h"
#include "Stm32_time.h"
#include "Global_status.h"
#include "IMU_updata.h"
#include "gimbal.h"

//����б�º�����
#include "RampFunc.h"

// wheel conf
#define WHEEL_RADIUS 0.15240f // m
#define PI 3.1415926f

// car conf
#define ROLLER_DISTANCE 100 // mm  ���
#define WHEELS_DISTANCE 100 // mm  �־�

struct chassis_status chassis;
struct cap cap_chassis;	//������
// mm/s
#define FR 0
#define FL 1
#define BL 2
#define BR 3
float wheel_rpm[4]; // �����ٶ�����
float Plimit=1.0f;	//�ȱ�ϵ��

float Power;
uint16_t Engerny_buffer;
float vis_rela_angle;
float relative_angle = 0;

float spin_forward_sen=-4.0f;
extern float spin;
extern float slope;
// ����ٶȻ�PID
pid_t motor_speed[4];
pid_t motor_location[4];
pid_t move_motor_speed[4];
pid_t chassis_follow;

// ��ʼ������
void chassis_move_init()
{
	chassis.speed.max_x = 8.0f; // m/s 
	chassis.speed.max_y = 8.0f; // m/s
	chassis.speed.max_r = 5.0f;	//

	chassis.acc.max_x = 2.5f; // 1m/^2
	chassis.acc.max_y = 2.5f; // m/^2
	chassis.acc.max_r = 2.5f;  //
/***********************************���ٶȻ�����*******************************************/
	pid_set(&move_motor_speed[FR], 8000, 0, 250, MAX_CURRENT, 0);
	pid_set(&move_motor_speed[FL], 8000, 0, 250, MAX_CURRENT, 0);
	pid_set(&move_motor_speed[BL], 8000, 0, 250, MAX_CURRENT, 0);
	pid_set(&move_motor_speed[BR], 8000, 0, 250, MAX_CURRENT, 0);
/***********************************˫������************************************************/
  pid_set(&motor_location[FR], 20,0, 100, 1000, 0);
	pid_set(&motor_location[FL], 20,0, 100, 1000, 0);
	pid_set(&motor_location[BL], 20,0, 100, 1000, 0);
	pid_set(&motor_location[BR], 20,0, 100, 1000, 0);
  
  pid_set(&motor_speed[FR], 20, 0, 10, MAX_CURRENT, 0);
	pid_set(&motor_speed[FL], 20, 0, 10, MAX_CURRENT, 0);
	pid_set(&motor_speed[BL], 20, 0, 10, MAX_CURRENT, 0);
	pid_set(&motor_speed[BR], 20, 0, 10, MAX_CURRENT, 0);
  
  chassis.angle_now[FR] = motor_data[0].angle_cnt;
	chassis.angle_now[FL] = motor_data[1].angle_cnt;
	chassis.angle_now[BL] = motor_data[2].angle_cnt;
	chassis.angle_now[BR] = motor_data[3].angle_cnt;
	srand(2); //��ʼ��һ����������ӣ�Ϊ��֮�����С����ʹ��
}

//����ֵ
inline void val_limit(float *val, float MAX)
{
	if (fabs(*val) > MAX)
	{
		if (*val > 0)
			*val = MAX;
		else
			*val = -MAX;
	}
}

//���Ʊ仯��
inline void change_limit(float last, float *now, float limit)
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






/**********************sethome************************************************************/

float now_p = 0.0f;
float b = 0.015f;
float power_limit(int32_t current[4])
{

	float max_p; // = REFEREE_DATA.Chassis_Power_Limit - 2.0f; // 2w����

	if (cap.remain_vol <= 6)
		max_p = REFEREE_DATA.Chassis_Power_Limit - 2.0f; // 2w����
	else if (cap.remain_vol > 6)
	{
		if(Global.input.fly_status == 1)
			max_p = REFEREE_DATA.Chassis_Power_Limit +cap.remain_vol * 15 ; // ��������� = �����ѹ * 14A ��Ȧ������ 
		if(Global.input.fly_status != 1)
			max_p = REFEREE_DATA.Chassis_Power_Limit +cap.remain_vol * 14 ;
	}
	
	now_p = 0;	
	
//	if (cap.remain_vol <= 5)
//		max_p = 300 - 2.0f; // 2w����
//	else if (cap.remain_vol > 5)
//	{
//			  max_p = 300 +cap.remain_vol * 14 ;; // ��������� = �����ѹ * 14A ��Ȧ������ 
//	}
//	
//	if(max_p >= 300 + cap.remain_vol * 14)
//		max_p = 300 + cap.remain_vol * 14;
//	
//	now_p = 0;	
//	

	
//	const float a = 1.95e-07;	 // k1
  
	const float a = 1.23e-07;	 // k1
	const float k2 = 1.453e-07; // k2
	const float constant = 4.081f;
  //���ٱȸ�Ϊ14�ø�ϵ�������ļ��ٱ�Ϊ19Ϊע�ͺ�ϵ��
	const float toque_coefficient = (20.0f/16384.0f)*(0.3f)*(187.0f/3591.0f)/9.55f; // (20/16384)*(0.3)*(187/3591)/9.55=1.99688994e-6f P19
	for (int i = 0; i < 4; i++)
	{
		// ���㹦��
		// ���������֣�https://github.com/MaxwellDemonLin/Motor-modeling-and-power-control/blob/master/chassis_power_control.c#L89
    
    // ��ǰ���� = ������ * ��������ת��ϵ�� * �ٶ� + K2 * �ٶȵ�ƽ�� + a * ������ƽ���� / Ч�� 
    // K2 �������ٶ����ޣ����ٳ���������K2
    // a ����������ʱ�����������𲽳���������a
    // Ч��һ�㲻�ö���ԼΪ0.6-0.85
		now_p += fabs(current[i] * toque_coefficient * get_motor_data(i).speed_rpm +
					  k2 * get_motor_data(i).speed_rpm * get_motor_data(i).speed_rpm +
					  a * current[i] * current[i] + constant) / 0.85f;
	}
  
  // ����Ԥ�⹦�ģ���������ı���
	float percentage = max_p / now_p;
	
	if (percentage > 1.0f)
		return 1.0f;
	return percentage - b; // b ��һ����ѧ�Ĳ��������ڲ�������ٶ�ʱ���ʳ��������
}


///**************************************************doujuezi***************************************************/
//float per;
//float now_give_power[4]= {0.0f,0.0f,2.0f,0.0f}; //��֪ת�ٺ����ؼ�����Ķ�Ӧ����
//float now_total_power =0.0f;//�ĸ����ӹ����ܺ�
//float power_scale;
//float chassis_max_power; 
//float siri;
//fp32 chassis_power_text;
//float error_text_sqrt ;
//float error_text_sum ;
//void power_limit(void) //PID�����
//{
//	/***************��ߵ��̹���������*********************/
//	// Slightly greater than the maximum power, avoiding the capacitor being full all the time
//  //	and improving energy utilization
//	// = REFEREE_DATA.Chassis_Power_Limit - 2.0f; // 2w���� ��������   ��������
//                           //
//	
//	if (cap.remain_vol <= 6)
//		chassis_max_power = REFEREE_DATA.Chassis_Power_Limit - 2.0f; // 2w����
//	else if (cap.remain_vol > 6)
//	{
//		if (cap.state == 0)
//		{
//			chassis_max_power = REFEREE_DATA.Chassis_Power_Limit + cap.remain_vol*14; // Slightly greater than the maximum power, avoiding the capacitor being full all the time and improving energy utilization
//      //chassis_max_power = REFEREE_DATA.Chassis_Power_Limit;
//		}
//		else
//		{
//      //chassis_max_power +=  2.0f;
//      chassis_max_power = REFEREE_DATA.Chassis_Power_Limit + cap.remain_vol*14;
//		}
//		
//	}
//	
//	/***************��������ʿ���*********************/  
//	const float k1 = 1.46e-07;	 // k1
//	const float k2 = 1.453e-07; // k2
//	const float constant = 4.081f;
//  
//  //���ٱȸ�Ϊ14�ø�ϵ�������ļ��ٱ�Ϊ19Ϊע�ͺ�ϵ��
//	const float toque_coefficient = (20.0f / 16384.0f) * (0.3f) * (1000.0f / 13733.0f) / 9.55f; // (20/16384)*(0.3)*(187/3591)/9.55=1.99688994e-6f P19
//  
//	
//		// ���㹦��
//		// ���������֣�https://github.com/MaxwellDemonLin/Motor-modeling-and-power-control/blob/master/chassis_power_control.c#L89
//    
//    // ��ǰ���� = ������ * ��������ת��ϵ�� * �ٶ� + K2 * �ٶȵ�ƽ�� + a * ������ƽ���� / Ч�� 
//    // K2 �������ٶ����ޣ����ٳ���������K2
//    // K1 ����������ʱ�����������𲽳���������K1
//    // Ч��һ�㲻�ö���ԼΪ0.6-0.85
//		
////		now_give_power[i] = fabs(current[i] * toque_coefficient * get_motor_data(i).speed_rpm +
////					  k2 * get_motor_data(i).speed_rpm * get_motor_data(i).speed_rpm +
////					  a * current[i] * current[i] + constant) / 0.85f;
//		

//    int j;
//    for(j = 0; j<4;j++)
//    {
//      		
//		now_give_power[j] = fabs(chassis.wheel_current[j] * toque_coefficient * get_motor_data(j).speed_rpm +
//					  k2 * get_motor_data(j).speed_rpm * get_motor_data(j).speed_rpm +
//					  k1 *chassis.wheel_current[j] * chassis.wheel_current[j] + constant) / 0.85f;
//		
//		if (now_give_power[j] < 0) // negative power not included (transitory)
//      continue;
//	//	now_total_power += now_give_power[j];
//    }
//now_total_power  = now_give_power[0]+now_give_power[1]+now_give_power[2]+now_give_power[3];
//	
//	/***************���̹������·���*********************/
//    	if (now_total_power > chassis_max_power) // determine if larger than max power
//	{
//		float scaled_give_power[4]={0.0f,1.0f,2.0f,3.0f};
//	 power_scale = chassis_max_power/now_total_power ;
//  
//		for (uint8_t i = 0; i < 4; i++)
//		{
//			scaled_give_power[i] = now_give_power[i] * power_scale; // get scaled power
//			if (scaled_give_power[i] < 0)
//			{
//				continue;
//			}

//  		float b = toque_coefficient * get_motor_data(i).speed_rpm;
////      fp32 b = get_motor_data(i).speed_rpm/9.55;
//			float c = k2 * get_motor_data(i).speed_rpm * get_motor_data(i).speed_rpm - scaled_give_power[i] + constant;
////      fp32 d = (0.3f) * (1000.0f / 13733.0f);
//      
//      
//           siri=b * b - 4 *k1 * c;
//           error_text_sqrt = sqrt(fabsf(b * b - 4 *k1 * c));
//           error_text_sum = -b + sqrt(fabsf(b * b - 4 *k1 * c));
//      
//         //  chassis_power_text = 50;
//           
//			if (chassis.wheel_current[i]> 0) // Selection of the calculation formula according to the direction of the original moment
//			{
// 
//        
//				   chassis_power_text = (-b + sqrt(fabs(b * b - 4 *k1 * c))) / (2 * k1);
//				if (chassis_power_text > 16000)
//				{
//					//chassis.wheel_current[i] = 6100;
//				}
//				//else
//					//chassis.wheel_current[i] = chassis_power_text;
//			}
//			else
//			{
//				fp32 temp = (-b - sqrt(fabsf(b * b - 4 *k1 * c))) / (2 * k1);
//				if (temp < -16000)
//				{
//					//chassis.wheel_current[i] = -6100;
//				}
//				//else
//					//chassis.wheel_current[i] = temp;
//			}
//		}
//	}
//    
//    
//    
////per = chassis_max_power/now_total_power;

////if (per<1) // determine if larger than max power
////{
//// chassis.wheel_current[0] = chassis.wheel_current[0]*0.2;

//// chassis.wheel_current[1] = chassis.wheel_current[1]*0.2;

//// chassis.wheel_current[2] = chassis.wheel_current[2]*0.2;

//// chassis.wheel_current[3] = chassis.wheel_current[3]*0.2;

////}

//}
//	



// �����������ٶ�
float chassis_angle;
  int32_t max_curr = 0;
float curr_a = 0.0f;

void chassis_moto_speed_calc()
{
	// ����ٶ�����
	val_limit(&chassis.speed.x, chassis.speed.max_x);
	val_limit(&chassis.speed.y, chassis.speed.max_y);
	val_limit(&chassis.speed.r, chassis.speed.max_r);

	decode_as_3508(CAN_1_1);
	decode_as_3508(CAN_1_2);
	decode_as_3508(CAN_1_3);
	decode_as_3508(CAN_1_4);

	// �����ٶȷ���
	wheel_rpm[FR] = +chassis.speed.x - chassis.speed.y + chassis.speed.r;
	wheel_rpm[FL] = +chassis.speed.x + chassis.speed.y + chassis.speed.r;
	wheel_rpm[BL] = -chassis.speed.x + chassis.speed.y + chassis.speed.r;
	wheel_rpm[BR] = -chassis.speed.x - chassis.speed.y + chassis.speed.r;

	// ��ǰ�ٶ�
	chassis.speed.now_x = wheel_rpm[FL] / 2.0f - wheel_rpm[BL] / 2.0f;
	chassis.speed.now_y = wheel_rpm[FL] / 2.0f - wheel_rpm[FR] / 2.0f;
	chassis.speed.now_r = wheel_rpm[FR] / 2.0f + wheel_rpm[BL] / 2.0f;

	// ������ٶ�
	uint32_t now_time = Get_sys_time_ms();
	static uint32_t last_time = 0;
	float dt = (now_time - last_time) / 1000.0f;
	last_time = now_time;
	chassis.acc.now_x = (chassis.speed.x - chassis.speed.now_x) / dt;
	chassis.acc.now_y = (chassis.speed.y - chassis.speed.now_y) / dt;
	chassis.acc.now_r = (chassis.speed.r - chassis.speed.now_r) / dt;

	// ���Ƽ��ٶ�
	 if (fabs(chassis.acc.now_x) > chassis.acc.max_x)
	 {
	 	if (chassis.speed.x < 0.0f)
	 		chassis.speed.x = -(chassis.acc.max_x * dt + chassis.speed.now_x);
	 	chassis.speed.x = chassis.acc.max_x * dt + chassis.speed.now_x;
	 }
	 if (fabs(chassis.acc.now_y) > chassis.acc.max_y)
	 {
	 	if (chassis.speed.y < 0.0f)
	 		chassis.speed.y = -(chassis.acc.max_y * dt + chassis.speed.now_y);
	 	chassis.speed.y = chassis.acc.max_y * dt + chassis.speed.now_y;
	  }
	 if (fabs(chassis.acc.now_r) > chassis.acc.max_r)
	 {
	 	if (chassis.speed.r < 0.0f)
	 		chassis.speed.r = -(chassis.acc.max_r * dt + chassis.speed.now_r);
	 	chassis.speed.r = chassis.acc.max_r * dt + chassis.speed.now_r;
    
	 }
//   	float relative_angle = get_motor_data(YAW_MOTOR).angle_cnt - gimbal.yaw.location_offset;
//    if(abs((int)relative_angle) < 35&& Global.input.x == 0&&Global.input.y == 0)
//    {
//        if(fabs(slope)<= 10)
//        {
//            chassis.status = move;        
//        }
//        else
//          
//            chassis.status = park;
//    }
//    else
//    {
//            chassis.status = move;
//    }
//    
	 chassis.angle_now[FR] = motor_data[0].angle_cnt;
   chassis.angle_now[FL] = motor_data[1].angle_cnt;
   chassis.angle_now[BL] = motor_data[2].angle_cnt;
   chassis.angle_now[BR] = motor_data[3].angle_cnt;
	// ����������
 if(chassis.status == move)
   //( rad2degree(IMU_data.AHRS.pitch) - get_motor_data(PITCH_MOTOR).angle - 57.5)<=5)
 {
     chassis.wheel_current[FR] = pid_cal(&move_motor_speed[FR], get_motor_data(chassis_FR).round_speed * WHEEL_RADIUS * PI, wheel_rpm[FR]);
     chassis.wheel_current[FL] = pid_cal(&move_motor_speed[FL], get_motor_data(chassis_FL).round_speed * WHEEL_RADIUS * PI, wheel_rpm[FL]);
     chassis.wheel_current[BL] = pid_cal(&move_motor_speed[BL], get_motor_data(chassis_BL).round_speed * WHEEL_RADIUS * PI, wheel_rpm[BL]);
     chassis.wheel_current[BR] = pid_cal(&move_motor_speed[BR], get_motor_data(chassis_BR).round_speed * WHEEL_RADIUS * PI, wheel_rpm[BR]);
   
   chassis.angle_set[FR] = motor_data[0].angle_cnt;
   chassis.angle_set[FL] = motor_data[1].angle_cnt;
   chassis.angle_set[BL] = motor_data[2].angle_cnt;
   chassis.angle_set[BR] = motor_data[3].angle_cnt;
   
 }
 else
 {
     chassis.wheel_speed[FR]=pid_cal(&motor_location[FR],chassis.angle_now[FR],chassis.angle_set[FR]);
     chassis.wheel_speed[FL]=pid_cal(&motor_location[FL],chassis.angle_now[FL],chassis.angle_set[FL]);   
     chassis.wheel_speed[BL]=pid_cal(&motor_location[BL],chassis.angle_now[BL],chassis.angle_set[BL]);
     chassis.wheel_speed[BR]=pid_cal(&motor_location[BR],chassis.angle_now[BR],chassis.angle_set[BR]);
   
     chassis.wheel_current[FR] = pid_cal(&motor_speed[FR], get_motor_data(chassis_FR).round_speed * WHEEL_RADIUS * PI, chassis.wheel_speed[FR]);
     chassis.wheel_current[FL] = pid_cal(&motor_speed[FL], get_motor_data(chassis_FL).round_speed * WHEEL_RADIUS * PI, chassis.wheel_speed[FL]);
     chassis.wheel_current[BL] = pid_cal(&motor_speed[BL], get_motor_data(chassis_BL).round_speed * WHEEL_RADIUS * PI, chassis.wheel_speed[BL]);
     chassis.wheel_current[BR] = pid_cal(&motor_speed[BR], get_motor_data(chassis_BR).round_speed * WHEEL_RADIUS * PI, chassis.wheel_speed[BR]);
 }
//  for (int i = 0; i < 4;i+  +)
//  {
//    if (chassis.wheel_current[i] > max_curr)
//      max_curr = chassis.wheel_current[i];
//  }
//  if(max_curr > MAX_CURRENT)
//  {
//    curr_a = (float)MAX_CURRENT / (float)max_curr;
//    for(int i = 0; i < 4;i++)
//    {
//      chassis.wheel_current[i] = (float)chassis.wheel_current[i] * curr_a;
//    }
//  }


/*******************************sethome*****************************************/
//  if(( rad2degree(IMU_data.AHRS.pitch) - get_motor_data(PITCH_MOTOR).angle - 57.5)>5)
//         Plimit *=1.1;
//	else
         Plimit = power_limit(chassis.wheel_current);


/********************************doujuezi***************************************/
//	 if(cap.state == 0)
//		{
//		power_limit();
//		}
//    else if(cap.state == 1)
//		{
//			
//		}


	// �趨������ ����freeRTOS�з��ͣ�
if(Global.mode != LOCK)
{
	set_motor((  Plimit *chassis.wheel_current[FR]), chassis_FR);
	set_motor((  Plimit *chassis.wheel_current[FL]), chassis_FL);
	set_motor((  Plimit *chassis.wheel_current[BL]), chassis_BL);
	set_motor((  Plimit *chassis.wheel_current[BR]), chassis_BR);//��ʱע�͵���������ֻ������̨
}
	 else
	 {
	set_motor(0, chassis_FR);
	set_motor(0, chassis_FL);
	set_motor(0, chassis_BL);
	set_motor(0, chassis_BR);
	 }
	chassis.speed.last_x = chassis.speed.now_x;
	chassis.speed.last_y = chassis.speed.now_y;
	chassis.speed.last_r = chassis.speed.now_r;
}

int RampInc_float(int16_t *buffer, float now, float ramp)
{
	if (*buffer > 0)
	{
		if (*buffer > ramp)
		{
			now += ramp;
			*buffer -= ramp;
		}
		else
		{
			now += *buffer;
			*buffer = 0;
		}
	}
	else
	{
		if (*buffer < -ramp)
		{
			now += -ramp;
			*buffer -= -ramp;
		}
		else
		{
			now += *buffer;
			*buffer = 0;
		}
	}

	return now;
}
int refresh_interval = 30;//���´���������ʮ�θ���һ��
int smaller_than_2_count = 0;
float valve=0.0f;
float random_anti_vision_r_s(float min, float max)
{
	static int run_count =100 ;
	run_count++;
        if (run_count >refresh_interval &&smaller_than_2_count<2) 
			{
				valve = generate_random_float(min, max);//���޺�����

				run_count = 0;
			if (valve < 2.0f) 
				{
					smaller_than_2_count++;
				}
				return  valve;
			}
		else if(run_count >refresh_interval &&smaller_than_2_count>=2)
		{
			smaller_than_2_count=0;
			return 3.5f;
		}
		else 
			return valve;
}
	
float generate_random_float(float min, float max) 
{
    return min + ((float)rand() / RAND_MAX) * (max - min);
}
//�տ�ʼʱĬ�ϼ��ٶȣ�Ȼ�����Խ��Խ��
//����ֵ��ÿ�����м��ٶ�����ֵ���ٶ�����ֵ
float fly_speed_up(float *set,float acceleration_increase_rate ,float limit)
{
	static float initial_acceleration =0.2;//��ʼ���ٶ���Ϊ0.2//ÿ������+���ٶ�;	
	if(set ==0)//Ҳ���Ǵ�ͷ��ʼ�ˣ��Ǿ����ü��ٶ�
	{
		initial_acceleration =0.2;
	}
	if(fabs(*set)<limit)
	{
	*set += initial_acceleration;
	initial_acceleration +=acceleration_increase_rate;
	}
	else
	{
		*set =limit;
	}
}
//��ָ������ʽȥ���������Ǹ������������acc=ae^bv-a+c,��aΪ����cΪ��ʼ���ٶ�,�����ٶ�Ϊ�Ա���
float fly_speed_up_ex(float a,float b,float c,float v)
{
  return a*exp(b*v)-a+c;
}

void chassis_Flow_mode()
{
	float x_s, y_s, r_s;
	float sin_beta, cos_beta;
	
	uint32_t mul = 0;
    
		decode_as_6020(YAW_MOTOR);
	 	relative_angle = get_motor_data(YAW_MOTOR).angle_cnt - gimbal.yaw.location_offset;

if(slope > 10)
{   
     if(abs((int)(get_motor_data(YAW_MOTOR).angle - gimbal.yaw.location_offset))< 35 && Global.input.x == 0&&Global.input.y == 0)
    {
            chassis.status = park;        
    }
        else      
            chassis.status = move;    
    }     
else
    chassis.status = move;

    
				vis_rela_angle =relative_angle;
		sin_beta = sinf(degree2rad(relative_angle)); // ���뻡�ȣ������Ӧ�ĽǶ�sin��cos��Ӧֵ
		cos_beta = cosf(degree2rad(relative_angle));
		// ���̸���PID,����ʱ��ǿ������ȥ��ֹ�����ƫ
		if(Global.input.fly_status ==1)
			pid_set(&chassis_follow, 8.0f, 0, 0, 100, 0);//
		else
			pid_set(&chassis_follow, 2.0f, 0.0f, 0.0, 100, 0);//
		
		y_s = Global.input.x * sin_beta + Global.input.y * cos_beta;
		x_s = Global.input.x * cos_beta - sin_beta * Global.input.y; // �˶��ֽ�
		r_s = Global.input.r;
		mul = fabs(relative_angle) / 180;
		if (relative_angle > 180.0f)
		{
			if (mul % 2 == 1) // ����-180��
				relative_angle -= (mul + 1) * 180;
			else // ����180��
				relative_angle -= mul * 180;
		}
		if (relative_angle < -180.0f)
		{
			if (mul % 2 == 1) // ����180��
				relative_angle += (mul + 1) * 180;
			else // ����-180��
				relative_angle += mul * 180;
		}

		if (fabs(relative_angle) > 0.0f) // 0.05
			r_s = pid_cal(&chassis_follow, degree2rad(relative_angle), 0.0f);
		else
			r_s = 0.0;
		
if (fabs(Global.input.yaw) > 0.0f)
			gimbal.yaw.set -= Global.input.yaw;
		if (fabs(Global.input.pitch) > 0.0f)
			gimbal.pitch.set -= Global.input.pitch;

		chassis.speed.x = -x_s;
		chassis.speed.y = -y_s;
		chassis.speed.r = r_s;
}

void chassis_Spin_mode()
{
	float x_s, y_s, r_s;
	float sin_beta, cos_beta;

    chassis.status = move;  
    
		Global.input.fly_status = 0;
		relative_angle = get_motor_data(YAW_MOTOR).angle_cnt - gimbal.yaw.location_offset-get_motor_data(YAW_MOTOR).round_speed*spin_forward_sen;
				sin_beta = sinf(degree2rad(relative_angle)); // ���뻡�ȣ������Ӧ�ĽǶ�sin��cos��Ӧֵ
		cos_beta = cosf(degree2rad(relative_angle));

		x_s = Global.input.x * cos_beta - sin_beta * Global.input.y; // �˶��ֽ�
		y_s = Global.input.x * sin_beta + Global.input.y * cos_beta;

		if(REFEREE_DATA.Chassis_Power_Limit>= 40&&REFEREE_DATA.Chassis_Power_Limit<= 60)
			r_s = 1.4f;
		else if(REFEREE_DATA.Chassis_Power_Limit> 60&&REFEREE_DATA.Chassis_Power_Limit<= 80)
			r_s = 1.6f;
		else if(REFEREE_DATA.Chassis_Power_Limit> 80&&REFEREE_DATA.Chassis_Power_Limit<= 150)
			r_s = 1.8f; 
 
			//��ʱ��ע�͵������Ա���С����
//		r_s = random_anti_vision_r_s(1.5f,3.0f);
		if (fabs(Global.input.yaw) > 0.0f)
			gimbal.yaw.set -= Global.input.yaw; 
		if (fabs(Global.input.pitch) > 0.0f)
			gimbal.pitch.set -= Global.input.pitch;
		
		if (spin == 1)
	{
		chassis.speed.x = -x_s;//-x_s
		chassis.speed.y = -y_s;//-y_s
		chassis.speed.r = -r_s;
	}	
	
	if (spin == 0)
	{
		chassis.speed.x = -x_s;//-x_s
		chassis.speed.y = -y_s;//-y_s
		chassis.speed.r = r_s;
	}	

}

