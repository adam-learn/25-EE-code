/**
 * @file PWM_control.c
 * @author sethome (you@domain.com)  
 * @brief PWM����
 * 		  PS: IO1-8(6,7Ĭ��Ϊ���룬���޸Ĳ�����)
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "cover_headerfile_h.h" 
#include "PWM_control.h"


//��ʱ������
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim12;

float vbus;

	const uint16_t tone[] ={3817,3401,3030,2865,2552,2272,2024,//do~xi 0-6 ����
						//							0	  1     2    3    4    5    6
													1912,1703,1517,1432,1275,1136,1012,//7-13 ����
						//							 7     8    9   10    11   12   13
													956,  851,758, 715,  637,568, 506};//14-20 ����
						//							14    15   16   17    18  19   20
													
	uint8_t music_tone[200] = {5,7,11,7,3,4,5,11,7,  0,4,11,7,0,11,6,11,  5,7,11,5,3,4,5,11,7,  0,4,11,7,0,11,6,7,11,
												 		 5,7,11,7,3,4,5,11,0,  0,4,11,7,0,11,6,11,  5,7,11,5,3,4,5,11,7,  0,4,11,7,0,11,6,7,11,
							               11,11,7,7,8,9, 11,11,7,7,8,9,8,7,4,11,11,7,7,8,9 ,9,8,9,10,9,8,11,9,8,7};
		
  uint8_t music_time[200] = {2,2, 2,2, 2,1,1,2,2, 2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,1,2,
							               2,2, 2,2, 2,1,1,2,2, 2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,1,2,
							               2,2,2,2,4,2,2,2,2,2,2,1,1,1,1,2,2,2,2,4,2,2,4,1,1,1,1,1,1,1,1,2};


void TIM_IT_init(void)
{
	HAL_TIM_Base_Start_IT(&htim6);  // ʹ�ܸ����жϣ�1000HZ
	HAL_TIM_Base_Start_IT(&htim7);  // ʹ�ܸ����жϣ�1000HZ
	HAL_TIM_Base_Start_IT(&htim13); // ʹ�ܸ����жϣ�1000HZ
	HAL_TIM_Base_Start_IT(&htim14); // ʹ�ܸ����жϣ�1000HZ	
	HAL_TIM_Base_Start_IT(&htim16); // ʹ�ܸ����жϣ�1000HZ
}



//��ʼ��
void PWM_control_init(void)
{
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_Base_Start(&htim2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);//������PWM
//	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);	//���ȵ���PWM,������	
}


//��ʼ��snail���
void PWM_snail_init(uint8_t channel)
{
	set_PIN_PWM(channel, 1200);
}
void PWM_snail_set(uint8_t channel, uint16_t CCR)
{
	set_PIN_PWM(channel, CCR);
}
void PWM_snail_change_vector(uint8_t channel)
{
	set_PIN_PWM(channel, 1200);
	HAL_Delay(1000);
	set_PIN_PWM(channel, 20000);
}



//�趨����Ƕ�
void set_servo_angle(uint8_t channel, float angle) //ͳһ��180���
{
	uint16_t CCR = (1500.0 / 180.0) * angle + 500;
	switch (channel)
	{
	case PWM_PIN_1:
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, CCR);
		break;
	case PWM_PIN_2:
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, CCR);
		break;
	case PWM_PIN_3:
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, CCR);
		break;
	case PWM_PIN_4:
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, CCR);
		break;
	}
}


//�趨PWM��ռ�ձ�
void set_PIN_PWM(uint8_t channel, uint16_t CCR)
{
	switch (channel)
	{
	case PWM_PIN_1:
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, CCR);
		break;
	case PWM_PIN_2:
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, CCR);
		break;
	case PWM_PIN_3:
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, CCR);
		break;
	case PWM_PIN_4:
		__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, CCR);
	}
}





void buzzer_music_set_pwm(uint16_t period, uint16_t pulse)
{
	__HAL_TIM_SetAutoreload(&htim12,period);
		__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,pulse);	
	
}


void Sunny_Day_Jay(void)//
{		
	uint8_t i;	
		for(i=0; i<20; i++)  //�ɸ���ʱ�䣬 ԭʱ��Ϊ101
		{
			buzzer_music_set_pwm(tone[music_tone[i]],tone[music_tone[i]]/2); 
			HAL_Delay(music_time[i]*62.5*4);
		}
		__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,0);					
}




uint32_t adc_get_result(void)
{
    HAL_ADC_Start(&hadc1);//����ת��ģʽ��ÿ��ת����ɺ�ADCת�����Զ�ֹͣ
    HAL_ADC_PollForConversion(&hadc1, 10);//ADCת����ת������ms
    return (uint16_t)HAL_ADC_GetValue(&hadc1);
}








// end of file
