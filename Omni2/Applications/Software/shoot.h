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
#include "stdint.h"
#include "struct_typedef.h"
#define _SHOOT_H_
#ifdef _SHOOT_H_

#define USE_3508_AS_SHOOT_MOTOR

// �����������
#define TRIGGER_MOTOR CAN_2_7
#define A_BULLET_ANGEL 49.0f

// Ħ���ֵ������ 3508
#ifdef USE_3508_AS_SHOOT_MOTOR
#define SHOOT_MOTOR1 CAN_2_2
#define SHOOT_MOTOR2 CAN_2_4
#endif

#pragma anon_unions

enum shoot_speed // ��������ٶȣ��˴�Ϊ��������
{
		SHOOT_BEGIN = 5000,
    SHOOT_STOP = 0,
    SHOOT_30 = -7200,//15000
};

enum trigger_status_e // �����ֿ���ģʽ
{
    LOCATIONS = 0,
    SPEEDS,
};

typedef struct
{
    /* data */
    enum shoot_speed speed_level;

    // �������
    float shoot_speed[2]; // Ħ�����ٶ�

    struct
    {
        /* data */
        float now;
        float set;
        float off_set;
    } trigger_location; // �������λ��

    float trigger_speed; // ��������ٶ�
    float set_trigger_speed;
    float trigger_given_current; 		
    enum trigger_status_e trigger_status;
} shoot_t;


extern shoot_t shoot;
extern uint8_t trigger_cnt_auto;

// �ⲿ����
void shoot_init(void);    // ��ʼ��

void shoot_update(void);  // ���²�������ٶȵ�

void shoot_pid_cal(void); // ����pid

void shoot_speed_limit();//

void RC_trigger_anti_kill_and_set_speed(float set);

void shoot_trigger_online();//PC����

void shoot_set_trigger_location(int n);

int shoot_Bullets(int n); // ����N���ӵ�

void triger_clear_cnt();

void shoot_set_trigger_speed(int set);//�����ٶȿ���

void PC_trigger_set_speed(float set);
#endif

// end of file
