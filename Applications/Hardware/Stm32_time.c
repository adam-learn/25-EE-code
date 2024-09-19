/**
 * @file time.c
 * @author sethome
 * @brief STM32F4�Ŀ���ʱ�����
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "cover_headerfile_h.h"
#include "Stm32_time.h"

uint32_t Get_sys_time_ms(void)
{
	return HAL_GetTick();
}

float Get_sys_time_s(void)
{
	return HAL_GetTick() / 1000.0f;
}

uint32_t cnt = 0;
void TIM_count_100KHz(void)
{
	cnt+=10;
}
uint32_t Get_sys_time_us(void)
{
	return cnt;
}

//end of file
