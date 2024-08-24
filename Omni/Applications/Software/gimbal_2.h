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
#define __GIMBAL_H__
#ifdef __GIMBAL_H__

#include "pid.h"
#include "stdint.h"

//��̨�������
#define PITCH_MOTOR CAN_2_5
#define YAW_MOTOR CAN_2_6
#define PI 3.1415926f

extern float  pitch_test_link;
extern float yaw_test_link;
extern float set_motor_time;

enum gimbal_status_e
{
    LOCATION = 0,
    SPEED,
	ABSOLUTE,
    zero_force,
};

struct gimbal_status
{
    //�趨��̨����ģʽ
    enum gimbal_status_e pitch_status;
    enum gimbal_status_e yaw_status;

    struct
    {
        float set, now, last, absoulte_offset,location_offset;
        float stable;
    } pitch;
    float pitch_speed;
    float set_pitch_speed;

    struct
    {
        float set, now, last, absoulte_offset,location_offset;
        float stable;
    } yaw;
    float yaw_speed;
    float set_yaw_speed;
};

extern struct gimbal_status gimbal;

//�ⲿ����
void gimbal_init(void);                         //��ʼ����̨
void gimbal_set_offset(float ab_pitch, float ab_yaw,float lo_pitch,float lo_yaw); //��ʼ�����

void gimbal_set(float pitch, float yaw); //���ýǶ�
void gimbal_set_pitch(float pitch,float up_angle,float down_angle);      //�趨picth�Ƕ�,�޷���

void gimbal_set_speed(float pitch, float yaw); //�趨�ٶ�
void gimbal_set_yaw_speed(float yaw);          //�趨yaw�ٶ�

void gimbal_pid_cal(void); //��̨PID����
void gimbal_updata(void);  //������̨����
void gimbal_clear_cnt(void);

float feedforward_contorl(float target);//ǰ��

// end of file

#endif
