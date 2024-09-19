/**
 * @file UART_data_transmit.c
 * @author sethome
 * @brief 串口数据发送
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022 sethome
 *
 */
 ////来源于于sethome&DM例程，串口中断回调函数内包括串口5的遥控器解算
 
#include "cover_headerfile_h.h"
#include "UART_data_transmit.h"

//// DMA控制变量
extern DMA_HandleTypeDef hdma_uart5_rx;
extern DMA_HandleTypeDef hdma_uart5_tx;

extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_uart5_rx;
extern DMA_HandleTypeDef hdma_uart5_tx;
extern DMA_HandleTypeDef hdma_uart7_rx;
extern DMA_HandleTypeDef hdma_uart7_tx;
extern DMA_HandleTypeDef hdma_usart10_rx;
extern DMA_HandleTypeDef hdma_usart10_tx;

// 串口控制变量
extern UART_HandleTypeDef huart5;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart10;


// 将上述串口+DMA整合，并包含缓冲区
transmit_data UART1_data;
transmit_data UART5_data;
transmit_data UART7_data;
transmit_data UART10_data;


custom_board_comm_message_t H723_uart10_receive,H723_uart10_send,H723_uart7_receive,H723_uart7_send;


// 初始化串口
void uart_init(void)
{
  UART_DMA_rxtx_start(&UART1_data, &huart1, &hdma_usart1_rx, &hdma_usart1_tx);
	UART_DMA_rxtx_start(&UART5_data, &huart5, &hdma_uart5_rx, &hdma_uart5_tx);
  UART_DMA_rxtx_start(&UART7_data, &huart7, &hdma_uart7_rx, &hdma_uart7_tx);
	UART_DMA_rxtx_start(&UART10_data, &huart10, &hdma_usart10_rx, &hdma_usart10_tx);
}

// ヾ(?ω?`)o温馨提示，使用 DMA + 中断空闲，缓冲区爆了。。就是爆了 固定256位(可更改)，暂时没有给你自定义的打算
//  DMA，串口中断启动
void UART_DMA_rxtx_start(transmit_data *data, UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_usart_rx, DMA_HandleTypeDef *hdma_usart_tx)
{
  data->huart = huart;                 // 串口控制变量
  data->hdma_usart_rx = hdma_usart_rx; // DMA接收缓冲
  data->hdma_usart_tx = hdma_usart_tx; // DMA发送缓冲
//  HAL_UART_Receive_DMA(data->huart, data->rev_data, 1024); // 使能DMA	
//  __HAL_UART_ENABLE_IT(data->huart, UART_IT_RXNE); // 启动接收中断
//  __HAL_UART_ENABLE_IT(data->huart, UART_IT_IDLE); // 启动空闲中断
//  __HAL_DMA_ENABLE(hdma_usart_rx);                 // 启动DMA接收
	HAL_UARTEx_ReceiveToIdle_DMA(data->huart, data->rev_data, recv_buff_size);	
   __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);			
}


// 发送数据（数据别释放了，不然后面收不到）
void UART_send_data(transmit_data uart, uint8_t data[], uint16_t size)
{
  HAL_UART_Transmit_DMA(uart.huart, data, size); // 套娃ヾ(?ω?`)o
}

// //请放于UARTx_IRQHandler下，即UART全局中断函数
////=.=当然你想放在HAL_UART_RxCpltCallback也不是不行
void UART_rx_IRQHandler(transmit_data *uart)
{
		HAL_UARTEx_ReceiveToIdle_DMA(uart->huart, uart->rev_data, recv_buff_size*2); // 重新使能DMA缓冲区
   __HAL_DMA_DISABLE_IT(uart->huart->hdmarx, DMA_IT_HT);		
}


 void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{	

		if (huart == &huart1) // 
		{	
//			HAL_UARTEx_ReceiveToIdle_DMA(huart, UART1_data.rev_data, recv_buff_size);				
//			//fifo_s_puts(&referee_fifo, (char *)&UART1_data.rev_data, recv_buff_size);
//      __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);		
		}	
		else if(huart == &huart5)
		{	
				HAL_UARTEx_ReceiveToIdle_DMA(&huart5, UART5_data.rev_data, recv_buff_size); // 接收完毕后重启
				//update_sbus(UART5_data.rev_data,&SBUS_CH);	
				__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);				
		}			
		else if (huart == &huart7) // 
		{

			HAL_UARTEx_ReceiveToIdle_DMA(huart, UART7_data.rev_data, recv_buff_size);		
			memcpy(&H723_uart7_receive,UART7_data.rev_data,recv_buff_size);			
      __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);					
		}
		else if (huart == &huart10) // 
		{	

			HAL_UARTEx_ReceiveToIdle_DMA(huart, UART10_data.rev_data, recv_buff_size);
			memcpy(&H723_uart10_receive,UART10_data.rev_data,recv_buff_size);
     __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);					
		}	
