/**
 * @file UART_data_transmit.c
 * @author sethome
 * @brief �������ݷ���
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022 sethome
 *
 */
 ////��Դ����sethome&DM���̣������жϻص������ڰ�������5��ң��������
 
#include "cover_headerfile_h.h"
#include "UART_data_transmit.h"

//// DMA���Ʊ���
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

// ���ڿ��Ʊ���
extern UART_HandleTypeDef huart5;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart10;


// ����������+DMA���ϣ�������������
transmit_data UART1_data;
transmit_data UART5_data;
transmit_data UART7_data;
transmit_data UART10_data;


custom_board_comm_message_t H723_uart10_receive,H723_uart10_send,H723_uart7_receive,H723_uart7_send;


// ��ʼ������
void uart_init(void)
{
  UART_DMA_rxtx_start(&UART1_data, &huart1, &hdma_usart1_rx, &hdma_usart1_tx);
	UART_DMA_rxtx_start(&UART5_data, &huart5, &hdma_uart5_rx, &hdma_uart5_tx);
  UART_DMA_rxtx_start(&UART7_data, &huart7, &hdma_uart7_rx, &hdma_uart7_tx);
	UART_DMA_rxtx_start(&UART10_data, &huart10, &hdma_usart10_rx, &hdma_usart10_tx);
}

// �d(?��?`)o��ܰ��ʾ��ʹ�� DMA + �жϿ��У����������ˡ������Ǳ��� �̶�256λ(�ɸ���)����ʱû�и����Զ���Ĵ���
//  DMA�������ж�����
void UART_DMA_rxtx_start(transmit_data *data, UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_usart_rx, DMA_HandleTypeDef *hdma_usart_tx)
{
  data->huart = huart;                 // ���ڿ��Ʊ���
  data->hdma_usart_rx = hdma_usart_rx; // DMA���ջ���
  data->hdma_usart_tx = hdma_usart_tx; // DMA���ͻ���
//  HAL_UART_Receive_DMA(data->huart, data->rev_data, 1024); // ʹ��DMA	
//  __HAL_UART_ENABLE_IT(data->huart, UART_IT_RXNE); // ���������ж�
//  __HAL_UART_ENABLE_IT(data->huart, UART_IT_IDLE); // ���������ж�
//  __HAL_DMA_ENABLE(hdma_usart_rx);                 // ����DMA����
	HAL_UARTEx_ReceiveToIdle_DMA(data->huart, data->rev_data, recv_buff_size);	
   __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);			
}


// �������ݣ����ݱ��ͷ��ˣ���Ȼ�����ղ�����
void UART_send_data(transmit_data uart, uint8_t data[], uint16_t size)
{
  HAL_UART_Transmit_DMA(uart.huart, data, size); // ���ީd(?��?`)o
}

