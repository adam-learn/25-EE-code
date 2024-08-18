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
#include "NUC_communication.h"
#include "IMU_updata.h"
#include "Global_status.h"
#include "USB_VirCom.h"
#include "Stm32_time.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "gimbal.h"
STM32_data_t toNUC;
unsigned char data[128];

uint32_t ready_time =0;
float auto_yaw,auto_pitch,visual_yaw,visual_pitch;
bool vision_update_flag;
int yaw_err_time =36;
int pitch_err_time =36;

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
void board_to_nuc(uint8_t time)//���ڶ�ʱ�жϵ�����Ϊ�˱�֤�̶�Ƶ��ȥ����
{
	toNUC.header = (unsigned)'h';
//	toNUC.Q0 = IMU_data.AHRS.q[0];//����imu�������Ԫ����̬
//	toNUC.Q1 = IMU_data.AHRS.q[1];
//	toNUC.Q2 = IMU_data.AHRS.q[2];
//	toNUC.Q3 = IMU_data.AHRS.q[3];
//	
//	toNUC.yaw = IMU_data.AHRS.yaw_rad_cnt;
//	toNUC.pitch = IMU_data.AHRS.pitch;
	
	toNUC.Q0 = get_history_q_data(0,time);//����imu�����"��ʷ"��Ԫ����̬
	toNUC.Q1 = get_history_q_data(1,time);
	toNUC.Q2 = get_history_q_data(2,time);
	toNUC.Q3 = get_history_q_data(3,time);
	
	toNUC.yaw = get_history_data(1,time);//��ʷ����
	toNUC.pitch = get_history_data(0,time);


	toNUC.x_speed = 100.0f;//�����������Ϊ
	toNUC.y_speed = 100.0f;
	toNUC.r_speed = 100.0f;

	toNUC.bullet = 100;
	toNUC.distance = 100;

	toNUC.robot_speed_mps = 27.0f;
		
	if(Global.input.anti_stauts==1)//������
		toNUC.mode = 1;
	else
		toNUC.mode = 0;	
	
	if(get_robot_id() >= 100)
		toNUC.enemy_color = 1;//�з���ɫ
	else 
		toNUC.enemy_color = 0;
	
	if(toNUC.enemy_color)//��ʱ��ȡ��ɫ���˵�Ѫ������
	{
		toNUC.enemy_blood_[0] = game_robot_HP.red_7_robot_HP;//�ڱ�
		toNUC.enemy_blood_[1] = game_robot_HP.red_1_robot_HP;
		toNUC.enemy_blood_[2] = game_robot_HP.red_2_robot_HP;
//		toNUC.enemy_blood_[2] = ;
		toNUC.enemy_blood_[3] = game_robot_HP.red_3_robot_HP;
		toNUC.enemy_blood_[4] = game_robot_HP.red_4_robot_HP;
		toNUC.enemy_blood_[5] = game_robot_HP.red_5_robot_HP;
	}
	else
	{
		
		toNUC.enemy_blood_[0] = game_robot_HP.blue_7_robot_HP;//�ڱ�
		toNUC.enemy_blood_[1] = game_robot_HP.blue_1_robot_HP;
		toNUC.enemy_blood_[2] = game_robot_HP.blue_2_robot_HP;
//		toNUC.enemy_blood_[2] = 40;
		toNUC.enemy_blood_[3] = game_robot_HP.blue_3_robot_HP;
		toNUC.enemy_blood_[4] = game_robot_HP.blue_4_robot_HP;
		toNUC.enemy_blood_[5] = game_robot_HP.blue_5_robot_HP;
	
	}
	toNUC.time_data =Get_sys_time_ms();//��¼��ʱ��ʱ���
  toNUC.enter=0x0A;
	encodeSTM32(&toNUC, data, sizeof(STM32_data_t));
	VirCom_send(data, sizeof(STM32_data_t));
}