////		else if(huart->Instance == USART2)
////		{
////			HAL_UARTEx_ReceiveToIdle_DMA(huart, UART1_data.rev_data, recv_buff_size);				
////      __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);					
////		}		
////		else if(huart->Instance == USART3)
////		{
////			HAL_UARTEx_ReceiveToIdle_DMA(huart, UART1_data.rev_data, recv_buff_size);				
////      __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);					
////		}

}





void board_uart_send_message(custom_board_comm_message_t *send_data)
{
//  send_data->test_float0 = IMU_data.AHRS.pitch;
//  send_data->test_float1 = IMU_data.AHRS.yaw;	
//  send_data->test_float2 = IMU_data.AHRS.roll;	
//  send_data->test_float3 = IMU_data.AHRS.q[0];	
//  send_data->test_float4 = IMU_data.AHRS.q[1];		
//	send_data->test_float5 = IMU_data.AHRS.q[2];	
//	send_data->test_float6 = IMU_data.AHRS.q[3];	
//	send_data->unknow = 10;	
}



//////// //请放于UARTx_IRQHandler下，即UART全局中断函数
//////////=.=当然你想放在HAL_UART_RxCpltCallback也不是不行
//////void UART_rx_IRQHandler(transmit_data *uart)
//////{
//////  uint16_t len = recv_buff_size; // 得到的数据长度

//////  if (uart->huart->Instance->ISR & UART_FLAG_RXNE) // 接受单字节中断
//////  {
//////    // 如果需要对单个字符处理，在此处
//////  }
//////  else if (uart->huart->Instance->ISR & UART_FLAG_IDLE) // 如果为空闲中断
//////  {
//////    HAL_UART_DMAStop(uart->huart); // 失效DMA

//////    len = recv_buff_size - __HAL_DMA_GET_COUNTER(uart->hdma_usart_rx); // 计算获得的字节长度
//////    // 此处放置处理函数，蟹蟹
//////    // 数据数组 = uart->rev_data ,长度 = len
//////    // 自发自收示例： UART_send_data(UART1_data,uart->rev_data,len);
//////    if (uart->huart == &huart1) // 
//////    {	
//////				HAL_UART_Receive_DMA(uart->huart, uart->rev_data, len);			
////////				HAL_UARTEx_ReceiveToIdle_DMA(uart->huart, uart->rev_data, len);		
//////			fifo_s_puts(&referee_fifo, (char *)&UART1_data.rev_data, recv_buff_size);			
//////    }
//////    else if (uart->huart == &huart7) // 
//////    {
//////				HAL_UART_Receive_DMA(uart->huart, uart->rev_data, len);		
////////				HAL_UARTEx_ReceiveToIdle_DMA(uart->huart, uart->rev_data, len);	
//////			memcpy(&H723_uart7_receive,UART7_data.rev_data,recv_buff_size);					
//////    }
//////    else if (uart->huart == &huart10) // 
//////    {	
//////				HAL_UART_Receive_DMA(uart->huart, uart->rev_data, len);	
////////				HAL_UARTEx_ReceiveToIdle_DMA(uart->huart, uart->rev_data, len);	
//////			memcpy(&H723_uart10_receive,UART10_data.rev_data,recv_buff_size);			
//////    }		
//////		
//////    // 清除数据
//////    for (int p = 0; p < recv_buff_size; p++)
//////      uart->rev_data[p] = 0;
//////    __HAL_UART_CLEAR_IDLEFLAG(uart->huart);                 // 清除空闲中断标志
//////    __HAL_UART_CLEAR_PEFLAG(uart->huart);                   // 清除等待标志
//////    HAL_UART_Receive_DMA(uart->huart, uart->rev_data, recv_buff_size); // 重新使能DMA缓冲区
////////		HAL_UARTEx_ReceiveToIdle_DMA(uart->huart, uart->rev_data, recv_buff_size); // 重新使能DMA缓冲区
//////  }
//////  __HAL_UART_CLEAR_PEFLAG(uart->huart); // 清除等待标志
//////}






