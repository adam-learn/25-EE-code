/**
 * @file shoot.h
 * @author sethome
 * @brief ����ģ��
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

enum shoot_speed // ��������ٶȣ��˴�Ϊ��������
{
		SHOOT_BEGIN = 5000,
    SHOOT_STOP = 0,
    SHOOT_30 =-8100, //27.5
};

enum trigger_status_e // �����ֿ���ģʽ
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
	float shoot_speed[2]; // Ħ�����ٶ�
	enum trigger_status_e trigger_status;
	float trigger_speed; // ��������ٶ�	
	int remainingBullets;		
	struct
	{/* data */
		float now;
		float set;
		float off_set;
	}trigger_location; // �������λ��
	
  float set_trigger_speed;
  float trigger_given_current; 		
}	shoot_t;

extern shoot_t shoot;

// �ⲿ����
void shoot_init(void);    // ��ʼ��

void shoot_update(void);  // ���²�������ٶȵ�

void shoot_pid_cal(void); // ����pid

void shoot_speed_limit(void);//���ݲ���ϵͳ�����ٶ��޷�

void trigger_anti_kill_and_set_speed(float set);

void shoot_trigger_online(void);//PC����

void shoot_set_trigger_location(int n);

int shoot_Bullets(int n); // ����N���ӵ�

void shoot_set_back(void);

void shoot_reload(void);  // �ӵ����¼���


#endif




// end of file
