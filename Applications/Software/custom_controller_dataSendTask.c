#include "cover_headerfile_h.h"
#include "custom_controller_dataSendTask.h"


ext_custom_controller_data_t custom_controller_data;
unsigned char custom_controller_Send[39];
uint8_t seq = 0;

/**********************************************************************************************************
*函 数 名: 
*功能说明: 数据打包发送
*形    参: uint8_t sof,uint16_t cmd_id, uint8_t *p_data, uint16_t len
*返 回 值: 无
**********************************************************************************************************/
void custom_controller_data_pack_handle(uint8_t sof,uint16_t cmd_id, uint8_t *p_data, uint16_t len)
{
	uint16_t frame_length = frameheader_len + cmd_len + len + crc_len;   //数据帧长度	

	memset(custom_controller_Send,0,frame_length);  //存储数据的数组清零
	
	/*****帧头打包*****/
	custom_controller_Send[0] = sof;//数据帧起始字节
	memcpy(&custom_controller_Send[1],(uint8_t*)&len,2);//数据帧中data的长度
	custom_controller_Send[3] = seq;//包序号
	append_CRC8_check_sum(custom_controller_Send,frameheader_len);  //帧头校验CRC8

	/*****命令码打包*****/
	memcpy(&custom_controller_Send[frameheader_len],(uint8_t*)&cmd_id, cmd_len);
	
	/*****数据打包*****/
	memcpy(&custom_controller_Send[frameheader_len+cmd_len],p_data,len);
	append_CRC16_check_sum(custom_controller_Send,frame_length);  //一帧数据校验CRC16

	if (seq == 0xff) seq=0;
  else seq++;
//	HAL_UART_Transmit(&huart1, custom_controller_Send, 39, 1000);
  ////HAL_UART_Transmit_DMA(&huart1,custom_controller_Send,39);
}
