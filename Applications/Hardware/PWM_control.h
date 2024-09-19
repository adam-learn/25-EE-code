/**
 * @file PWM_control.h
 * @author sethome 
 * @brief PWM控制头文件
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __PWM_CONTROL_H__
#define __PWM_CONTROL_H__


#include "cover_headerfile_h.h"

#define PWM_PIN_1 1
#define PWM_PIN_2 2
#define PWM_PIN_3 3
#define PWM_PIN_4 4

extern float vbus;

void TIM_IT_init(void);
void PWM_control_init(void);
void PWM_snail_init(uint8_t channel);
void PWM_snail_set(uint8_t channel, uint16_t CCR);
void PWM_snail_change_vector(uint8_t channel);
void set_servo_angle(uint8_t channel, float angle); //统一给180舵机
void set_PIN_PWM(uint8_t channel, uint16_t CCR);


void buzzer_music_set_pwm(uint16_t period, uint16_t pulse);
void Sunny_Day_Jay(void);
uint32_t adc_get_result(void);

#endif





