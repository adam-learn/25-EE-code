//���ڴ���Э�鸽¼V1.5
#ifndef REFEREE_HANDLE_PACK_H
#define REFEREE_HANDLE_PACK_H


#include "main.h"

#include "protocol.h"


typedef struct//�Զ���ṹ�壬���ں����и�ֵ��Ȼ���� FREERTOS �����  �����ɸ�����Ҫ�������
{
	float Initial_SPEED;//������ٶȣ���λ��m/s��	
	uint8_t Launching_Frequency;//��������Ƶ�ʣ���λ��Hz��
	uint16_t Launching_SPEED_Limit;//�������������ٶ�����
	 uint16_t projectile_allowance_17mm;
	uint16_t Barrel_Heat;//���������ǹ������	
	uint16_t CooLing_Value;//ǹ������ÿ����ȴֵ
	uint16_t Heat_Limit;//ǹ����������

	uint16_t Chassis_Voltage;//chassis �������ѹ����λ��mV��
	uint16_t Chassis_Current;//chassis �������������λ��mA��
	uint16_t Buffer_Energy;//������������λ��J��	
	float Chassis_Power;//���̹��ʣ���λ��W��
	uint16_t Chassis_Power_Limit;//�����˵��̹�������	
	float rest_time;

} REFEREE_DATA_t;

/********************
****game_type��������1��RoboMaster ���״�ʦ�����Կ���2��RoboMaster ���״�ʦ��У������
										3��ICRA RoboMaster ��У�˹�������ս�� 4��RoboMaster ���״�ʦ��У������ 3V3 �Կ�5��RoboMaster ���״�ʦ��У�����������Կ�
game_progress ��ǰ�����׶�0��δ��ʼ����1��׼���׶�2���Լ�׶�3��5 �뵹��ʱ4�������� 5������������
stage_remain_time  ��ǰ�׶�ʣ��ʱ�� s
***/

__packed typedef struct  //0x0001  ����״̬����11
{
 uint8_t game_type : 4;/**��������**/
 uint8_t game_progress : 4;/**��ǰ�����׶�**/
 uint16_t stage_remain_time;/*��ǰ�׶�ʣ��ʱ��*/
 uint64_t SyncTimeStamp;
}ext_game_status_t;


/***************
*****0��ƽ��  1���췽ʤ��   2������ʤ��
***/
__packed typedef struct  //0x0002  �����������1
{
	uint8_t winner;/******/
}ext_game_result_t;

__packed typedef struct  //0x0003  ������Ѫ������
{
 uint16_t red_1_robot_HP;
 uint16_t red_2_robot_HP;
 uint16_t red_3_robot_HP;
 uint16_t red_4_robot_HP;
 uint16_t red_5_robot_HP;
 uint16_t red_7_robot_HP;/*�ڱ�*/
 uint16_t red_outpost_HP;/**ǰ��վ**/
 uint16_t red_base_HP;
 uint16_t blue_1_robot_HP;
 uint16_t blue_2_robot_HP;
 uint16_t blue_3_robot_HP;
 uint16_t blue_4_robot_HP;
 uint16_t blue_5_robot_HP;
 uint16_t blue_7_robot_HP;
 uint16_t blue_outpost_HP;
 uint16_t blue_base_HP;
}ext_game_robot_HP_t;/**Ѫ��**/



