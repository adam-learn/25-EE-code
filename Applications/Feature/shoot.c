/**
 * @file shoot.c
 * @author sethome
 * @brief 发射模块
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "cover_headerfile_h.h"
#include "shoot.h"

shoot_t shoot;
uint16_t booster_cnt = 0;
uint8_t booster_status = 0;
uint8_t trigger_cnt_auto;

//初始化
void shoot_init(void)
{
	pid_set(&shoot.shoot1_speed_pid, 15, 0, 4, 4000, 0);
	pid_set(&shoot.shoot2_speed_pid, 15, 0, 4, 4000, 0);

	pid_set(&shoot.trigger_speed_pid, 10, 0, 5, 16000, 300);
	pid_set(&shoot.trigger_location_pid, 50, 0, 0, 5000, 100);

	shoot.trigger_status = SPEEDS;
	shoot.speed_level = SHOOT_STOP;
	shoot.trigger_location.set = 0;
	shoot.trigger_location.now = 0;
}

//更新拨弹电机数据
void shoot_update(void)
{

	decode_as_3508(SHOOT_MOTOR1);
	decode_as_3508(SHOOT_MOTOR2);
	shoot.shoot_speed[0] = get_motor_data(SHOOT_MOTOR1).speed_rpm;
	shoot.shoot_speed[1] = get_motor_data(SHOOT_MOTOR2).speed_rpm;

	decode_as_2006(TRIGGER_MOTOR);
	shoot.trigger_location.now = get_motor_data(TRIGGER_MOTOR).angle_cnt;
	shoot.trigger_speed = get_motor_data(TRIGGER_MOTOR).speed_rpm;
	shoot.trigger_given_current = get_motor_data(TRIGGER_MOTOR).given_current;
}

void shoot_set_shoot_Motor_speed(float speed)
{
  // 速度环
		if(robot_status.power_management_shooter_output==1&&Global.mode==NORMAL) //	 if(Global.mode==NORMAL)
		{
			set_motor(pid_cal(&shoot.shoot1_speed_pid, get_motor_data(SHOOT_MOTOR1).speed_rpm, speed), SHOOT_MOTOR1);
			set_motor(pid_cal(&shoot.shoot2_speed_pid, get_motor_data(SHOOT_MOTOR2).speed_rpm, -speed), SHOOT_MOTOR2);
		}
		else if(robot_status.power_management_shooter_output==0||Global.mode==LOCK) //		else if(Global.mode==LOCK)
		{
			set_motor(0, SHOOT_MOTOR1);
			set_motor(0, SHOOT_MOTOR2);						
		}	
	
}


void shoot_pid_cal(void)
{
	static enum trigger_status_e last_status = LOCATIONS;

	//摩擦轮设定
	decode_as_3508(SHOOT_MOTOR1);
	shoot_set_shoot_Motor_speed((float)shoot.speed_level);

	decode_as_2006(TRIGGER_MOTOR);

	//拨弹电机设定
	if (shoot.trigger_status == LOCATIONS) //位置控制
	{
		if (last_status == SPEEDS)
		{
			shoot.trigger_location.set += shoot.trigger_location.now;
		}
		shoot.trigger_speed = pid_cal(&shoot.trigger_location_pid, shoot.trigger_location.now, shoot.trigger_location.set);
	}
	else if (shoot.trigger_status == SPEEDS) //速度控制
	{
		shoot.trigger_speed = shoot.set_trigger_speed;
	}

	//速度环
		if(robot_status.power_management_shooter_output==1&&Global.mode==NORMAL) //	 if(Global.mode==NORMAL)
		{
			set_motor(pid_cal(&shoot.trigger_speed_pid, get_motor_data(TRIGGER_MOTOR).speed_rpm, shoot.trigger_speed), TRIGGER_MOTOR);
		}
		else if(robot_status.power_management_shooter_output==0||Global.mode==LOCK) //		else if(Global.mode==LOCK)
		{
			set_motor(0, TRIGGER_MOTOR);				
		}	
	
	
	last_status = shoot.trigger_status;
}

void shoot_speed_limit(void)
{
	if (Global.input.shooter_status == 0)
	{
		shoot.speed_level = SHOOT_STOP;
		booster_status = 0;
		booster_cnt = 0;
		trigger_anti_kill_and_set_speed(0);
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
			shoot.speed_level = SHOOT_BEGIN;
	}
	else
	{
		trigger_anti_kill_and_set_speed(0);
	}
}

void trigger_anti_kill_and_set_speed(float set)
{
	if (shoot.trigger_given_current < -10000)
		Global.input.trigger_kill_cnt = 50;

	if (Global.input.trigger_kill_cnt > 5)
	{
		Global.input.trigger_kill_cnt--;
		Global.input.trigger_kill = 1;
	}
	else if (Global.input.trigger_kill_cnt == 5)
		Global.input.trigger_kill = 0;

	if (Global.input.trigger_kill == 1)
	{
		shoot.set_trigger_speed = 10000;
	}
	else
	{

		if (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 20))	
		{
			if (REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 150))//290-150 = 140 
				shoot.set_trigger_speed = set;
			else if ((REFEREE_DATA.Barrel_Heat > (REFEREE_DATA.Heat_Limit - 150))&&(REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 100)))  //290- 100 = 190
				shoot.set_trigger_speed = set / 1.5f;
			else if ((REFEREE_DATA.Barrel_Heat > (REFEREE_DATA.Heat_Limit - 100))&&(REFEREE_DATA.Barrel_Heat < (REFEREE_DATA.Heat_Limit - 50)))  //290-50 = 240 
				shoot.set_trigger_speed = set / 3;
			else
				shoot.set_trigger_speed = set / 4;
		}
		else
			shoot.set_trigger_speed = 0;
	}

}

void shoot_trigger_online(void)
{
	if (Global.input.shooter_status != 0)
	{

		switch (Global.input.shoot_num)
		{
		case 0:
			if(fromNUC.shoot == 2)
				trigger_anti_kill_and_set_speed(-3000.0f);
			else
				trigger_anti_kill_and_set_speed(-3000.0f);
			break;

		case 1:
			if(fromNUC.shoot == 2)
				trigger_anti_kill_and_set_speed(-6000.0f);
			else
				trigger_anti_kill_and_set_speed(-4000.0f);
			break;

		default:
			trigger_anti_kill_and_set_speed(0);
			break;
		}
	}
	else if (Global.input.shooter_status == 0)
	{
		trigger_anti_kill_and_set_speed(0);
	}
}

//内部调用，射出子弹
void shoot_set_trigger_location(int n)
{
			static float temp = 0;
	if (shoot.speed_level != SHOOT_STOP)
	{

		if (Get_sys_time_ms() - temp > 200)
		{
			shoot.trigger_location.set -= n * A_BULLET_ANGEL;
			temp = Get_sys_time_ms();
		}
	}
}

//发射N颗子弹
int shoot_Bullets(int n)
{
	shoot.trigger_status = LOCATIONS;
	shoot_set_trigger_location(n);
	return n;
}



void shoot_set_back(void) //手动防卡弹 
{
	shoot.trigger_status = LOCATIONS;
	if (shoot.speed_level != SHOOT_STOP)
	{
		shoot.trigger_location.set -= 20;
	}
}

//重设子弹数目
void shoot_reload(void)
{
	shoot.remainingBullets = FULL_BULLETS;
}

// end of file
