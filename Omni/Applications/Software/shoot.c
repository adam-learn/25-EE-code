/**
 * @file shoot.c
 * @author sethome
 * @brief ����ģ��
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "shoot.h"
#include "stdio.h"
#include "pid.h"
#include "Stm32_time.h"
#include "math.h"
#include "global_status.h"
#include "CAN_receive&send.h"
#include "referee_handle_pack.h"
#include "NUC_communication.h"

pid_t trigger_speed_pid;
pid_t trigger_location_pid;

pid_t shoot1_speed_pid;
pid_t shoot2_speed_pid;

shoot_t shoot;

uint16_t booster_cnt = 0;
uint8_t booster_status = 0;
uint8_t trigger_cnt_auto;

// ��ʼ��
void shoot_init()
{
#ifdef USE_3508_AS_SHOOT_MOTOR
	// Ħ���ֵ��
	pid_set(&shoot1_speed_pid, 27, 0, 0, 3500, 0);
	pid_set(&shoot2_speed_pid, 27, 0, 0, 3500, 0);

#endif
	// �������
	pid_set(&trigger_speed_pid, 5, 0, 0, 16000, 300);
	pid_set(&trigger_location_pid, 140, 0, 0, 10000, 100);

	// ����˫�����ƺ�������ò����ٶȱ����ôλ�û���p��ֵһ������С�����ҽ����е����������p��΢����һ�㣬������Ԥѹ���̵�Ч��
	shoot.trigger_status = SPEEDS;
	//	shoot.trigger_status = LOCATIONS;//Ĭ��˫������
	shoot.speed_level = SHOOT_STOP;
	shoot.trigger_location.set = 0; // ��ʼ�ϵ����λ�ò�֪��Ϊʲô����5���ң��Ӹ��̶�����
	shoot.trigger_location.now = 0;
}

// ���²����������
void shoot_update()
{
#ifdef USE_3508_AS_SHOOT_MOTOR
	// ���ʹ��3508��ΪĦ���ֵ���Ļ�
	decode_as_3508(SHOOT_MOTOR1);
	decode_as_3508(SHOOT_MOTOR2);
	shoot.shoot_speed[0] = get_motor_data(SHOOT_MOTOR1).speed_rpm;
	shoot.shoot_speed[1] = get_motor_data(SHOOT_MOTOR2).speed_rpm;
#endif

	decode_as_2006(TRIGGER_MOTOR);
	shoot.trigger_location.now = get_motor_data(TRIGGER_MOTOR).angle_cnt;
	shoot.trigger_speed = get_motor_data(TRIGGER_MOTOR).speed_rpm;

	shoot.trigger_given_current = get_motor_data(TRIGGER_MOTOR).given_current;
}

void shoot_set_shoot_Motor_speed(float speed)
{
#ifdef USE_3508_AS_SHOOT_MOTOR
	set_motor(pid_cal(&shoot1_speed_pid, get_motor_data(SHOOT_MOTOR1).speed_rpm, speed), SHOOT_MOTOR1);
	set_motor(pid_cal(&shoot2_speed_pid, get_motor_data(SHOOT_MOTOR2).speed_rpm, -speed), SHOOT_MOTOR2);
#else
	// ���������������
	PWM_snaill_set(PIN_2, (uint16_t)speed);
	PWM_snaill_set(PIN_3, (uint16_t)speed);
#endif
}

void shoot_pid_cal(void) // �ں��˶�����ܣ������л����������ƣ����������pid��ͬ
{
	float set;
	if (Global.input.shoot_num == 1 && Global.input.shoot_fire && Global.input.shooter_status) // ������ģʽ&&���������&&Ħ���ֿ���
		set = 6000.0f;
	else if (Global.input.shoot_num == 0 && Global.input.shoot_fire && Global.input.shooter_status) // ������ģʽ&&���������&&Ħ���ֿ���
		set = 3000.0f;
	else
		set = 0.0f;
	// Ħ�����趨
	decode_as_3508(SHOOT_MOTOR1);
	shoot_set_shoot_Motor_speed((float)shoot.speed_level);

	decode_as_2006(TRIGGER_MOTOR);

	// ��������趨

	if (shoot.trigger_status == LOCATIONS) // λ�ÿ���
	{
		pid_set(&trigger_speed_pid, 10, 0, 0, 16000, 300);
		shoot.trigger_speed = pid_cal(&trigger_location_pid, shoot.trigger_location.now, shoot.trigger_location.set);
	}
	else if (shoot.trigger_status == SPEEDS) // �ٶȿ���
	{
		if (Global.input.shoot_fire == 1 || fromNUC.shoot == 2)
		{
			pid_set(&trigger_speed_pid, 40, 0, 0, 16000, 300);
		}
		else
			pid_set(&trigger_speed_pid, 5, 0, 0, 16000, 300);
	}
	// ��ѧУ֮����switch case ��д������û��������
	if (Global.input.shoot_fire)
	{
		if (Global.input.vision_status == 0) // ������
		{
			if (power_heat_data.shooter_17mm_1_barrel_heat < (robot_status.shooter_barrel_heat_limit - 20)) // 180
			{
				if (power_heat_data.shooter_17mm_1_barrel_heat < (robot_status.shooter_barrel_heat_limit - 120)) // 80
					RC_trigger_anti_kill_and_set_speed(set / 1.5f);
				else if ((power_heat_data.shooter_17mm_1_barrel_heat > (robot_status.shooter_barrel_heat_limit - 120)) && (power_heat_data.shooter_17mm_1_barrel_heat < (robot_status.shooter_barrel_heat_limit - 90))) // 80--110
					RC_trigger_anti_kill_and_set_speed(set / 3.0);
				else
					RC_trigger_anti_kill_and_set_speed(set / 4.0f); // 150-180
			}
			else
				shoot.set_trigger_speed = 0.0f;
		}
		else if (Global.input.vision_status == 1) // ����
		{
			if (power_heat_data.shooter_17mm_1_barrel_heat < (robot_status.shooter_barrel_heat_limit - 20))
			{
				if (power_heat_data.shooter_17mm_1_barrel_heat < (robot_status.shooter_barrel_heat_limit - 140)) // 60
					RC_trigger_anti_kill_and_set_speed(set);
				else if ((power_heat_data.shooter_17mm_1_barrel_heat > (robot_status.shooter_barrel_heat_limit - 140)) && (power_heat_data.shooter_17mm_1_barrel_heat < (robot_status.shooter_barrel_heat_limit - 70))) // 60--130
					RC_trigger_anti_kill_and_set_speed(set/1.5f);
				else
					RC_trigger_anti_kill_and_set_speed(set/4.0f);
			}
			else
				shoot.set_trigger_speed = 0.0f;
		}
	}
	else // ң��������
		RC_trigger_anti_kill_and_set_speed(Global.input.shoot_RC*10);
	// �ٶȻ�
	if (shoot.set_trigger_speed || get_motor_data(TRIGGER_MOTOR).speed_rpm >= 5)
		set_motor(pid_cal(&trigger_speed_pid, get_motor_data(TRIGGER_MOTOR).speed_rpm, shoot.set_trigger_speed), TRIGGER_MOTOR);
	if (!shoot.set_trigger_speed && get_motor_data(TRIGGER_MOTOR).speed_rpm <= 5)
		set_motor(0, TRIGGER_MOTOR); // ����ֱ�Ӹ������̵����0
}

void shoot_speed_limit()
{
	if (Global.input.shooter_status == 0)
	{
		shoot.speed_level = SHOOT_STOP;
		booster_status = 0;
		booster_cnt = 0;
	}
	else if (Global.input.shooter_status == 1)
	{
		booster_cnt++;
		if (booster_cnt >= 500)
		{
			booster_status = 1;
		}

		if (booster_status == 1)
		{
			shoot.speed_level = SHOOT_30;
		}
		else if (booster_status == 0)
			shoot.speed_level = SHOOT_BEGIN; // �տ�ʼʱ��Ħ���ַ�ת��ֹ��������Ȼ�ͼ���
	}
}

void RC_trigger_anti_kill_and_set_speed(float set) // ��ң�������񵥶��õģ����ڲ���ϵͳ��¼ʱ��ֹ��������Ҳ���ڼ�������µĶ�ת��ת
{
	shoot.trigger_status = SPEEDS;			 // �ٶȻ����ƣ�����ģʽ�л�
	if (shoot.trigger_given_current > 10000) // �ﵽ����������ֵ
		Global.input.trigger_kill_cnt = 18;	 // ��ʱ����

	if (Global.input.trigger_kill_cnt > 5)
	{
		Global.input.trigger_kill_cnt--;
		Global.input.trigger_kill = 1; // ������־λ��һ
	}
	else if (Global.input.trigger_kill_cnt == 5) // �ܹ�ִ��13�η�ת
		Global.input.trigger_kill = 0;

	if (Global.input.trigger_kill == 1)
	{
		shoot.set_trigger_speed = -10000;
	}

	else // ����������������߼�
	{
		shoot.set_trigger_speed = set; // ��������
	}
}



/*********************** ����Ϊδ��ʹ�õĺ��������ڲ��Ժ���ɾ��**************************/ 
void PC_trigger_set_speed(float set) // ���ڼ���ģʽ�·������������ڼ���ģʽ�ĺ����е������ܷ�ֹ���߼�����������һ����
{
	shoot.trigger_status = SPEEDS;
	if (Global.input.vision_status == 0)
	{
		if (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 20)) // 180
		{
			if (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 120)) // 80
				shoot.set_trigger_speed = set / 1.5f;
			else if ((REFEREE_DATA.Barrel_Heat > (REFEREE_DATA.Heat_Limit - 120)) && (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 90))) // 80--110
				shoot.set_trigger_speed = set / 3.0f;
			else
				shoot.set_trigger_speed = set / 4.0f; // 150-180
		}
		else
			shoot.set_trigger_speed = -0.01f;
	}
	else if (Global.input.vision_status == 1)
	{
		if (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 20))
		{
			if (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 140)) // 60
				shoot.set_trigger_speed = set;
			else if ((REFEREE_DATA.Barrel_Heat > (REFEREE_DATA.Heat_Limit - 140)) && (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 70))) // 60--130
				shoot.set_trigger_speed = set / 1.5f;
			else
				shoot.set_trigger_speed = set / 4.0f;
		}
		else
			shoot.set_trigger_speed = -0.01f;
	}

	else
		shoot.set_trigger_speed = 0;
}

