/**
 * @file Error_detect.c
 * @author sethome
 * @brief ������
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Error_detect.h"
#include "CAN_receive&send.h"
#include "gimbal.h"
#include "chassis_move.h"
#include "shoot.h"
#include "global_status.h"
#include "Stm32_time.h"
#include "LED_control.h"

struct Error_detect_t Error_detect;

void Error_detect_init(void)
{
	
}

void Error_detect_flush(void)
{
    // ң�������
    static uint32_t last_remote = 0;
    if (last_remote == Error_detect.remote.last_time)
    {
        Global.err[REMOTE_ERR] = 1;
        Error_detect.remote.flag = 1;
    }
    else
    {
        Global.err[REMOTE_ERR] = 0;
        Error_detect.remote.flag = 0;
    }
    last_remote = Error_detect.remote.last_time;

    // ������
    Error_detect_motor(chassis_FR);
    Error_detect_motor(chassis_FL);
    Error_detect_motor(chassis_BL);
    Error_detect_motor(chassis_BR);
    if (Error_detect.motor.flag[chassis_FR] ||
        Error_detect.motor.flag[chassis_FL] ||
        Error_detect.motor.flag[chassis_BL] ||
        Error_detect.motor.flag[chassis_BR])
        Global.err[CHASSIS_ERR] = 1;
    else
        Global.err[CHASSIS_ERR] = 0;

    Error_detect_motor(YAW_MOTOR);
    Error_detect_motor(PITCH_MOTOR);
    if (Error_detect.motor.flag[YAW_MOTOR] ||
        Error_detect.motor.flag[PITCH_MOTOR])
        Global.err[GIMBAL_ERR] = 1;
    else
        Global.err[GIMBAL_ERR] = 0;

#ifdef USE_3508_AS_SHOOT_MOTOR
    Error_detect_motor(SHOOT_MOTOR1);
    Error_detect_motor(SHOOT_MOTOR2);
#endif

    Error_detect_motor(TRIGGER_MOTOR);
    if (Error_detect.motor.flag[TRIGGER_MOTOR] ||
        Error_detect.motor.flag[SHOOT_MOTOR1] ||
        Error_detect.motor.flag[SHOOT_MOTOR2])
        Global.err[SHOOT_ERR] = 1;
    else
        Global.err[SHOOT_ERR] = 0;
}

/**
 * @brief ��������⣬��FreeRTOS�е���
 *
 * @param ID
 */
void Error_detect_motor(can_id ID)
{
    uint16_t tmp1 = get_motor_data(ID).given_current;
    uint16_t tmp2 = get_motor_data(ID).ecd;
    if (Error_detect.motor.last_given_current[ID] == tmp1 &&
        Error_detect.motor.last_ecd[ID] == tmp2)
        Error_detect.motor.err_cnt[ID]++;
    else
    {
        Error_detect.motor.err_cnt[ID] = 0;
        Error_detect.motor.flag[ID] = 0;
    }

    Error_detect.motor.last_given_current[ID] = tmp1;
    Error_detect.motor.last_ecd[ID] = tmp2;

    if (Error_detect.motor.err_cnt[ID] > 3)
    {
        Error_detect.motor.err_cnt[ID] = 0;
        Error_detect.motor.flag[ID] = 1;
    }
}

void Error_detect_remote(void)
{
    Error_detect.remote.last_time++;
}

//void Error_detect_led(void)
//{
//	Error_detect_flush();
//	Error_detect_remote();
//	if (Global.err[REMOTE_ERR]==1)led_show(RED);
//	else if (Global.err[CHASSIS_ERR]==1)led_show(BLUE);
//	else if (Global.err[GIMBAL_ERR]==1)led_show(PURPLE);
//}
