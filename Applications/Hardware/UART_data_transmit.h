/**
 * @file UART_data_transmit.h
 * @author sethome
 * @brief 串口数据发送
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __UART_DATA_TRANSMIT__
#define __UART_DATA_TRANSMIT__


#include "cover_headerfile_h.h"


#define  recv_buff_size 256

//串口数据结构体
typedef struct
{
  UART_HandleTypeDef *huart;
	DMA_HandleTypeDef  *hdma_usart_rx;
  DMA_HandleTypeDef  *hdma_usart_tx;
  uint8_t rev_data[recv_buff_size];
} transmit_data;

extern transmit_data UART1_data;
extern transmit_data UART5_data;
extern transmit_data UART7_data;
extern transmit_data UART10_data;

////外部调用
void uart_init(void);                                                                                                                         //初始化
void UART_DMA_rxtx_start(transmit_data *data, UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_usart_rx, DMA_HandleTypeDef *hdma_usart_tx); //初始化
void UART_rx_IRQHandler(transmit_data *uart);                                                                                                 //接受中断
void UART_send_data(transmit_data uart, uint8_t data[], uint16_t size);                                                                       //发送




#pragma pack(1)
 //交互数据信息
typedef struct         
{
	float test_float0;
	float test_float1;	
	float test_float2;	
	float test_float3;
	float test_float4;
	float test_float5;
	float test_float6;
	short unknow;
}custom_board_comm_message_t;	

#pragma pack()


extern custom_board_comm_message_t H723_uart10_receive,H723_uart10_send,H723_uart7_receive,H723_uart7_send;

void board_uart_send_message(custom_board_comm_message_t *send_data);



#endif




// end of file