void shoot_trigger_online()
{											 // ������ʱ��
	if (shoot.trigger_given_current > 10000) // �ﵽ����������ֵ
		Global.input.trigger_kill_cnt = 18;	 // ��ʱ����

	if (Global.input.trigger_kill_cnt > 5)
	{
		Global.input.trigger_kill_cnt--;
		Global.input.trigger_kill = 1; // ������־λ��һ
	}
	else if (Global.input.trigger_kill_cnt == 5) // �ܹ�ִ��13�η�ת
		Global.input.trigger_kill = 0;

	if (Global.input.trigger_kill == 1)
	{
		shoot.set_trigger_speed = -10000;
	}
	else // ��������ʱ��ִ�з����߼�
	{
		if (Global.input.shooter_status != 0) // ��ʼ����
		{
			switch (Global.input.shoot_num) // ��������
			{
			case 0:														   // Ĭ�ϵ���
				if (fromNUC.shoot == 2 && Global.input.vision_status == 1) // �Ҽ�+���������Ʒ���
					PC_trigger_set_speed(3000.0f);
				else if (Global.input.vision_status == 0) // ����������ʱ�ֶ�����
					PC_trigger_set_speed(3000.0f);
				//						shoot_Bullets(1);//����
				// shoot_Bullets(114514);
				break;
			case 1: // ����//	if(fromNUC.shoot == 2&& Global.input.vision_status==1&&Global.input.anti_stauts==0)

				if (fromNUC.shoot == 2 && Global.input.vision_status == 1) // �Ҽ�+���������Ʒ���
					PC_trigger_set_speed(6000.0f);
				else if (Global.input.vision_status == 0) // ����������ʱ�ֶ�����
					PC_trigger_set_speed(6000.0f);
				break;
			}
		}
		else
		{
			PC_trigger_set_speed(-0.01f);
		}
	}
}