/**************
******0��δռ��/δ����
1����ռ��/�Ѽ���

bit 0-2��
? bit 0�� ��������վǰ��Ѫ���ռ��״̬�� 1 Ϊ��ռ��
? bit 1�� ��������վ�ڲ���Ѫ���ռ��״̬�� 1 Ϊ��ռ��
? bit 2�� ������������ռ��״̬�� 1 Ϊ��ռ�죨�� RMUL ���ã�

bit 3-5��������������״̬
? bit 3�� �����������ؼ�����ռ��״̬�� 1 Ϊ��ռ��
? bit 4������С�������صļ���״̬�� 1 Ϊ�Ѽ���
? bit 5���������������صļ���״̬�� 1 Ϊ�Ѽ���

bit 6-11�������ߵ�ռ��״̬
? bit 6-7�� �������θߵص�ռ��״̬�� 1 Ϊ������ռ�죬 2 Ϊ���Է�ռ��
? bit 8-9�� �������θߵص�ռ��״̬�� 1 Ϊ������ռ�죬 2 Ϊ���Է�ռ��
? bit 10-11�� �������θߵص�ռ��״̬�� 1 Ϊ������ռ�죬 2 Ϊ���Է�ռ��
bit 12-18�� �����������⻤�ܵ�ʣ��ֵ�ٷֱȣ��������룬����������
bit 19-27���������һ�λ��м���ǰ��վ����ص�ʱ�䣨0-420������Ĭ��Ϊ0��
bit 28-29�� �������һ�λ��м���ǰ��վ����صľ���Ŀ�꣬����Ĭ��Ϊ 0��1 Ϊ����ǰ��վ�� 2 Ϊ���л��ع̶�Ŀ�꣬ 3 Ϊ���л������Ŀ��
bit 30-31�� ����������ռ������� 0 Ϊδ��ռ�죬 1 Ϊ������ռ�죬 2 Ϊ���Է�ռ�죬 3 Ϊ��˫��ռ�졣���� RMUL ���ã�
*********************/
__packed typedef struct  //0x0101  �����¼�����
{
	uint32_t event_data;
}ext_event_data_t; 



/******************
0  ���� 
***1 
���������� ID��
? 0����ǰ�޻����˲���
? 1���췽Ӣ�ۻ����˲���
? 3/4/5���췽���������˲���
? 101������Ӣ�ۻ����˲���
? 103/104/105���������������˲���
***2 
�����ڿ���״̬��
? 0���ر�
? 1������׼����
? 2�������ͷ�
***3 
����������
? 50��50 �ŵ���
? 100��100 �ŵ���
? 150��150 �ŵ���
? 200��200 �ŵ���
***************************/
__packed typedef struct  //0x0102  ����վ������ʶ����
{
 uint8_t reserved;
 uint8_t supply_robot_id;
 uint8_t supply_projectile_step;
 uint8_t supply_projectile_num;
}ext_supply_projectile_action_t;

/****
�������һ���ܵ��з��ĵȼ���
? 1�� ˫������
? 2�� ����
? 3������
? 4���и�
**************/
__packed typedef struct  //0x0104  ���о������� 
{

 uint8_t level;
 uint8_t offending_robot_id;
 uint8_t count;
 
}ext_referee_warning_t;



/****************************
** 1 �������ڷ���ʣ��ʱ�䣬��λ����
1 
bit 0-1��
���һ�μ������ڻ��е�Ŀ�꣬����Ĭ��Ϊ 0��1 Ϊ����ǰ��վ��2 Ϊ����
���ع̶�Ŀ�꣬3 Ϊ���л������Ŀ��
bit 2-4��
�Է���������е�Ŀ���ۼƱ����м���������Ĭ��Ϊ 0������Ϊ 4
bit 5-6��
���ڴ�ʱѡ���Ļ���Ŀ�꣬����Ĭ�ϻ�δѡ��/ѡ��ǰ��վʱΪ 0��ѡ�л�
�ع̶�Ŀ�� 1��ѡ�л������Ŀ��Ϊ 2
bit 7-15������
***/
__packed typedef struct  //0x0105  ���ڷ���ʱ������  
{
	uint8_t dart_remaining_time;
	uint16_t dart_info;
}ext_dart_remaining_time_t;



/***************
0 1 �������� ID
1 1 �����˵ȼ�
2 2 �����˵�ǰѪ��
4 2 ������Ѫ������
6 2 ������ǹ������ÿ����ȴֵ
8 2 ������ǹ����������
10 2 �����˵��̹�������
12 1
��Դ����ģ�����������
? bit 0�� gimbal ������� 0 Ϊ������� 1 Ϊ 24V ���
? bit 1�� chassis ������� 0 Ϊ������� 1 Ϊ 24V ���
? bit 2�� shooter ������� 0 Ϊ������� 1 Ϊ 24V ���
? bit 3-7�� ����
***************/
__packed typedef struct  //0x201  ������������ϵ����  
{

 
	uint8_t robot_id;       //�������� ID
	uint8_t robot_level;    // �����˵ȼ�
	uint16_t current_HP;    //�����˵�ǰѪ��
	uint16_t maximum_HP;    //������Ѫ������
	uint16_t shooter_barrel_cooling_value;    //������ǹ������ÿ����ȴֵ
	uint16_t shooter_barrel_heat_limit;       //������ǹ����������
	uint16_t chassis_power_limit;            //�����˵��̹�������
	uint8_t power_management_gimbal_output : 1;//��Դ����ģ����������
	uint8_t power_management_chassis_output : 1;
	uint8_t power_management_shooter_output : 1;

}ext_robot_status_t;


