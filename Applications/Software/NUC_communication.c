/**
 * @file NUC_communication.c
 * @brief 
 * @author sethome (you@domain.com)
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "cover_headerfile_h.h" 
#include "NUC_communication.h"

STM32_data_t toNUC;
NUC_data_t fromNUC;

int decodeSTM32(STM32_data_t *target, unsigned char rx_buff[], unsigned int len)
{
//    if (len != sizeof(STM32_data_t))
//        return -1;
    memcpy(target, rx_buff, sizeof(STM32_data_t));
    return 0;
}
int encodeSTM32(STM32_data_t *target, unsigned char tx_buff[], unsigned int len)
{
//    if (len < sizeof(STM32_data_t))
//        return -1;
    memcpy(tx_buff, target, sizeof(STM32_data_t));
    return 0;
}

int decodeNUC(NUC_data_t *target, unsigned char rx_buff[], unsigned int len)
{
//    if (len != sizeof(NUC_data_t))
//        return -1;
    memcpy(target, rx_buff, sizeof(NUC_data_t));
    return 0;
}
int encodeNUC(NUC_data_t *target, unsigned char tx_buff[], unsigned int len)
{
//    if (len < sizeof(NUC_data_t))
//        return -1;
    memcpy(tx_buff, target, sizeof(NUC_data_t));
    return 0;
}

void board_to_nuc(STM32_data_t *toNUC_t)
{
	unsigned char data[64];	
	
	toNUC_t->header = (unsigned)'h';
	toNUC_t->Q0 = IMU_data.AHRS.q[0];
	toNUC_t->Q1 = IMU_data.AHRS.q[1];
	toNUC_t->Q2 = IMU_data.AHRS.q[2];
	toNUC_t->Q3 = IMU_data.AHRS.q[3];	
	
	toNUC_t->yaw = IMU_data.AHRS.yaw_rad_cnt;
	toNUC_t->pitch = IMU_data.AHRS.pitch;

	toNUC_t->x_speed = 100.0f;
	toNUC_t->y_speed = 100.0f;
	toNUC_t->r_speed = 100.0f;

	toNUC_t->bullet = 100;
	toNUC_t->distance = 100;

	toNUC_t->robot_speed_mps = 30.0f;
		
	toNUC_t->mode = 0;	

	if(get_robot_id() >= 100)
		toNUC_t->enemy_color = 1;//敌方红色
	else 
		toNUC_t->enemy_color = 0;
	
	if(toNUC_t->enemy_color)//此时读取红色敌人的血量数据
	{
		toNUC_t->enemy_blood_[0] = game_robot_HP.red_7_robot_HP/10;//哨兵
		toNUC_t->enemy_blood_[1] = game_robot_HP.red_1_robot_HP/10;
		toNUC_t->enemy_blood_[2] = game_robot_HP.red_2_robot_HP/10;
		toNUC_t->enemy_blood_[3] = game_robot_HP.red_3_robot_HP/10;
		toNUC_t->enemy_blood_[4] = game_robot_HP.red_4_robot_HP/10;
		toNUC_t->enemy_blood_[5] = game_robot_HP.red_5_robot_HP/10;
		toNUC_t->enemy_blood_[6] = game_robot_HP.red_outpost_HP/10;
	}
	else
	{
		toNUC_t->enemy_blood_[0] = game_robot_HP.blue_7_robot_HP/10;//哨兵
		toNUC_t->enemy_blood_[1] = game_robot_HP.blue_1_robot_HP/10;
		toNUC_t->enemy_blood_[2] = game_robot_HP.blue_2_robot_HP/10;
		toNUC_t->enemy_blood_[3] = game_robot_HP.blue_3_robot_HP/10;
		toNUC_t->enemy_blood_[4] = game_robot_HP.blue_4_robot_HP/10;
		toNUC_t->enemy_blood_[5] = game_robot_HP.blue_5_robot_HP/10;
		toNUC_t->enemy_blood_[6] = game_robot_HP.blue_outpost_HP/10;	
	}
	toNUC_t->time_data =Get_sys_time_ms();//记录此时的时间戳
	
	encodeSTM32(&toNUC, data, sizeof(STM32_data_t));
	VirCom_send(data, sizeof(STM32_data_t));
	
}



