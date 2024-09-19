/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cover_headerfile_h.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */



/* USER CODE END Variables */
/* Definitions for Flash_LED_Task */
osThreadId_t Flash_LED_TaskHandle;
const osThreadAttr_t Flash_LED_Task_attributes = {
  .name = "Flash_LED_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for CAN_sendTask */
osThreadId_t CAN_sendTaskHandle;
const osThreadAttr_t CAN_sendTask_attributes = {
  .name = "CAN_sendTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for ChassisTask */
osThreadId_t ChassisTaskHandle;
const osThreadAttr_t ChassisTask_attributes = {
  .name = "ChassisTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for GimbalTask */
osThreadId_t GimbalTaskHandle;
const osThreadAttr_t GimbalTask_attributes = {
  .name = "GimbalTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for ShootTask */
osThreadId_t ShootTaskHandle;
const osThreadAttr_t ShootTask_attributes = {
  .name = "ShootTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for EngineTask */
osThreadId_t EngineTaskHandle;
const osThreadAttr_t EngineTask_attributes = {
  .name = "EngineTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Motion_modeTask */
osThreadId_t Motion_modeTaskHandle;
const osThreadAttr_t Motion_modeTask_attributes = {
  .name = "Motion_modeTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for RC_Task */
osThreadId_t RC_TaskHandle;
const osThreadAttr_t RC_Task_attributes = {
  .name = "RC_Task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for RM_RefereeTask */
osThreadId_t RM_RefereeTaskHandle;
const osThreadAttr_t RM_RefereeTask_attributes = {
  .name = "RM_RefereeTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CommTask */
osThreadId_t CommTaskHandle;
const osThreadAttr_t CommTask_attributes = {
  .name = "CommTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Flash_LED_Task_callback(void *argument);
void CAN_sendTask_callback(void *argument);
void ChassisTask_callback(void *argument);
void GimbalTask_callback(void *argument);
void ShootTask_callback(void *argument);
void EngineTask_callback(void *argument);
void Motion_modeTask_callback(void *argument);
void RC_Task_callback(void *argument);
void RM_RefereeTask_callback(void *argument);
void CommTask_callback(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
		ulTdleCycleCount++;
		input_voltage_t	= (adc_get_result()*3.3f/65535)*11.0f;		
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Flash_LED_Task */
  Flash_LED_TaskHandle = osThreadNew(Flash_LED_Task_callback, NULL, &Flash_LED_Task_attributes);

  /* creation of CAN_sendTask */
  CAN_sendTaskHandle = osThreadNew(CAN_sendTask_callback, NULL, &CAN_sendTask_attributes);

  /* creation of ChassisTask */
  ChassisTaskHandle = osThreadNew(ChassisTask_callback, NULL, &ChassisTask_attributes);

  /* creation of GimbalTask */
  GimbalTaskHandle = osThreadNew(GimbalTask_callback, NULL, &GimbalTask_attributes);

  /* creation of ShootTask */
  ShootTaskHandle = osThreadNew(ShootTask_callback, NULL, &ShootTask_attributes);

  /* creation of EngineTask */
  EngineTaskHandle = osThreadNew(EngineTask_callback, NULL, &EngineTask_attributes);

  /* creation of Motion_modeTask */
  Motion_modeTaskHandle = osThreadNew(Motion_modeTask_callback, NULL, &Motion_modeTask_attributes);

  /* creation of RC_Task */
  RC_TaskHandle = osThreadNew(RC_Task_callback, NULL, &RC_Task_attributes);

  /* creation of RM_RefereeTask */
  RM_RefereeTaskHandle = osThreadNew(RM_RefereeTask_callback, NULL, &RM_RefereeTask_attributes);

  /* creation of CommTask */
  CommTaskHandle = osThreadNew(CommTask_callback, NULL, &CommTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Flash_LED_Task_callback */
/**
  * @brief  Function implementing the Flash_LED_Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Flash_LED_Task_callback */
void Flash_LED_Task_callback(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN Flash_LED_Task_callback */
  /* Infinite loop */
  for(;;)                       //LED灯闪烁，判断进程是否正常运行
  {
		WS2812_Ctrl(0, 0, 50);
		osDelay(100);
		WS2812_Ctrl(50, 0, 0);
		osDelay(100);	
		WS2812_Ctrl(0, 50, 0);
		osDelay(100);		
  }
  /* USER CODE END Flash_LED_Task_callback */
}

/* USER CODE BEGIN Header_CAN_sendTask_callback */
/**
* @brief Function implementing the CAN_sendTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CAN_sendTask_callback */
void CAN_sendTask_callback(void *argument)
{
  /* USER CODE BEGIN CAN_sendTask_callback */
  /* Infinite loop */
  for(;;)
  {
		//CAN1_send_current(); // 发送CAN1电机控制电流
    //osDelay(5);				
		CAN2_send_current(); // 发送CAN2电机控制电流
    osDelay(5);				
		CAN3_send_current(); // 发送CAN3电机控制电流
    osDelay(5);			
  }
  /* USER CODE END CAN_sendTask_callback */
}

/* USER CODE BEGIN Header_ChassisTask_callback */
/**
* @brief Function implementing the ChassisTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ChassisTask_callback */
void ChassisTask_callback(void *argument)
{
  /* USER CODE BEGIN ChassisTask_callback */
  /* Infinite loop */
  for(;;)
  {
		chassis.power_limit.Plimit = power_limit(chassis.wheel_current);//底盘功率控制Plimit值计算
		chassis_moto_speed_calc(Global.input.x_s,Global.input.y_s,Global.input.w_s);//底盘运动解算					
		osDelay(5);
  }
  /* USER CODE END ChassisTask_callback */
}

/* USER CODE BEGIN Header_GimbalTask_callback */
/**
* @brief Function implementing the GimbalTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GimbalTask_callback */
void GimbalTask_callback(void *argument)
{
  /* USER CODE BEGIN GimbalTask_callback */
  /* Infinite loop */
  for(;;)
  {	
		gimbal_pid_cal();//云台PID计算
		gimbal_updata();//云台参数更新
    osDelay(5);
  }
  /* USER CODE END GimbalTask_callback */
}

/* USER CODE BEGIN Header_ShootTask_callback */
/**
* @brief Function implementing the ShootTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ShootTask_callback */
void ShootTask_callback(void *argument)
{
  /* USER CODE BEGIN ShootTask_callback */
  /* Infinite loop */
  for(;;)
  {
		shoot_pid_cal();
		shoot_update();
		shoot_speed_limit();		
    osDelay(5);
  }
  /* USER CODE END ShootTask_callback */
}

/* USER CODE BEGIN Header_EngineTask_callback */
/**
* @brief Function implementing the EngineTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_EngineTask_callback */
void EngineTask_callback(void *argument)
{
  /* USER CODE BEGIN EngineTask_callback */
  /* Infinite loop */
  for(;;)
  {
		ENGINE_updata();
		ENGINE_pid_cal();
    osDelay(5);
  }
  /* USER CODE END EngineTask_callback */
}

/* USER CODE BEGIN Header_Motion_modeTask_callback */
/**
* @brief Function implementing the Motion_modeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Motion_modeTask_callback */
void Motion_modeTask_callback(void *argument)
{
  /* USER CODE BEGIN Motion_modeTask_callback */
  /* Infinite loop */
  for(;;)
  {
		MotionTask_mode_choose(Global.mode);
    osDelay(5);
  }
  /* USER CODE END Motion_modeTask_callback */
}

/* USER CODE BEGIN Header_RC_Task_callback */
/**
* @brief Function implementing the RC_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RC_Task_callback */
void RC_Task_callback(void *argument)
{
  /* USER CODE BEGIN RC_Task_callback */
  /* Infinite loop */
  for(;;)
  {
//		DT7_remote_control_task();//新步兵
		WFLY_remote_control_task();//工程		
    osDelay(5);
  }
  /* USER CODE END RC_Task_callback */
}

/* USER CODE BEGIN Header_RM_RefereeTask_callback */
/**
* @brief Function implementing the RM_RefereeTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RM_RefereeTask_callback */
void RM_RefereeTask_callback(void *argument)
{
  /* USER CODE BEGIN RM_RefereeTask_callback */
  /* Infinite loop */
  for(;;)
  {
		referee_usart_task();		
    Required_Data();				
//    custom_controller_data_pack_handle(0xA5,0x302,(uint8_t *)&custom_data_controller,30);		
    osDelay(10);
  }
  /* USER CODE END RM_RefereeTask_callback */
}

/* USER CODE BEGIN Header_CommTask_callback */
/**
* @brief Function implementing the CommTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CommTask_callback */
void CommTask_callback(void *argument)
{
  /* USER CODE BEGIN CommTask_callback */
		char matlab[256];
		uint8_t len = 0;		
  /* Infinite loop */
  for(;;)
  {
		board_uart_send_message(&H723_uart10_send);	
		board_uart_send_message(&H723_uart7_send);			
		HAL_UART_Transmit(UART10_data.huart,(uint8_t *)&H723_uart10_send,30,1000);	
		HAL_UART_Transmit(UART7_data.huart,(uint8_t *)&H723_uart7_send,30,1000);			
		len = sprintf (matlab,"ROBOMASTER\n\n\n",sizeof("ROBOMASTER\n\n\n"));
		VirCom_send((uint8_t*)matlab,len);

//		board_to_nuc(&toNUC);	
    osDelay(10);
  }
  /* USER CODE END CommTask_callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void vApplicationldleHook(void)
{

}

/* USER CODE END Application */

