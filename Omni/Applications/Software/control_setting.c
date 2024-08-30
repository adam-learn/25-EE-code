#include "CAN_receive&send.h"
#include "IMU_updata.h"
#include "DBUS_remote_control.h"
#include "PWM_control.h"
#include "LED_control.h"
#include "AHRS_MiddleWare.h"
#include "cap_ctl.h"
#include "Laser.h"
#include "can.h"
#include "freertos.h"
#include "cmsis_os2.h"

#include "referee_handle_pack.h"
#include "referee_usart_task.h"
#include "usbd_cdc_if.h"
#include "USB_VirCom.h"

#include "ui.h"
#include "Global_status.h"
#include "Error_detect.h"
#include "chassis_move.h"
#include "gimbal.h"
#include "shoot.h"
#include "math.h"
#include "RampFunc.h"
#include "NUC_communication.h"
#include "control_setting.h"
#include "Stm32_time.h"
#include "usb_device.h"

extern float DBUStime1;

uint8_t is_input_for_rc = 1;
uint32_t Time_LEAN_delay = 0;
uint32_t Time_SPIN_delay = 0;
uint32_t Time_TANK_delay = 0;
uint32_t Time_delay_lid = 0;
uint32_t Time_ANTI_delay = 0;
uint32_t Time_delay_friction_wheel = 0;
uint32_t Time_delay_resetcan = 0;
uint32_t Time_delay_Switch = 0;
uint8_t coverop = 0;

float KS;

/******************************ң������������**************************************************/
void Remote_Control()
{
	if ((Get_sys_time_ms() - DBUStime1) > 1000.0f)
	{
		image_to_RC(&RC_data); // �л���ͼ����·
	}
	// ��������  ����ģʽ
	if (switch_is_up(RC_L_SW) && switch_is_up(RC_R_SW))
	{
		Global.input.ctl = PC;
	}
	else
		Global.input.ctl = RC;
	// ��������   ���̸���
	if (switch_is_mid(RC_L_SW) && switch_is_mid(RC_R_SW))
	{
		Global.mode = FLOW;
	}

	// ��������   ����
	if (switch_is_down(RC_L_SW) && switch_is_down(RC_R_SW))
	{
		Global.mode = LOCK;
	}
	// ��������   TUENSPIN
	if (switch_is_up(RC_L_SW) && switch_is_down(RC_R_SW))
	{
		Global.mode = TUSP;
	}

	// ��������   SPIN
	if (switch_is_mid(RC_L_SW) && switch_is_down(RC_R_SW))
	{
		Global.mode = SPIN;
	}

	// ��������   AUTO_AIM
	if (switch_is_down(RC_L_SW) && switch_is_mid(RC_R_SW))
	{
		Global.input.vision_status = 1;
	}
	else
		Global.input.vision_status = 0;
}
/******************************RCң���������߼�**************************************************/
void Remote_Control_RC()
{
	// �ƶ�
	Global.input.r = RC_data.rc.ch[2] / 110.0f;
	Global.input.x = RC_data.rc.ch[0] / 110.0f;
	Global.input.y = RC_data.rc.ch[1] / 80.0f;
	// ����
	if (Global.input.vision_status == 1)
	{
		Global.input.yaw = 0;
		Global.input.pitch = 0;
		auto_ctrl();
	}
	else
	{
		fromNUC.pitch = 0;
		fromNUC.yaw = 0;
		Global.input.yaw = RC_data.rc.ch[2] / 6000.0f; // ��ͷ���󲿷�ҲҪ��С
		Global.input.pitch = -RC_data.rc.ch[3] / 7000.0f;
	}
	// CH4 ����
	// Ħ�����߼�
	if (RC_data.rc.ch[4] == 0)
	{
		Global.input.shooter_status = 0;
	}
	if ((RC_data.rc.ch[4] > 300 && RC_data.rc.ch[4] < 660))
	{
		Global.input.shoot_num = 1;		 // ����
		Global.input.shooter_status = 1; // Ħ��������
	}
	// �����߼�
	if (RC_data.rc.ch[4] > 600 && RC_data.rc.ch[4] <= 660)
	{
		Global.input.shoot_RC = 80;
	}
	else if (RC_data.rc.ch[4] > 6000 && RC_data.rc.ch[4] <= 7000)
	// ���������������Ľ��ͣ������ϲ�0-7000���²�0-660,�������������߼�
	{
		Global.input.shoot_RC = 100;
	}
	else
	{
		Global.input.shoot_RC = 0; // û�в���λ�ò����ӵ�
	}
	if (Global.mode == LOCK) // �л�����ģʽ���л����ָǵĿ���
		cover_open();
	else
		cover_close();
}

