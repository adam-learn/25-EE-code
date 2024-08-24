#include "CAN_receive&send.h"
#include "IMU_updata.h"
#include "DBUS_remote_control.h"
#include "PWM_control.h"
#include "LED_control.h"
#include "AHRS_MiddleWare.h"
#include "cap_ctl.h"
#include "Laser.h"

#include "RM_Cilent_UI.h"
#include "referee_handle_pack.h"
#include "referee_usart_task.h"
#include "usbd_cdc_if.h"
#include "USB_VirCom.h"

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


uint8_t is_input_for_rc = 1;
uint32_t Time_LEAN_delay = 0;
uint32_t Time_SPIN_delay = 0;
uint32_t Time_TANK_delay = 0;

uint32_t Time_delay_friction_wheel = 0;
uint32_t Time_delay_Switch = 0;
////������������ȣ��ײⲻ��ʹ�ã���֪��Ϊʲô
//uint16_t yaw_sen = 2800.0f;
//uint16_t pitch_sen= 1700.0f;

/******************************ң������������**************************************************/	
void remote_control_task()
{

  //��������  ����ģʽ
	if (switch_is_up(RC_L_SW) && switch_is_up(RC_R_SW))
		 Global.input.ctl=PC;
	
	//��������   ���̸���
	if (switch_is_mid(RC_L_SW) && switch_is_mid(RC_R_SW))
	{
		Global.mode = FLOW;	
		Global.input.ctl=RC;
	}
	
	//��������   ����
	if(switch_is_down(RC_L_SW) && switch_is_down(RC_R_SW))
	  Global.mode = LOCK;	
	
//	//��������   TANK
//	if (switch_is_mid(RC_L_SW) && switch_is_up(RC_R_SW))
//	{
//		Global.mode = TANK;	
//		Global.input.ctl=RC;
//	}	
	
	//��������   SPIN
	if (switch_is_mid(RC_L_SW) && switch_is_down(RC_R_SW))
	{
		Global.mode = SPIN;	
		Global.input.ctl=RC;
	}	

	
	//��������   AUTO_AIM
	if (switch_is_down(RC_L_SW) && switch_is_mid(RC_R_SW))
	{
		Global.input.vision_status = 1;
		Global.input.ctl=RC;		
	}
	else
		Global.input.vision_status = 0;			
	
	
/******************************RCң���������߼�**************************************************/	
	if (Global.input.ctl==RC) // rc input
	{
		// �ƶ�
		Global.input.r = RC_data.rc.ch[2] / 110.0f;
		Global.input.x = RC_data.rc.ch[0] / 110.0f;
		Global.input.y = RC_data.rc.ch[1] / 110.0f;

		// ��̨
		/*������ƣ�˼·�ܼ򵥣���Ϊ�Ӿ��ش�����ƫ����ҵ�Ŀ��ֵ���ǵ�ǰyaw+ƫ��=Ŀ��yaw��ʵʱ����
		Ϊʲô����+=�أ���Ϊ�����ʽ���ڻ�����ת�Ĺ����л����µ����ݴ��룬��ʱ��SET��>Ŀ��ֵ��
		���ұ���Ҫ����һ����ֵ�������������ޱƽ���������ȫ����
		*/
		if (Global.input.vision_status == 1)
		{
		}
		else
		{
			fromNUC.pitch = 0;
			fromNUC.yaw = 0;
			Global.input.yaw = RC_data.rc.ch[2] / 6000.0f;//��ͷ���󲿷�ҲҪ��С
			Global.input.pitch = -RC_data.rc.ch[3] /7000.0f;
		}
		
		// CH4 ����
		// Ħ�����߼�
		if (RC_data.rc.ch[4] == 0)
		{
			Global.input.shooter_status = 0;
		}
		if ((RC_data.rc.ch[4] > 300 && RC_data.rc.ch[4] < 660))
		{
			Global.input.shooter_status = 1;
		}
		
		
	// �����߼�
		if (RC_data.rc.ch[4] > 600 && RC_data.rc.ch[4] <= 660)
		{
			trigger_anti_kill_and_set_speed(3000.0f);//3000
		}
		else if (RC_data.rc.ch[4] > 6000 && RC_data.rc.ch[4] <= 7000)
	//���������������Ľ��ͣ������ϲ�0-7000���²�0-660,�������������߼�
		{
			trigger_anti_kill_and_set_speed(3000.0f);//3000
		}
		else
		{
			trigger_anti_kill_and_set_speed(0);
		}			
	}
/******************************PC�����߼�**************************************************/
	else if (Global.input.ctl==PC) // keyborad&mouuse_input_begin
	{
		//����״̬���
		Global.input.vision_status = RC_data.mouse.press_r;
		// ��̨
		if (Global.input.vision_status == 1)//�������
		{
			auto_ctrl();
		}
		else		//�����ֽӹ�yaw+pitch
		{
		//������򵥵ĵ����ָкã���ʺ���´δ��ɲ�¼��ȫ���������˵�ҿ�����
			vision_reset();
			Global.input.yaw = MOUSE_X_MOVE_SPEED/7000.0f;
			Global.input.pitch =MOUSE_Y_MOVE_SPEED/6000.0f;	
		}
		/*************����ģʽ�л�****************/
		//����С����ģʽ
		if (IF_KEY_PRESSED_Q)
		{
			if (Get_sys_time_ms() - Time_SPIN_delay > 350)//���̷���
			{
				if (Global.mode == SPIN)
					Global.mode = FLOW;
				else if (Global.mode != SPIN)
					Global.mode = SPIN;
				Time_SPIN_delay = Get_sys_time_ms();
			}
		}

		//����45��\��ģʽ
		 if (IF_KEY_PRESSED_CTRL)
		 {
			if (Get_sys_time_ms() - Time_LEAN_delay > 350)
			{
				if (Global.mode == LEAN)
					Global.mode = FLOW;
				else if (Global.mode != LEAN)
					Global.mode = LEAN;
				Time_LEAN_delay = Get_sys_time_ms();
			}
		 }

		//����̹��ģʽ
		if (IF_KEY_PRESSED_F)
		{
			if (Get_sys_time_ms() - Time_TANK_delay > 350)
			{
				if (Global.mode == TANK)
					Global.mode = FLOW;
				else if (Global.mode != TANK)
					Global.mode = TANK;
				Time_TANK_delay = Get_sys_time_ms();
			}
		}

		//�����������ݼ���
		if (IF_KEY_PRESSED_SHIFT)
		{
			Global.cap = FULL;
		}
		else
		{
			Global.cap = STOP;
		}

		/*************����ģʽ����****************/
		Global.input.shoot_fire = RC_data.mouse.press_l;
		// Ħ���ֿ���
		if (IF_KEY_PRESSED_R)		
		{
			if (Get_sys_time_ms() - Time_delay_friction_wheel > 350)
			{
				if (Global.input.shooter_status == 0) // �л�״̬
				{
					Global.input.shooter_status = 1;//�����־��λ
				}
				else
				{
					Global.input.shooter_status = 0;//��������ر�
				}

				Time_delay_friction_wheel = Get_sys_time_ms();
			}
		}		
		//��������
		if (IF_KEY_PRESSED_E)
		{
			if (Get_sys_time_ms() - Time_delay_Switch > 350)
			{
				if (Global.input.shoot_num != 1) // �л�״̬
				{
					Global.input.shoot_num = 1;
				}
				else if (Global.input.shoot_num == 1)
				{
					Global.input.shoot_num = 0;
				}
				Time_delay_Switch = Get_sys_time_ms();
			}
		}		
		//���ڣ�������
		if (Global.input.shoot_fire)	
		{
			if(Global.input.anti_stauts == 0)//������ģʽ�Ƿ���
				shoot_trigger_online();//������������
			else if(Global.input.anti_stauts == 1)
			{
				trigger_anti_kill_and_set_speed(8000.0f);//�����ݣ�ʹ���ٶȻ����ƣ���ʱ���Ķ�
			}
			else
				trigger_anti_kill_and_set_speed(0);
		}	
		else
		{
			trigger_anti_kill_and_set_speed(0);	
		}		
	

		//�ƶ�����
		if (IF_KEY_PRESSED_W)
		{
			if (Global.cap == FULL)
			{
				if (Global.input.y < 2.6f)
					Global.input.y += 0.2f;
				// Global.input.y = 10.0f;
			}
			else
			{
				if (Global.input.y < 1.6f)
					Global.input.y += 0.2f;
				// Global.input.y = 8.0f;
			}
		}
		else if (IF_KEY_PRESSED_S)
		{
			if (Global.cap == FULL)
			{
				if (Global.input.y > -2.6f)
					Global.input.y -= 0.2f;
				// Global.input.y = -10.0f;
			}
			else
			{
				if (Global.input.y > -1.6f)
					Global.input.y -= 0.2f;
				// Global.input.y = -8.0f;
			}
		}
		else
			Global.input.y = 0;

		if (IF_KEY_PRESSED_A)
		{
			if (Global.cap == FULL)
			{
				if (Global.input.x > -2.6f)
					Global.input.x -= 0.2f;
				// Global.input.x = -10.0f;
			}
			else
			{
				if (Global.input.x > -1.6f)
					Global.input.x -= 0.2f;
				// Global.input.x = -8.0f;
			}
		}
		else if (IF_KEY_PRESSED_D)
		{
			if (Global.cap == FULL)
			{
				if (Global.input.x < 2.6f)
					Global.input.x += 0.2f;
				// Global.input.x = 10.0f;
			}
			else
			{
				if (Global.input.x < 1.6f)
					Global.input.x += 0.2f;
				// Global.input.x = 8.0f;
			}
		}
		else
			Global.input.x = 0;



		if (IF_KEY_PRESSED_V) //��V����UI���ڰ�����ʼ����
		{
			press_refrsh();
		}

		if (IF_KEY_PRESSED_Z) //��Zȷ�������³�ʼ��
		{
			UI_task_init(); // UIͼ���ʼ��
		}
		//������
			
		if(IF_KEY_PRESSED_X)
			Global.input.anti_stauts = 1;
		else
			Global.input.anti_stauts = 0;		
		
	}
}
