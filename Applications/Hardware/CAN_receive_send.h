#ifndef __CAN_RECEIVE_SEND_H__
#define __CAN_RECEIVE_SEND_H__

#include "cover_headerfile_h.h"


/* CAN send and receive ID */
typedef enum
{
  CAN_1_4_SIGN_ID = 0x200,
  CAN_ID1 = 0x201,
  CAN_ID2 = 0x202,
  CAN_ID3 = 0x203,
  CAN_ID4 = 0x204,

  CAN_5_8_SIGN_ID = 0x1FF,
  CAN_ID5 = 0x0205,
  CAN_ID6 = 0x0206,
  CAN_ID7 = 0x0207,
  CAN_ID8 = 0x0208,

  CAN_6020_SIGN_ID = 0x2FF,
  CAN_6020_ID5 = 0x209,
  CAN_6020_ID6 = 0x210,
  CAN_6020_ID7 = 0x211,
} can_msg_id_e;

typedef enum
{
  CAN_1_1 = 0,   //0
  CAN_1_2,       //1
  CAN_1_3,       //2
  CAN_1_4,       //3
  CAN_1_5,
  CAN_1_6,
  CAN_1_7,
  CAN_1_8,
  CAN_1_6020_5,
  CAN_1_6020_6,
  CAN_1_6020_7,  //10

  CAN_2_1,       //11
  CAN_2_2,       //12
  CAN_2_3,
  CAN_2_4,
  CAN_2_5,       //15
  CAN_2_6,
  CAN_2_7,       //17
  CAN_2_8,
  CAN_2_6020_5,
  CAN_2_6020_6,
  CAN_2_6020_7,  //21
	
  CAN_3_1,       //22
  CAN_3_2,       //23
  CAN_3_3,
  CAN_3_4,
  CAN_3_5, 
  CAN_3_6,
  CAN_3_7, 
  CAN_3_8,
  CAN_3_6020_5,
  CAN_3_6020_6,
  CAN_3_6020_7,   //32	

} can_id;


// ������궨�����ĵ��ID(������ֱ���ڵ����ļ��ж���� ����չʾ) 
// 6020�� CAN_1_5(��ӦID1) �� CAN_1_6020_7����ӦID7��
// 3508/2006�� CAN_1_1(��ӦID1) �� CAN_1_8����ӦID7��
// ���޸�can_msg_id_e
#define motor_1_1 CAN_1_1
#define motor_1_2 CAN_1_2
#define motor_1_3 CAN_1_3
#define motor_1_4 CAN_1_4
#define motor_1_5 CAN_1_5
#define motor_1_6 CAN_1_6
#define motor_1_7 CAN_1_7
#define motor_1_8 CAN_1_8
#define M6020_1_5 CAN_1_6020_5
#define M6020_1_6 CAN_1_6020_6
#define M6020_1_7 CAN_1_6020_7

#define motor_2_1 CAN_2_1
#define motor_2_2 CAN_2_2
#define motor_2_3 CAN_2_3
#define motor_2_4 CAN_2_4
#define motor_2_5 CAN_2_5
#define motor_2_6 CAN_2_6
#define motor_2_7 CAN_2_7
#define motor_2_8 CAN_2_8
#define M6020_2_5 CAN_2_6020_5
#define M6020_2_6 CAN_2_6020_6
#define M6020_2_7 CAN_2_6020_7

#define motor_3_1 CAN_3_1
#define motor_3_2 CAN_3_2
#define motor_3_3 CAN_3_3
#define motor_3_4 CAN_3_4
#define motor_3_5 CAN_3_5
#define motor_3_6 CAN_3_6
#define motor_3_7 CAN_3_7
#define motor_3_8 CAN_3_8
#define M6020_3_5 CAN_3_6020_5
#define M6020_3_6 CAN_3_6020_6
#define M6020_3_7 CAN_3_6020_7



// ����������
#define ECD_MAX 8192.0f    // ���������ֵ
#define M3508_P 19.0f      //13.7f      // M3508������ٱ�
#define M2006_P 36.0f      // M2006������ٱ�
#define MAX_CURRENT 16384  // M2006+M3508������ 20A / MAX_CURRENT
#define MAX_6020_VOL 30000 // 6020����ѹ 24V / MAX_6020_VOL

// rm motor data
// notice:Ĭ��Ϊ3508���
// 3508/2006�õ��ǵ�����6020�õ��ǵ�ѹ
typedef struct
{
  int16_t set; // �趨�ĵ��� / ��ѹ

  // ԭʼ����
  uint16_t ecd;          // ��������ֵ
  int16_t speed_rpm;     // ת��
  int16_t given_current; // ������ĵ���
  uint8_t temperate;     // �¶ȣ���ȡ������
  int16_t last_ecd;      // ��һ�α���������ֵ

  // ��������
  long long ecd_cnt;  // ������������
  double angle_cnt;   // ת�����ܽǶ� degree
  double angle_zero;  // ������0��Ƕ� degree
  double angle;       // -180~180 degree
  double round_speed; // ������ת�ٶ� degree/s
	
} motor_measure_t;

extern motor_measure_t motor_data[33];

void can_filter_init(void);

uint8_t fdcanx_send_data(FDCAN_HandleTypeDef *hfdcan, uint16_t id, uint8_t *data, uint32_t len);
uint8_t fdcanx_receive(FDCAN_HandleTypeDef *hfdcan,	FDCAN_RxHeaderTypeDef *fdcan_RxHeader, uint8_t *buf);

void get_motor_measure(motor_measure_t *ptr, uint8_t data[]);
void process_motor_data(motor_measure_t *motor_data);
void decode_as_3508(can_id motorID);
void decode_as_2006(can_id motorID);
void decode_as_6020(can_id motorID);

void decode_as_3508_Yaw_Root(can_id motorID);//  19*52.56/28.65
void decode_as_3508_Pitch_Root(can_id motorID);//  19*70.03/22.28
void decode_as_2006_Roll_Root(can_id motorID);//  36*91.5/33
void decode_as_2006_pitch_end(can_id motorID);


motor_measure_t get_motor_data(can_id motorID); // ��ȡ�������

void set_motor(int16_t val, can_id motorID); // �趨������
void set_motor_offset(can_id motorID, float angle);
void clear_motor_cnt(can_id motorID);

void CAN1_send_current(void); // ���͵�����Ƶ���
void CAN2_send_current(void); // ���͵�����Ƶ���
void CAN3_send_current(void); // ���͵�����Ƶ���


#endif /* __CAN_RECEIVE_SEND_H__ */






