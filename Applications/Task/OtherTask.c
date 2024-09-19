#include "cover_headerfile_h.h"
#include "OtherTask.h"






//void RC_Task_callback(void *argument)
//{
//  /* USER CODE BEGIN RC_Task_callback */
//  /* Infinite loop */
//  for(;;)
//  {
////		DT7_remote_control_task();//新步兵
//		WFLY_remote_control_task();//工程		
//    osDelay(5);
//  }
//  /* USER CODE END RC_Task_callback */
//}


//void Motion_modeTask_callback(void *argument)
//{
//  /* USER CODE BEGIN Motion_modeTask_callback */
//  /* Infinite loop */
//  for(;;)
//  {
//		MotionTask_mode_choose(Global.mode);
//    osDelay(5);
//  }
//  /* USER CODE END Motion_modeTask_callback */
//}



//void RM_RefereeTask_callback(void *argument)
//{
//  /* USER CODE BEGIN RefereeTask_callback */
//  /* Infinite loop */
//  for(;;)
//  {
//		referee_usart_task();		
//    Required_Data();				
////    custom_controller_data_pack_handle(0xA5,0x302,(uint8_t *)&custom_data_controller,30);		
//    osDelay(10);
//  }
//  /* USER CODE END RefereeTask_callback */
//}

//void CommTask_callbaack(void *argument)
//{
//  /* USER CODE BEGIN CommTask_callbaack */
//		char matlab[256];
//		uint8_t len = 0;	
//  /* Infinite loop */
//  for(;;)
//  {
//		board_uart_send_message(&H723_uart10_send);	
//		HAL_UART_Transmit_DMA(UART10_data.huart,(uint8_t *)&H723_uart10_send,30);	
//		
//	 len = sprintf (matlab,"I_LOVE_U\n\n\n",sizeof("I_LOVE_U"));
//	 VirCom_send((uint8_t*)matlab,len);

////		board_to_nuc(&toNUC);	
//    osDelay(10);
//  }
//  /* USER CODE END CommTask_callbaack */
//}