__packed typedef struct  //0x202  ʵʱ������������
{
 uint16_t chassis_voltage;//��Դ����ģ�� chassis �������ѹ����λ��mV��
 uint16_t chassis_current;//��Դ����ģ�� chassis �������������λ��mA��
 float chassis_power;//���̹��ʣ���λ��W��
 uint16_t buffer_energy;//������������λ��J��
 uint16_t shooter_17mm_1_barrel_heat;//�� 1 �� 17mm ���������ǹ������(0)
 uint16_t shooter_17mm_2_barrel_heat;//�� 2 �� 17mm ���������ǹ������(1)
 uint16_t shooter_42mm_barrel_heat;//42mm ���������ǹ������

}ext_power_heat_data_t;



/*******************
0  ��������λ�� x ���꣬��λ��m
4  ��������λ�� y ���꣬��λ��m
8  �������˲���ģ�鳯�򣬵�λ���ȡ�����Ϊ 0 ��
**************/
__packed typedef struct  //0x203  ������λ������
{
 float x;/*****/
 float y;/****/
 float angle;/*****/
}ext_robot_pos_t;



/*************
0  �����˻�Ѫ���棨�ٷֱȣ�ֵΪ 10 ��Ϊÿ��ظ� 10%���Ѫ����
1  ������ǹ����ȴ���ʣ�ֱ��ֵ��ֵΪ 5 ��ζ�� 5 ����ȴ��
2  �����˷������棨�ٷֱȣ�ֵΪ 50 ��Ϊ 50%�������棩
3  �����˹������棨�ٷֱȣ�ֵΪ 50 ��Ϊ 50%�������棩
*****************/
__packed typedef struct  //0x0204  ��������������
{
 uint8_t recovery_buff;//�����˻�Ѫ���棨�ٷֱȣ�ֵΪ 10 ��Ϊÿ��ظ� 10%���Ѫ����/******/
 uint8_t cooling_buff;//������ǹ����ȴ���ʣ�ֱ��ֵ��ֵΪ 5 ��ζ�� 5 ����ȴ��/******/
 uint8_t defence_buff;//�����˷������棨�ٷֱȣ�ֵΪ 50 ��Ϊ 50%�������棩/******/
 uint16_t attack_buff;//�����˹������棨�ٷֱȣ�ֵΪ 50 ��Ϊ 50%�������棩/*****/
}ext_buff_t;



__packed typedef struct  //0x0205  ����֧Ԯʱ������
{
 uint8_t airforce_status;
 uint8_t time_remain;
}ext_air_support_data_t;



__packed typedef struct  //0x0206  �˺�״̬����
{
 uint8_t armor_id : 4;//����Ѫԭ��Ϊװ��ģ������ģ��ʱ���� 4bit ��ɵ���ֵΪװ��ģ������ģ��� ID ��ţ�����ԭ���Ѫʱ������ֵΪ 
 uint8_t HP_deduction_reason : 4;//Ѫ���仯����
}ext_hurt_data_t;



__packed typedef struct  //0x0207  ʵʱ�������
{
 uint8_t bullet_type;//�������ͣ� 1��17mm ���� 2��42mm ����
 uint8_t shooter_number;//1���� 1 �� 17mm ������� 2���� 2 �� 17mm ������� 3��42mm �������
 uint8_t launching_frequency;//��������Ƶ�ʣ���λ��Hz��
 float initial_speed;//������ٶȣ���λ��m/s��
}ext_shoot_data_t;


/********
0  17mm ������������
2  42mm ������������
4  ʣ��������
******/
__packed typedef struct  //0x0208  ��������
{
 uint16_t projectile_allowance_17mm;/*****/
 uint16_t projectile_allowance_42mm;/****/
 uint16_t remaining_gold_coin;/****/
}ext_projectile_allowance_t;