// //�����UARTx_IRQHandler�£���UARTȫ���жϺ���
////=.=��Ȼ�������HAL_UART_RxCpltCallbackҲ���ǲ���
void UART_rx_IRQHandler(transmit_data *uart)
{
		HAL_UARTEx_ReceiveToIdle_DMA(uart->huart, uart->rev_data, recv_buff_size*2); // ����ʹ��DMA������
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
				HAL_UARTEx_ReceiveToIdle_DMA(&huart5, UART5_data.rev_data, recv_buff_size); // ������Ϻ�����
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



//////// //�����UARTx_IRQHandler�£���UARTȫ���жϺ���
//////////=.=��Ȼ�������HAL_UART_RxCpltCallbackҲ���ǲ���
//////void UART_rx_IRQHandler(transmit_data *uart)
//////{
//////  uint16_t len = recv_buff_size; // �õ������ݳ���

//////  if (uart->huart->Instance->ISR & UART_FLAG_RXNE) // ���ܵ��ֽ��ж�
//////  {
//////    // �����Ҫ�Ե����ַ������ڴ˴�
//////  }
//////  else if (uart->huart->Instance->ISR & UART_FLAG_IDLE) // ���Ϊ�����ж�
//////  {
//////    HAL_UART_DMAStop(uart->huart); // ʧЧDMA

//////    len = recv_buff_size - __HAL_DMA_GET_COUNTER(uart->hdma_usart_rx); // �����õ��ֽڳ���
//////    // �˴����ô�������зз
//////    // �������� = uart->rev_data ,���� = len
//////    // �Է�����ʾ���� UART_send_data(UART1_data,uart->rev_data,len);
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
//////    // �������
//////    for (int p = 0; p < recv_buff_size; p++)
//////      uart->rev_data[p] = 0;
//////    __HAL_UART_CLEAR_IDLEFLAG(uart->huart);                 // ��������жϱ�־
//////    __HAL_UART_CLEAR_PEFLAG(uart->huart);                   // ����ȴ���־
//////    HAL_UART_Receive_DMA(uart->huart, uart->rev_data, recv_buff_size); // ����ʹ��DMA������
////////		HAL_UARTEx_ReceiveToIdle_DMA(uart->huart, uart->rev_data, recv_buff_size); // ����ʹ��DMA������
//////  }
//////  __HAL_UART_CLEAR_PEFLAG(uart->huart); // ����ȴ���־
//////}






//////void BEGIN_UART_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
//////{
//////    //enable the DMA transfer for the receiver request
//////    //ʹ��DMA���ڽ���
//////    SET_BIT(huart7.Instance->CR3, USART_CR3_DMAR);

//////    //enalbe idle interrupt
//////    //ʹ�ܿ����ж�
//////    __HAL_UART_ENABLE_IT(&huart7, UART_IT_IDLE);

//////    //disable DMA
//////    //ʧЧDMA
//////    __HAL_DMA_DISABLE(&hdma_uart7_rx);
//////    while(((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->CR & DMA_SxCR_EN)
//////    {
//////        __HAL_DMA_DISABLE(&hdma_uart7_rx);
//////    }

//////    ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->PAR = (uint32_t) & (UART7->RDR);
//////    //memory buffer 1
//////    //�ڴ滺����1
//////    ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->M0AR = (uint32_t)(rev_data_0);
//////    //memory buffer 2
//////    //�ڴ滺����2
//////    ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->M1AR = (uint32_t)(rev_data_1);
//////    //data length
//////    //���ݳ���
//////    ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR = dma_buf_num;
//////    //enable double memory buffer
//////    //ʹ��˫������
//////    SET_BIT(((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->CR, DMA_SxCR_DBM);

//////    //enable DMA
//////    //ʹ��DMA
//////    __HAL_DMA_ENABLE(&hdma_uart7_rx);

//////}



//////void UART7_IRQHandler(void)
//////{
//////  /* USER CODE BEGIN UART7_IRQn 0 */

//////  /* USER CODE END UART7_IRQn 0 */
//////  HAL_UART_IRQHandler(&huart7);
//////  /* USER CODE BEGIN UART7_IRQn 1 */
////////  UART_rx_IRQHandler(&UART7_data);//��Դ��sethome
//////	
//////	
//////	    if(huart7.Instance->ISR & UART_FLAG_RXNE)//���յ�����
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
//////            //ʧЧDMA
//////            __HAL_DMA_DISABLE(&hdma_uart7_rx);

//////            //get receive data length, length = set_data_length - remain_length
//////            //��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
//////            this_time_rx_len = recv_buff_size - ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR;

//////            //reset set_data_lenght
//////            //�����趨���ݳ���
//////            ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR = recv_buff_size;

//////            //set memory buffer 1
//////            //�趨������1
//////            ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->CR |= DMA_SxCR_CT;
//////            
//////            //enable DMA
//////            //ʹ��DMA
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
//////            //ʧЧDMA
//////            __HAL_DMA_DISABLE(&hdma_uart7_rx);

//////            //get receive data length, length = set_data_length - remain_length
//////            //��ȡ�������ݳ���,���� = �趨���� - ʣ�೤��
//////            this_time_rx_len = recv_buff_size - ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR;

//////            //reset set_data_lenght
//////            //�����趨���ݳ���
//////            ((DMA_Stream_TypeDef   *)hdma_uart7_rx.Instance)->NDTR = recv_buff_size;

//////            //set memory buffer 0
//////            //�趨������0
//////            DMA1_Stream4->CR &= ~(DMA_SxCR_CT);
//////            
//////            //enable DMA
//////            //ʹ��DMA
//////            __HAL_DMA_ENABLE(&hdma_uart7_rx);

//////            if(this_time_rx_len == recv_buff_size)
//////            {
//////                //����ң��������
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

