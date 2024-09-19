/**
 * @file USB_VirCom.c
 * @author sethome
 * @brief 虚拟串口数据发送
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "cover_headerfile_h.h" 
#include "usbd_cdc_if.h"
#include "USB_VirCom.h"
	
void VirCom_send(uint8_t data[], uint16_t len)
{
  CDC_Transmit_HS(data, len);
}


void VirCom_rev(uint8_t data[], uint16_t len)
{
//	uint16_t sum;
  if (data[0] == (unsigned)'s')
  {		
//		if(Verify_CRC16_Check_Sum(data,sizeof(NUC_data_t)))
		decodeNUC(&fromNUC,data,len);
  }
}