/****************
bit λֵΪ 1/0 �ĺ��壺�Ƿ��Ѽ�⵽������� RFID
? bit0���������������
? bit1���������θߵ������
? bit2���Է����θߵ������
? bit3������ R3/B3 ���θߵ������**
? bit4���Է� R3/B3 ���θߵ������**
? bit5������ R4/B4 ���θߵ������**
? bit6���Է� R4/B4 ���θߵ������**
? bit7�������������ؼ����
? bit8��������������㣨��������һ�����ǰ��
? bit9��������������㣨��������һ����º�
? bit10���Է���������㣨�����Է�һ�����ǰ��
? bit11���Է���������㣨�����Է�һ����º�
? bit12������ǰ��վ�����
? bit13��������Ѫ�㣨��⵽��һ����Ϊ���
? bit14�������ڱ�Ѳ����**
? bit15���Է��ڱ�Ѳ����**
? bit16����������Դ�������
? bit17���Է�����Դ�������
? bit18�������һ���
? bit19-31������
*****************/
__packed typedef struct  //0x0209  ������ RFID ״̬
{
	uint32_t rfid_status;
}ext_rfid_status_t;




__packed typedef struct  //0x020A  ����ѡ�ֶ�ָ������
{
 uint8_t dart_launch_opening_status;//��ǰ���ڷ���վ��״̬�� 1���رգ�2�����ڿ������߹ر��У�0���Ѿ���
 uint8_t reserved;
 uint16_t target_change_time;//�л����Ŀ��ʱ�ı���ʣ��ʱ�䣬��λ��s����δ�л�����Ĭ��Ϊ 0
 uint16_t latest_launch_cmd_time;//���һ�β�����ȷ������ָ��ʱ�ı���ʣ��ʱ�䣬��λ��s����ʼֵΪ 0
}ext_dart_client_cmd_t;



/***************
0  ����Ӣ�ۻ�����λ�� x �����꣬��λ��m
4  ����Ӣ�ۻ�����λ�� y �����꣬��λ��m
8  �������̻�����λ�� x �����꣬��λ��m
12  �������̻�����λ�� y �����꣬��λ��m
16  ���� 3 �Ų���������λ�� x �����꣬��λ��m
20  ���� 3 �Ų���������λ�� y �����꣬��λ��m
24  ���� 4 �Ų���������λ�� x �����꣬��λ��m
28  ���� 4 �Ų���������λ�� y �����꣬��λ��m
32  ���� 5 �Ų���������λ�� x �����꣬��λ��m
36  ���� 5 �Ų���������λ�� y �����꣬��λ��m
*************/
__packed typedef struct  //0x020B  ���������λ������
{
 float hero_x;
 float hero_y;
 float engineer_x;
 float engineer_y;
 float standard_3_x;
 float standard_3_y;
 float standard_4_x;
 float standard_4_y;
 float standard_5_x;
 float standard_5_y;
}ext_ground_robot_position_t;/*****/



__packed typedef struct  //0x020C  �״��ǽ�������
{
 uint8_t mark_hero_progress;
 uint8_t mark_engineer_progress;
 uint8_t mark_standard_3_progress;
 uint8_t mark_standard_4_progress;
 uint8_t mark_standard_5_progress;
 uint8_t mark_sentry_progress;
}ext_radar_mark_data_t;



/**bit0-10���ڱ��Ѿ��ɹ��һ��ķ�����ֵ������Ϊ 0�����ڱ��ɹ��һ�һ����
���ķ������󣬸�ֵ����Ϊ�ڱ��Ѿ��ɹ��һ��ķ�����ֵ��
bit 11-14���ڱ��ɹ�Զ�̶һ��������Ĵ���������Ϊ 0�����ڱ��ɹ�Զ�̶�
���������󣬸�ֵ����Ϊ�ڱ��Ѿ��ɹ�Զ�̶һ��������Ĵ�����
bit 15-18���ڱ��ɹ�Զ�̶һ�Ѫ���Ĵ���������Ϊ 0�����ڱ��ɹ�Զ�̶һ�
Ѫ���󣬸�ֵ����Ϊ�ڱ��Ѿ��ɹ�Զ�̶һ�Ѫ���Ĵ�����
bit 19-31������**/
__packed typedef struct//0x020D �ڱ�����ָ��
{
	uint32_t sentry_info;
}ext_sentry_info_t;