//////void BEGIN_UART_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
//////{
//////    //enable the DMA transfer for the receiver request
//////    //使能DMA串口接收
//////    SET_BIT(huart7.Instance->CR3, USART_CR3_DMAR);

//////    //enalbe idle interrupt
//////    //使能空闲中断
//////    __HAL_UART_ENABLE_IT(&huart7, UART_IT_IDLE);

//////    //disable DMA
//////    //失效DMA
//////    __HAL_DMA_DISABLE(&hdma_uart7_rx);
//////    while(((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->CR & DMA_SxCR_EN)
//////    {
//////        __HAL_DMA_DISABLE(&hdma_uart7_rx);
//////    }

//////    ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->PAR = (uint32_t) & (UART7->RDR);
//////    //memory buffer 1
//////    //内存缓冲区1
//////    ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->M0AR = (uint32_t)(rev_data_0);
//////    //memory buffer 2
//////    //内存缓冲区2
//////    ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->M1AR = (uint32_t)(rev_data_1);
//////    //data length
//////    //数据长度
//////    ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR = dma_buf_num;
//////    //enable double memory buffer
//////    //使能双缓冲区
//////    SET_BIT(((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->CR, DMA_SxCR_DBM);

//////    //enable DMA
//////    //使能DMA
//////    __HAL_DMA_ENABLE(&hdma_uart7_rx);

//////}



//////void UART7_IRQHandler(void)
//////{
//////  /* USER CODE BEGIN UART7_IRQn 0 */

//////  /* USER CODE END UART7_IRQn 0 */
//////  HAL_UART_IRQHandler(&huart7);
//////  /* USER CODE BEGIN UART7_IRQn 1 */
////////  UART_rx_IRQHandler(&UART7_data);//来源于sethome
//////	
//////	
//////	    if(huart7.Instance->ISR & UART_FLAG_RXNE)//接收到数据
//////    {
//////        __HAL_UART_CLEAR_PEFLAG(&huart7);
//////    }
//////    else if(UART7->ISR & UART_FLAG_IDLE)
//////    {
//////        static uint16_t this_time_rx_len = 0;

//////        __HAL_UART_CLEAR_PEFLAG(&huart7);

//////        if ((((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->CR & DMA_SxCR_CT) == RESET)
//////        {
//////            /* Current memory buffer used is Memory 0 */
//////    
//////            //disable DMA
//////            //失效DMA
//////            __HAL_DMA_DISABLE(&hdma_uart7_rx);

//////            //get receive data length, length = set_data_length - remain_length
//////            //获取接收数据长度,长度 = 设定长度 - 剩余长度
//////            this_time_rx_len = recv_buff_size - ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR;

//////            //reset set_data_lenght
//////            //重新设定数据长度
//////            ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR = recv_buff_size;

//////            //set memory buffer 1
//////            //设定缓冲区1
//////            ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->CR |= DMA_SxCR_CT;
//////            
//////            //enable DMA
//////            //使能DMA
//////            __HAL_DMA_ENABLE(&hdma_uart7_rx);

//////            if(this_time_rx_len == recv_buff_size)
//////            {
///////////                sbus_to_rc(sbus_rx_buf[0], &rc_ctrl);
//////							
//////							memcpy(&H723_uart7_receive,rev_data_0,recv_buff_size);
//////            }
//////        }
//////        else
//////        {
//////            /* Current memory buffer used is Memory 1 */
//////            //disable DMA
//////            //失效DMA
//////            __HAL_DMA_DISABLE(&hdma_uart7_rx);

//////            //get receive data length, length = set_data_length - remain_length
//////            //获取接收数据长度,长度 = 设定长度 - 剩余长度
//////            this_time_rx_len = recv_buff_size - ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR;

//////            //reset set_data_lenght
//////            //重新设定数据长度
//////            ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR = recv_buff_size;

//////            //set memory buffer 0
//////            //设定缓冲区0
//////            DMA1_Stream4->CR &= ~(DMA_SxCR_CT);
//////            
//////            //enable DMA
//////            //使能DMA
//////            __HAL_DMA_ENABLE(&hdma_uart7_rx);

//////            if(this_time_rx_len == recv_buff_size)
//////            {
//////                //处理遥控器数据
////// ////               sbus_to_rc(sbus_rx_buf[1], &rc_ctrl);
//////							memcpy(&H723_uart7_receive,rev_data_1,recv_buff_size);
//////            }
//////        }
//////    }
//////	
//////	
//////	
//////  /* USER CODE END UART7_IRQn 1 */
//////}