/*�������񣬲�Ҫ��Ϊʲô�����������ļ����ʾ����Թ�*/
// ��̨
/*������ƣ�˼·�ܼ򵥣���Ϊ�Ӿ��ش�����ƫ����ҵ�Ŀ��ֵ���ǵ�ǰyaw+ƫ��=Ŀ��yaw��ʵʱ����
Ϊʲô����+=�أ���Ϊ�����ʽ���ڻ�����ת�Ĺ����л����µ����ݴ��룬��ʱ��SET��>Ŀ��ֵ��
���ұ���Ҫ����һ����ֵ�������������ޱƽ���������ȫ����
*/
void auto_ctrl(void)
{
		static uint32_t last_nuc_time,nuc_time,check_time;//�Ӿ�����ʱ����������Ӿ����߼��
		float record_yaw_now = gimbal.yaw.set;
		float record_pitch_now =gimbal.pitch.set;
		static uint8_t lost_count;
		/*******��������*******/
    if((Get_sys_time_ms()-check_time)>500){
    last_nuc_time=nuc_time;
    nuc_time=fromNUC.his_time_data;
    if(nuc_time==last_nuc_time)
      Global.input.vision_online=0;
    else
      Global.input.vision_online=1;   
    check_time=Get_sys_time_ms();
    }
    
		if(fromNUC.shoot!=0 &&fabs(fromNUC.yaw)<21.0f)
		{
			lost_count  =0;
			visual_yaw =  AutoAim_Algorithm(&yaw_auto_kf,fromNUC.yaw*ANGLE_TO_RAD -(get_history_data(YAW_DATA_HIS,yaw_err_time)-IMU_data.AHRS.yaw_rad_cnt));
			visual_pitch =AutoAim_Algorithm(&pitch_auto_kf,fromNUC.pitch*ANGLE_TO_RAD -(get_history_data(PITCH_DATA_HIS,pitch_err_time)-IMU_data.AHRS.pitch));
//				visual_yaw =  AutoAim_Algorithm(&yaw_auto_kf,fromNUC.yaw*ANGLE_TO_RAD -(IMU_data.AHRS.yaw_rad_cnt - get_history_data(YAW_DATA_HIS,yaw_err_time)));
//				visual_pitch =AutoAim_Algorithm(&pitch_auto_kf,fromNUC.pitch*ANGLE_TO_RAD -(IMU_data.AHRS.pitch - get_history_data(PITCH_DATA_HIS,pitch_err_time)));

			data_kalman_process();
		}
		else
		{
			lost_count++;
		}	
		/*******����ٿ�*******/
		if (vision_update_flag ==1&&fromNUC.shoot!=0)
		{
			//auto_yaw = auto_aim_judgement(raw_vision_data);//��������ģʽ�жϣ����ض�Ӧ����ֵ
			auto_yaw = IMU_data.AHRS.yaw_rad_cnt-visual_yaw;
			auto_pitch = IMU_data.AHRS.pitch - visual_pitch;
			//auto_pitch =get_history_data(PITCH_DATA_HIS,pitch_err_time)- visual_pitch;
		}
		else
		{
			auto_yaw = record_yaw_now;	
			auto_pitch = record_pitch_now;
		}
		//��ͷ���޸ģ���Ϊ��ʱ��ת��̫���Ӿ�ʶ�𲻵�����֡��ֱ�ӿ�����
		
}


void data_kalman_process(void)
{
	ready_time++;
	if(ready_time >30)
	{
		vision_update_flag =1;
	}
	else
		vision_update_flag =0;
}
float  auto_aim_judgement(float input)
{
////	if(fabs(fromNUC.yaw)<1.5f&&fromNUC.shoot!=0)
////	{
////		from_input =input;
////	}
////	else 
////	{
////	from_input =input;
////
	return input;

}
//
bool update_sensor_data(float new_data) //����30ms��ƽ�����ݷ�ֹͻ��
{
	ready_time++;
//	i =medianFilter(DATA_SIZE, new_data);	
	if(ready_time >30)
	{
		return true;
	}
	else
		return false;
}
void vision_reset(void)
{
	ready_time =0;
	
}


//end of file
