/**
 * @file Stm32_time.h
 * @author sethome 
 * @brief STM32F4的开机时间计算
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 #ifndef __STM32_TIME_H
#define __STM32_TIME_H

#include "cover_headerfile_h.h"

// 获取系统时间
uint32_t Get_sys_time_ms(void); // recommend
uint32_t Get_sys_time_us(void);

float Get_sys_time_s(void);

void TIM_count_100KHz(void);
#endif





// end of file
