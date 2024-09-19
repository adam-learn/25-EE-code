#ifndef __CUSTOM_CONTROLLER_DATASENDTASK_H 
#define __CUSTOM_CONTROLLER_DATASENDTASK_H 

#include "cover_headerfile_h.h"

#define SEND_MAX_SIZE    128    //上传数据最大的长度
#define frameheader_len  5       //帧头长度
#define cmd_len          2       //命令码长度
#define crc_len          2       //CRC16校验


extern uint8_t custom_controller_Send[39];

#pragma pack(1)
//交互数据信息
typedef struct         
{
	float data_0;
	float data_1;	
	float data_2;	
	float data_3;	
	float data_4;	
	float data_5;	
	float data_6;		
	short data_7;		
}ext_custom_controller_data_t;	
#pragma pack()

extern ext_custom_controller_data_t custom_controller_data;

void custom_controller_data_pack_handle(uint8_t sof,uint16_t cmd_id, uint8_t *p_data, uint16_t len);


#endif