/*bit 0-1���״��Ƿ�ӵ�д���˫�����˵��ʸ񣬿���Ϊ 0����ֵΪ�״�ӵ�д���
˫�����˵��ʸ����������Ϊ 2��
bit2�������Ƿ����ڱ�����˫������
? 0������δ������˫������
? 1���������ڱ�����˫������*/
/***/
__packed typedef struct// 0x020E �״��Ƿ����˫�������ʸ�
{
 uint8_t radar_info;
} ext_radar_info_t;



/**bit 0���ڱ��������Ƿ�ȷ�ϸ���
? 0 ��ʾ�ڱ������˲��븴���ʹ��ʱ�ڱ���������Ѿ�
���
? 1 ��ʾ�ڱ��������븴������������ɽ���������
bit 1���ڱ��������Ƿ���Ҫ�һ���������
? 0 ��ʾ�ڱ������˲���һ��������
? 1 ��ʾ�ڱ���������һ������������ʱ�ڱ������˷�
�϶һ���������Ĺ���Ҫ������������Ľ�Ҷһ��ڱ�
����������
bit2-12���ڱ���Ҫ�һ��ķ�����ֵ������Ϊ 0���޸Ĵ�ֵ��
�ڱ��ڲ�Ѫ�㼴�ɶһ�����������
��ֵ�ı仯��Ҫ����������������Ϊ���Ϸ���
ʾ������ֵ���ֽ���Ϊ 0���˺��ڱ��ɽ���� 0 �޸��� X������
�� X ��ҳɹ��һ� X �����������˺��ڱ��ɽ���� X �޸���
X+Y���Դ����ơ�
bit 13-16���ڱ���ҪԶ�̶һ����������������������Ϊ 0��
�޸Ĵ�ֵ��������Զ�̶һ���������
��ֵ�ı仯��Ҫ����������ÿ�ν������� 1��������Ϊ����
����
ʾ������ֵ���ֽ���Ϊ 0���˺��ڱ��ɽ���� 0 �޸��� 1������
�Ľ��Զ�̶һ������������˺��ڱ��ɽ���� 1 �޸��� 2��
�Դ����ơ�
bit 17-20���ڱ���ҪԶ�̶һ�Ѫ�����������������Ϊ 0����
�Ĵ�ֵ��������Զ�̶һ�Ѫ����
��ֵ�ı仯��Ҫ����������ÿ�ν������� 1��������Ϊ����
����
ʾ������ֵ���ֽ���Ϊ 0���˺��ڱ��ɽ���� 0 �޸��� 1������
�Ľ��Զ�̶һ�Ѫ�����˺��ڱ��ɽ���� 1 �޸��� 2���Դ���
�ơ�
**/
__packed typedef struct//0x0120  �ڱ���������ָ��
{
	uint32_t sentry_cmd;
}ext_sentry_cmd_t;



/**/
__packed typedef struct // 0x0121 �״���������ָ��
{
	uint8_t radar_cmd;
} ext_radar_cmd_t;


__packed typedef struct  //0x0301  �����˽�������
{
 uint16_t data_cmd_id;
 uint16_t sender_id;
 uint16_t receiver_id;
 uint8_t user_data[100];
	
}ext_robot_interaction_data_t;


__packed typedef struct//0x0303  ������
{
	float target_position_x;//Ŀ��λ�� x �����꣬��λ m ������Ŀ������� ID ʱ����ֵΪ 0
	float target_position_y;//Ŀ��λ�� y �����꣬��λ m ������Ŀ������� ID ʱ����ֵΪ 0
	uint8_t cmd_keyboard;//��̨�ְ��µļ��̰���ͨ�ü�ֵ �ް���������Ϊ 0
	uint8_t target_robot_id;//�Է������� ID ��������������ʱ����ֵΪ 0
	uint8_t cmd_source;//��Ϣ��Դ ID
}ext_map_command_t;



__packed typedef struct  //0x0305  ѡ�ֶ�С��ͼ�����״�����
{
	uint16_t target_robot_id;
	float target_position_x;
	float target_position_y;
}ext_map_robot_data_t;



