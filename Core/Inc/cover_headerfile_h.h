#ifndef  __COVER_HEADERFILE_H_H__
#define  __COVER_HEADERFILE_H_H__


#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "string.h"
#include "struct_typedef.h"

#include "cmsis_os.h"
#include "adc.h"
#include "tim.h"
#include "fdcan.h"
#include "usart.h"

#include "iwdg.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_uart.h"


//Algorithm
#include "pid.h"
#include "fifo.h"
#include "AHRS.h"
#include "MahonyAHRS.h"
#include "madgwick.h"
#include "Kalman_Filter_c.h"
#include "bsxlite_interface.h"
#include "CRC8_CRC16.h"
#include "fdacoefs.h"
#include "user_lib.h"


//Applications/hardware
#include "IMU_updata.h"
#include "can_receive_send.h"
#include "UART_data_transmit.h"
#include "DBUS_remote_control.h"
#include "PWM_control.h"
#include "USB_VirCom.h"
#include "Stm32_time.h"
#include "ws2812.h"
#include "cap_ctl.h"


//Applications/software
#include "Global_status.h"
#include "Error_detect.h"
#include "NUC_communication.h"
#include "referee_usart_task.h"
#include "referee_handle_pack.h"
#include "protocol.h"
#include "custom_controller_dataSendTask.h"


//Applications/Feature
#include "chassis_move.h"
#include "gimbal.h"
#include "shoot.h"
#include "engine.h"


//Applications/Task
#include "MotionTask.h"
#include "DT7_remote_control.h"
#include "WFLY_ET16_remote_control.h"


//Devices
#include "BMI088driver.h"
#include "BMI088Middleware.h"
#include "w25q64.h"

	
extern unsigned long ulTdleCycleCount;	
extern unsigned long TIMER_0X01;	
extern unsigned long TIMER_0X02;	
extern unsigned long TIMER_0X03;	
extern unsigned long TIMER_0X04;	
extern unsigned long TIMER_0X05;	
extern unsigned long TIMER_0X06;	
extern float input_voltage_t;



#endif


