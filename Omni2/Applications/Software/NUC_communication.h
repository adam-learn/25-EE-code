#include "referee_handle_pack.h"
#define DATA_SIZE 30
#define YAW_DATA_HIS 1
#define PITCH_DATA_HIS 0
#define ANGLE_TO_RAD 0.01745329251994329576923690768489f
#define RAD_TO_ANGLE 57.295779513082320876798154814105f
extern float auto_yaw,auto_pitch,visual_yaw,trans_delay_data,raw_vision_data;
 __packed typedef struct 
 {
 	uint8_t header;
	 
 	float Q0,Q1,Q2,Q3;
	 
 	float yaw,pitch;//û�ã�֮ǰ�ѵ�ʺ	 
	 
 	float x_speed,y_speed,r_speed;
	 
 	uint8_t bullet;

 	uint8_t distance;
	 
	float robot_speed_mps;//����

	uint8_t mode;
	
  uint8_t	enemy_color;

	uint8_t enemy_blood_[6];
	uint32_t time_data;//��¼��ʱC���ʱ���
 	char unknow[19];//24
	
	uint16_t checksum;
  char enter;
 } STM32_data_t;


typedef struct
{
	uint8_t header;
	uint8_t useless;
	uint8_t target_id;
	float yaw;
	float pitch;
	float pitch_speed;
	float yaw_speed;//����ĽǶ��ǡ�Ϊ��λ���յ����ٶ��ǻ���/s��
	uint8_t distance;
  uint8_t shoot;//������־λ
	uint8_t shoot_mode;//������־λ
	uint32_t his_time_data;
	char unknown[4];//ԭ����20����Ϊ16����Ϊʱ���ռ�����ĸ��ֽ�
	uint16_t checksum;
} __attribute__((packed)) NUC_data_t;

extern STM32_data_t toNUC;
extern NUC_data_t fromNUC;


//��STM32��NUC����Ϣ��/����
int encodeSTM32(STM32_data_t *target, unsigned char rx_buff[], unsigned int len);
int decodeSTM32(STM32_data_t *target, unsigned char tx_buff[], unsigned int len);

//��NUC��STM32����Ϣ��/����
int decodeNUC(NUC_data_t *target, unsigned char tx_buff[], unsigned int len);
int encodeNUC(NUC_data_t *target, unsigned char rx_buff[], unsigned int len);
void board_to_nuc(uint8_t time);
void Test_communcation_0128();

float  auto_aim_judgement(float input);
void vision_reset(void);
void data_kalman_process(void);
void auto_ctrl(void);
//end of file