/***/
__packed typedef struct  //0x0307  ѡ�ֶ�С��ͼ�����ڱ�����
{
	uint8_t intention;
	uint16_t start_position_x;
	uint16_t start_position_y;
	int8_t delta_x[49];
	int8_t delta_y[49];
	uint16_t sender_id;
}ext_map_sentry_data_t;



/***/
__packed typedef struct //0x0308  ���������˿�ͨ��������·�򼺷�����ѡ�ֶ˷����Զ������Ϣ������Ϣ���ڼ���ѡ�ֶ��ض�λ����ʾ��
{ 
uint16_t sender_id;
uint16_t receiver_id;
uint16_t user_data[30];
}ext_custom_info_t;



__packed typedef struct  //0x0302  �Զ��������������˽�������
{
uint8_t data[25];
}ext_custom_robot_data_t;



__packed typedef struct  //0x0304  ����ң������
{
int16_t mouse_x;
int16_t mouse_y;
int16_t mouse_z;
uint8_t left_button_down;
uint8_t right_button_down;
uint16_t keyboard_value;
uint16_t reserved;
}ext_remote_control_t;



__packed typedef struct  //0x0306  �Զ����������ѡ�ֶ˽�������
{
uint16_t key_value;
 uint16_t x_position:12;
 uint16_t mouse_left:4;
 uint16_t y_position:12;
 uint16_t mouse_right:4;
 uint16_t reserved;
}ext_custom_client_data_t;


///************************** �����˼佻������ ********************/
///* �������ݽ�����Ϣ�� 0x0301 */
typedef __packed struct {
    uint16_t data_cmd_id;  //���ݶε����� ID
    uint16_t sender_ID;
    uint16_t receiver_ID;
} ext_student_interactive_header_data_t;



/* �������ݽṹ�� */
typedef struct {
    uint16_t                              cmd_id;
    ext_student_interactive_header_data_t data_header;
    uint8_t                               data[120];
    uint16_t                              frame_tail;
}ext_referee_send_data_t;





extern REFEREE_DATA_t REFEREE_DATA;



typedef enum
{

    RED_HERO        = 1,
    RED_ENGINEER    = 2,
    RED_STANDARD_1  = 3,
    RED_STANDARD_2  = 4,
    RED_STANDARD_3  = 5,
    RED_AERIAL      = 6,
    RED_SENTRY      = 7,
    RED_DART        = 8,
    RED_RADAR       = 9,
    RED_OUTPOST     = 10,
    RED_LOCATION    = 11,

    BLUE_HERO       = 101,
    BLUE_ENGINEER   = 102,
    BLUE_STANDARD_1 = 103,
    BLUE_STANDARD_2 = 104,
    BLUE_STANDARD_3 = 105,
    BLUE_AERIAL     = 106,
    BLUE_SENTRY     = 107,
    BLUE_DART       = 108,
    BLUE_RADAR      = 109,
    BLUE_OUTPOST    = 110,
    BLUE_LOCATION   = 111,

}ext_robot_id_t;



typedef enum
{
    PROGRESS_UNSTART        = 0,
    PROGRESS_PREPARE        = 1,
    PROGRESS_SELFCHECK      = 2,
    PROGRESS_5sCOUNTDOWN    = 3,
    PROGRESS_BATTLE         = 4,
    PROGRESS_CALCULATING    = 5,
}ext_game_progress_t;



/* 

��ʱע��

�ͻ��� �ͻ����Զ������ݣ�cmd_id:0x0301������ ID:0x0100   0x0101  0x0102  0x0103  0x0104  0x0110
����Ƶ�ʣ����� 10Hz
*/

//typedef __packed struct  //0x0100  ѡ�ֶ�ɾ��ͼ��
//{
//uint8_t delete_type;
//uint8_t layer;
//}ext_interaction_layer_delete_t;


//typedef __packed struct  //0x0101  ѡ�ֶ˻���һ��ͼ��
//{ 
//uint8_t figure_name[3]; 
//uint32_t operate_tpye:3; 
//uint32_t figure_tpye:3; 
//uint32_t layer:4; 
//uint32_t color:4; 
//uint32_t details_a:9;
//uint32_t details_b:9;
//uint32_t width:10; 
//uint32_t start_x:11; 
//uint32_t start_y:11; 
//uint32_t details_c:10; 
//uint32_t details_d:11;
//uint32_t details_e:11; 
//}ext_interaction_figure_1_t;


