#ifndef __NUC_COMMUNICATION_H__
#define __NUC_COMMUNICATION_H__

#include "cover_headerfile_h.h"


typedef struct 
 {
 	uint8_t header;                               //1
 	float Q0,Q1,Q2,Q3;	                          //16 
 	float yaw,pitch;                              //8	 	 
 	float x_speed,y_speed,r_speed;	              //12 
 	uint8_t bullet;                               //1
 	uint8_t distance;                             //1
	float robot_speed_mps;                        //4
	uint8_t mode;	                                //1
  uint8_t	enemy_color;                          //1
	uint8_t enemy_blood_[7];                      //7
	uint32_t time_data;                           //4
 	char unknow[6];                               //6
	uint16_t checksum;                            //2
 }__attribute__((packed))	STM32_data_t;
extern STM32_data_t toNUC;

typedef struct
{
	uint8_t header;																//1
	uint8_t useless;															//1
	uint8_t target_id;														//1
	float yaw;																		//4
	float pitch;																	//4
	float pitch_speed;														//4
	float yaw_speed;															//4 
	uint8_t distance;															//1
  uint8_t shoot;																//1  
	uint8_t shoot_mode;														//1 
	uint32_t his_time_data;												//4
	char unknown[4];															//4  
	uint16_t checksum;														//2
} __attribute__((packed)) NUC_data_t;
extern NUC_data_t fromNUC;


//对STM32向NUC的信息解/编码
int encodeSTM32(STM32_data_t *target, unsigned char tx_buff[], unsigned int len);
int decodeSTM32(STM32_data_t *target, unsigned char rx_buff[], unsigned int len);

//对NUC向STM32的信息解/编码
int decodeNUC(NUC_data_t *target, unsigned char rx_buff[], unsigned int len);
int encodeNUC(NUC_data_t *target, unsigned char tx_buff[], unsigned int len);

void board_to_nuc(STM32_data_t *toNUC_t);

#endif