void triger_clear_cnt()
{
	clear_motor_cnt(TRIGGER_MOTOR);
	shoot.trigger_location.now = 0;
	shoot.trigger_location.set = 0;
}

void shoot_set_trigger_location(int n)
{
	static float last_time = 0;
	if (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 20)) // ��С���������Ƶ�ʱ�����������������ϵ����ٽ�������ֹͣ����
	{
		if (n == 1)
		{
			if (Get_sys_time_ms() - last_time > 150) // �����ж�
			// ֻ�а���>200ms�Ż��һ������Ϊ���µ�ʱ����ܻ�ִ�кܶ�Σ�����Ҫ�ӳ����
			{
				shoot.trigger_location.set = shoot.trigger_location.now + A_BULLET_ANGEL; // Ĭ�Ϸ���������
			}
		}
		last_time = Get_sys_time_ms();
	}
}
void shoot_set_trigger_speed(int set)
{
	shoot.trigger_status = SPEEDS;
	shoot.set_trigger_speed = set;
	triger_clear_cnt();
}
/*��Ϊ������Ҫ�����ٶȻ�Ϊ��Ҫ�߼���ֻ�е���ʱ��ʹ��λ�û���
���Բ����ж�֮ǰ����ʲô������Ϊ�������ٶȻ�����
������Ŀǰ��е�������ǻ���ڣ����ʹ��λ�û��ᵼ�¿������˺���񷢵����³���������
����ʵ�ڿ���ʱλ�û�set=now�Ϳ��Ա��⣬����Ŀǰλ�û����ֲ��ã������Ȳ����ٶȻ�������
*/

int shoot_Bullets(int n)
{
	shoot.trigger_status = LOCATIONS;
	shoot_set_trigger_location(n);
	return n;
}
//end of file