//typedef __packed struct  //0x0102  ѡ�ֶ˻�������ͼ��
//{
// interaction_figure_1_t interaction_figure[2];
//}ext_interaction_figure_2_t;


//typedef __packed struct  //0x0103  ѡ�ֶ˻������ͼ��
//{
//interaction_figure_t interaction_figure[5];
//}ext_interaction_figure_5_t;


//typedef __packed struct  //0x0104  ѡ�ֶ˻����߸�ͼ��
//{
//interaction_figure_t interaction_figure[7];
//}ext_interaction_figure_7_t;


//typedef __packed struct  //0x0110  ѡ�ֶ˻����ַ�ͼ��
//{
//graphic_data_struct_t grapic_data_struct;
//uint8_t data[30];
//}ext_client_custom_character_t;




extern ext_game_status_t game_status;//0x0001  ����״̬����
extern ext_game_result_t game_result;//0x0002  �����������
extern ext_game_robot_HP_t game_robot_HP;//0x0003  ������Ѫ������

extern ext_event_data_t event_data;//0x0101  �����¼�����

extern ext_supply_projectile_action_t supply_projectile_action;//0x0102  ����վ������ʶ����

extern ext_referee_warning_t referee_warning;//0x0104  ���о�������

extern ext_dart_remaining_time_t dart_remaining_time;//0x0105  ���ڷ���ʱ������ 

extern ext_robot_status_t robot_status;//0x201  ������������ϵ����

extern ext_power_heat_data_t power_heat_data;//0x202  ʵʱ������������

extern ext_robot_pos_t robot_pos;//0x203  ������λ������

extern ext_buff_t robot_buff;//0x0204  ��������������

extern ext_air_support_data_t air_support_data;//0x0205  ����֧Ԯʱ������

extern ext_hurt_data_t hurt_data;//0x0206  �˺�״̬����

extern ext_shoot_data_t shoot_data;//0x0207  ʵʱ�������

extern ext_projectile_allowance_t projectile_allowance;//0x0208  ��������

extern ext_rfid_status_t rfid_status;//0x0209  ������ RFID ״̬

extern ext_dart_client_cmd_t dart_client_cmd;//0x020A  ����ѡ�ֶ�ָ������

extern ext_ground_robot_position_t ground_robot_position;//0x020B  ���������λ������

extern ext_radar_mark_data_t radar_mark_data;//0x020C  �״��ǽ�������
/*��ʼȱ����*/

extern ext_sentry_info_t sentry_data;//0x020D�ڱ��������

extern ext_radar_info_t radar_data;//0x020E�״��������

extern ext_robot_interaction_data_t robot_interaction_data;//0x0301  �����˽�������

extern ext_map_command_t map_command;//0x0303  ѡ�ֶ�С��ͼ��������

extern ext_map_robot_data_t map_robot_data;//0x0305  ѡ�ֶ�С��ͼ�����״�����

extern ext_map_sentry_data_t map_sentry_data;//0x0307  ѡ�ֶ�С��ͼ�����ڱ�����

extern ext_custom_robot_data_t custom_robot_data;//0x0302  �Զ��������������˽�������

extern ext_remote_control_t remote_control;//0x0304  ����ң������

extern ext_custom_client_data_t custom_client_data;//0x0306  �Զ����������ѡ�ֶ˽�������
/*0x0308����ͨѶ���*/
extern ext_custom_info_t exchange_data;//0x0308 ���������ˡ�����ѡ�ֶ�

void init_referee_struct_data(void);
void referee_data_solve(uint8_t *frame);


uint8_t get_robot_id(void);


void get_chassis_power_and_buffer(fp32 *power, uint16_t *buffer);
void get_chassis_VOL_CUR_POW_BUF(uint16_t *chassis_voltage,uint16_t *chassis_current,float *chassis_power, uint16_t *buffer_energy);
void get_chassis_power_limit(uint16_t *chassis_power_limit);


const ext_robot_status_t *get_robot_state_point(void);
const ext_power_heat_data_t *get_power_heat_data_point(void);
const ext_shoot_data_t *get_shoot_data_point(void);


void Required_Data();
void Cap_Required_Data(); 
#endif