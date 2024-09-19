#include "cover_headerfile_h.h"
#include "custom_controller_dataSendTask.h"


ext_custom_controller_data_t custom_controller_data;
unsigned char custom_controller_Send[39];
uint8_t seq = 0;

/**********************************************************************************************************
*�� �� ��: 
*����˵��: ���ݴ������
*��    ��: uint8_t sof,uint16_t cmd_id, uint8_t *p_data, uint16_t len
*�� �� ֵ: ��
**********************************************************************************************************/
void custom_controller_data_pack_handle(uint8_t sof,uint16_t cmd_id, uint8_t *p_data, uint16_t len)
{
	uint16_t frame_length = frameheader_len + cmd_len + len + crc_len;   //����֡����	

	memset(custom_controller_Send,0,frame_length);  //�洢���ݵ���������
	
	/*****֡ͷ���*****/
	custom_controller_Send[0] = sof;//����֡��ʼ�ֽ�
	memcpy(&custom_controller_Send[1],(uint8_t*)&len,2);//����֡��data�ĳ���
	custom_controller_Send[3] = seq;//�����
	append_CRC8_check_sum(custom_controller_Send,frameheader_len);  //֡ͷУ��CRC8

	/*****��������*****/
	memcpy(&custom_controller_Send[frameheader_len],(uint8_t*)&cmd_id, cmd_len);
	
	/*****���ݴ��*****/
	memcpy(&custom_controller_Send[frameheader_len+cmd_len],p_data,len);
	append_CRC16_check_sum(custom_controller_Send,frame_length);  //һ֡����У��CRC16

	if (seq == 0xff) seq=0;
  else seq++;
//	HAL_UART_Transmit(&huart1, custom_controller_Send, 39, 1000);
  ////HAL_UART_Transmit_DMA(&huart1,custom_controller_Send,39);
}