/******************************PC�����߼�**************************************************/
void Remote_Control_PC()
{
	// ����״̬���
	Global.input.vision_status = RC_data.mouse.press_r;
	// ��̨
	if (Global.input.vision_status == 1 && Global.input.anti_stauts == 0) // �������
	{
		Global.input.yaw = 0;
		Global.input.pitch = 0;
		auto_ctrl();
	}
	else if (Global.input.vision_status == 1 && Global.input.anti_stauts == 1) // ������ �����ֽӹ�yaw
	{
		Global.input.pitch = 0;
		Global.input.yaw = MOUSE_X_MOVE_SPEED / 4500.0f;
		auto_ctrl();
	}
	else // �ֶ�ģʽ �����ֽӹ�yaw+pitch
	{
		vision_reset();
		Global.input.yaw = MOUSE_X_MOVE_SPEED / 4500.0f;
		if (Global.input.fly_status != 1) // ����ģʽ�в���¼pitch������
			Global.input.pitch = MOUSE_Y_MOVE_SPEED / 3000.0f;
	}
	/*************����ģʽ�л�****************/
	// ����С����ģʽ
	if (IF_KEY_PRESSED_Q)
	{
		if (Get_sys_time_ms() - Time_SPIN_delay > 350) // ���̷���
		{
			if (Global.mode == SPIN)
				Global.mode = FLOW;
			else if (Global.mode != SPIN)
			{
				Global.mode = SPIN;
				Global.input.fly_status = 0;
			}
			Time_SPIN_delay = Get_sys_time_ms();
		}
	}

	// �����������ݼ���
	if (IF_KEY_PRESSED_SHIFT)
		Global.cap = FULL;
	else
		Global.cap = STOP;

	/*************����ģʽ����****************/
	Global.input.shoot_fire = RC_data.mouse.press_l;
	// Ħ���ֿ���
	if (IF_KEY_PRESSED_R)
	{
		if (Get_sys_time_ms() - Time_delay_friction_wheel > 350)
		{
			if (Global.input.shooter_status == 0) // �л�״̬
			{
				Global.input.shooter_status = 1; // �����־��λ
			}
			else
			{
				Global.input.shooter_status = 0; // ��������ر�
			}

			Time_delay_friction_wheel = Get_sys_time_ms();
		}
	}
	// ��������
	if (IF_KEY_PRESSED_E)
	{
		if (Get_sys_time_ms() - Time_delay_Switch > 350)
		{
			if (Global.input.shoot_num != 1) // �л�״̬
			{
				Global.input.shoot_num = 1; // ����ģʽ
				shoot.trigger_status = SPEEDS;
			}
			else if (Global.input.shoot_num == 1)
			{
				Global.input.shoot_num = 0; // ����ģʽ
				shoot.trigger_status = LOCATIONS;
			}
			Time_delay_Switch = Get_sys_time_ms();
		}
	}

	/*************�����н�****************/
	if (REFEREE_DATA.Chassis_Power_Limit <= 60)
	{
		KS = 1.0f;
	}
	else if (REFEREE_DATA.Chassis_Power_Limit > 60 && REFEREE_DATA.Chassis_Power_Limit <= 80)
	{
		KS = 1.1f;
	}
	else if (REFEREE_DATA.Chassis_Power_Limit > 80 && REFEREE_DATA.Chassis_Power_Limit <= 120)
	{
		KS = 1.2f;
	}

	if (IF_KEY_PRESSED_W)
	{
		if (Global.input.fly_status == 1)
		{

			if (Global.input.y < 1.0f)
				Global.input.y += 0.0025f;
			else if (Global.input.y >= 1.0f && Global.input.y < 3.0f)
				Global.input.y += 0.004f;
			else if (Global.input.y >= 3.0f && Global.input.y < 5.0f)
				Global.input.y += 0.005f;
			else if (Global.input.y >= 5.0f && Global.input.y < 9.0f)
				Global.input.y += 0.008f;
		}
		else
		{

			if (Global.cap == FULL)
			{
				Global.input.y += 0.04;
				if (Global.input.y >= 3.0)
					Global.input.y = 3.0;
			}
			else
			{

				if (Global.input.y < 0.5)
					Global.input.y += 0.004f;
				if (Global.input.y > 0.5 && Global.input.y < 0.8)
					Global.input.y += 0.025f;
				if (Global.input.y > 0.8 && Global.input.y < 1.6 * KS)
					Global.input.y += 0.04f;
				if (Global.input.y > 1.6 * KS)
					Global.input.y = 1.6 * KS;

				if (Global.input.lid == 1)
					Global.input.y = 0.7;
			}
		}
	}
	else if (IF_KEY_PRESSED_S)
	{
		if (Global.cap == FULL)
		{
			if (Global.input.y > -1.0f)
				Global.input.y -= 0.0025f;
			else if (Global.input.y <= -1.0f && Global.input.y > -3.0f)
				Global.input.y -= 0.004f;
			else if (Global.input.y <= -3.0f && Global.input.y > -5.0f)
				Global.input.y -= 0.005f;
			else if (Global.input.y <= -5.0f && Global.input.y > -8.0f)
				Global.input.y -= 0.007f;
		}
		else
		{
			if (Global.input.y > -1.6f * KS)
				Global.input.y -= 0.02f;
			if (Global.input.lid == 1)
				Global.input.y = -0.7;
		}
	}
	else
		Global.input.y = 0;

	if (IF_KEY_PRESSED_A)
	{
		if (Global.cap == FULL)
		{
			if (Global.input.x > -2.0f)
				Global.input.x -= 0.08f;
		}
		else
		{
			if (Global.input.x > -1.8f)
				Global.input.x -= 0.02f;
			if (Global.input.lid == 1)
				Global.input.x = -0.7;
		}
	}
	else if (IF_KEY_PRESSED_D)
	{
		if (Global.cap == FULL)
		{
			if (Global.input.x < 2.0f)
				Global.input.x += 0.08f;
		}
		else
		{

			if (Global.input.x < 1.8f)
				Global.input.x += 0.02f;
			if (Global.input.lid == 1)
				Global.input.x = 0.7;
		}
	}
	else
		Global.input.x = 0;

	if (IF_KEY_PRESSED_V) // ����
	{
	}

	if (IF_KEY_PRESSED_Z) // UI��ʼ��
	{
		Global.input.ui_init = 1;
	}
	// ������

	if (IF_KEY_PRESSED_X)
	{
		if (Get_sys_time_ms() - Time_ANTI_delay > 350)
		{
			if (Global.input.anti_stauts == 0)
				Global.input.anti_stauts = 1;
			else
				Global.input.anti_stauts = 0;
			Time_ANTI_delay = Get_sys_time_ms();
		}
	}

	// �����ո�
	if (IF_KEY_PRESSED_C)
	{

		if (Get_sys_time_ms() - Time_delay_lid > 350)
		{
			if (Global.input.lid != 1)
				Global.input.lid = 1;
			else
				Global.input.lid = 0;
			Time_delay_lid = Get_sys_time_ms();
		}
		if (Global.input.lid == 1)
		{
			cover_open();
		}
		else
		{
			cover_close();
		}
	}

	if (IF_KEY_PRESSED_G)
	{
		if (Get_sys_time_ms() - Time_delay_friction_wheel > 350)
		{
			if (Global.input.fly_status == 0) // �л�״̬
			{
				Global.input.fly_status = 1; // �����־��λ
				gimbal.pitch_status = LOCATION;
			}
			else if (IF_KEY_PRESSED_Q)
			{
				Global.input.fly_status = 0; // ��������ر�
				gimbal.pitch_status = ABSOLUTE;
			}
			else
			{
				Global.input.fly_status = 0; // ��������ر�
				gimbal.pitch_status = ABSOLUTE;
			}

			Time_delay_friction_wheel = Get_sys_time_ms();
		}
	}
}

void remote_control_task()
{
	Remote_Control();
	if (Global.input.ctl == PC)
		Remote_Control_PC();
	else if (Global.input.ctl == RC)
		Remote_Control_RC();
	else
	{
	}
}