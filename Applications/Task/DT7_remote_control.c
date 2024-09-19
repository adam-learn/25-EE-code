#include "cover_headerfile_h.h"
#include "DT7_remote_control.h"


uint8_t is_input_for_rc = 1;

uint32_t Time_delay_LEAN = 0;
uint32_t Time_delay_SPIN = 0;
uint32_t Time_delay_TANK = 0;

uint32_t Time_delay_friction_wheel = 0;
uint32_t Time_delay_switch = 0;
uint32_t Time_delay_lid = 0;
uint32_t Time_delay_shoot= 0;
float pitch_test_link = 900.0f;
float yaw_test_link = 19.0f; //

void DT7_remote_control_task(void)  //NEW_ARMY!�²���
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
	
	//��������   TANK
	if (switch_is_mid(RC_L_SW) && switch_is_up(RC_R_SW))
	{
		Global.mode = TANK;	
		Global.input.ctl=RC;
	}	
	
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
	
	if (Global.input.ctl==RC) // rc input
	{
		// �ƶ�
		Global.input.x_s= RC_data.rc.ch[0] / 110.0f;
		Global.input.y_s = RC_data.rc.ch[1] / 110.0f;

		if (abs(RC_data.rc.ch[2]) > 50)
			Global.input.w_s = RC_data.rc.ch[2] / 110.0f;
		else
			Global.input.w_s = 0;
		
		//��̨
		if (Global.input.vision_status == 1) //�������
		{
			if (fabs(fromNUC.yaw) > 0.0f)
				Global.input.yaw = fromNUC.yaw / 19.0f;//yaw_test_link;
			else
				Global.input.yaw = 0.0f;

			if (fabs(fromNUC.pitch) > 0.0f)
				Global.input.pitch = fromNUC.pitch / 500.0f; // pitch_test_link;
			else
				Global.input.pitch = 0.0f;
		}
		else
		{
			fromNUC.pitch = 0;
			fromNUC.yaw = 0;

			if (abs(RC_data.rc.ch[2]) > 50)
				Global.input.yaw = RC_data.rc.ch[2] / 250.0f;
			else
				Global.input.yaw = 0;

			Global.input.pitch = -RC_data.rc.ch[3] / 15000.0f;
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
			trigger_anti_kill_and_set_speed(-3000.0f);
		}
		else
		{
			trigger_anti_kill_and_set_speed(0);
		}		
		
		
	}
	else if (Global.input.ctl==PC)
	{
		//��λ
		Global.input.vision_status = RC_data.mouse.press_r;
		Global.input.shoot_fire = RC_data.mouse.press_l;

		//��̨
		if (Global.input.vision_status == 1) //�������
		{
			if (fabs(fromNUC.yaw) > 0.0f)
				Global.input.yaw = fromNUC.yaw / yaw_test_link; // 130   15����ͦ�ã� 13�����ݸ��ã�  12.85Ҳ���ˣ�ͦ�ã�
			else
				Global.input.yaw = 0.0f;

			if (fabs(fromNUC.pitch) > 0.0f)
				Global.input.pitch = fromNUC.pitch / pitch_test_link; // 1000   950
			else
				Global.input.pitch = 0.0f;
		}
		else
		{
			fromNUC.pitch = 0;
			fromNUC.yaw = 0;
			Global.input.yaw = MOUSE_X_MOVE_SPEED / yaw_test_link;
			Global.input.pitch = MOUSE_Y_MOVE_SPEED / pitch_test_link;
			
			//����ƶ��ٶ��޷�
			if(Global.input.yaw >= 1.3f)
				Global.input.yaw = 1.3f;
			else if(Global.input.yaw <= -1.3f)
				Global.input.yaw = -1.3f;
			
			if(Global.input.pitch >= 0.027f)
				Global.input.pitch = 0.027f;
			else if(Global.input.pitch <= -0.027f)
				Global.input.pitch = -0.027f;
		}

		//�ƶ�����
		if (IF_KEY_PRESSED_W)
		{
			if (Global.cap == FULL)
			{
				if (Global.input.y_s < 3.0f)
					Global.input.y_s += 0.6f;
				// Global.input.y = 10.0f;
			}
			else
			{
				if (Global.input.y_s < 2.5f)
					Global.input.y_s += 0.4f;
				// Global.input.y = 8.0f;
			}
		}
		else if (IF_KEY_PRESSED_S)
		{
			if (Global.cap == FULL)
			{
				if (Global.input.y_s > -3.0f)
					Global.input.y_s -= 0.6f;
				// Global.input.y = -10.0f;
			}
			else
			{
				if (Global.input.y_s > -2.5f)
					Global.input.y_s -= 0.4f;
				// Global.input.y = -8.0f;
			}
		}
		else
			Global.input.y_s = 0;

		if (IF_KEY_PRESSED_A)
		{
			if (Global.cap == FULL)
			{
				if (Global.input.x_s > -3.0f)
					Global.input.x_s -= 0.2f;
				// Global.input.x = -10.0f;
			}
			else
			{
				if (Global.input.x_s > -2.5f)
					Global.input.x_s -= 0.4f;
				// Global.input.x = -8.0f;
			}
		}
		else if (IF_KEY_PRESSED_D)
		{
			if (Global.cap == FULL)
			{
				if (Global.input.x_s < 3.0f)
					Global.input.x_s += 0.6f;
				// Global.input.x = 10.0f;
			}
			else
			{
				if (Global.input.x_s < 2.5f)
					Global.input.x_s += 0.4f;
				// Global.input.x = 8.0f;
			}
		}
		else
			Global.input.x_s = 0;


		//������������
		if (IF_KEY_PRESSED_SHIFT)
		{
			Global.cap = FULL;
		}
		else
		{
			Global.cap = STOP;
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
		}

		if (Global.input.lid == 1)
		{
		}
		else
		{
		}
		

		// Ħ���ֿ���
		if (IF_KEY_PRESSED_R)
		{
			if (Get_sys_time_ms() - Time_delay_friction_wheel > 350)
			{
				if (Global.input.shooter_status == 0) // �л�״̬
				{
					Global.input.shooter_status = 1;
				}
				else
				{
					Global.input.shooter_status = 0;
				}

				Time_delay_friction_wheel = Get_sys_time_ms();
			}
		}

		if (IF_KEY_PRESSED_E)
		{
			if (Get_sys_time_ms() - Time_delay_switch > 350)
			{
				if (Global.input.shoot_num != 1) // �л�״̬
				{
					Global.input.shoot_num = 1;
				}
				else if (Global.input.shoot_num == 1)
				{
					Global.input.shoot_num = 0;
				}
				Time_delay_switch = Get_sys_time_ms();
			}
		}
		//����   				else if(Global.input.anti_stauts == 1 && fromNUC.shoot == 2)
			if (Global.input.shoot_fire)
			{
				if(Global.input.anti_stauts == 0)
					shoot_trigger_online();
				else if(Global.input.anti_stauts == 1)
				{
					trigger_anti_kill_and_set_speed(-8000.0f);
				}
				else
					trigger_anti_kill_and_set_speed(0);
			}	
			else
			{
				trigger_anti_kill_and_set_speed(0);	
			}
		
	}

		//����45��\��ģʽ
		if (IF_KEY_PRESSED_CTRL)
		{
			if (Get_sys_time_ms() - Time_delay_LEAN > 350)
			{
				if (Global.mode == LEAN)
					Global.mode = FLOW;
				else if (Global.mode != LEAN)
					Global.mode = LEAN;
				Time_delay_LEAN = Get_sys_time_ms();
			}
		}

		//����С����ģʽ
		if (IF_KEY_PRESSED_Q)
		{
			if (Get_sys_time_ms() - Time_delay_SPIN > 350)
			{
				if (Global.mode == SPIN)
					Global.mode = FLOW;
				else if (Global.mode != SPIN)
					Global.mode = SPIN;
				Time_delay_SPIN = Get_sys_time_ms();
			}
		}

		//����̹��ģʽ
		if (IF_KEY_PRESSED_F)
		{
			if (Get_sys_time_ms() - Time_delay_TANK > 350)
			{
				if (Global.mode == TANK)
					Global.mode = FLOW;
				else if (Global.mode != TANK)
					Global.mode = TANK;
				Time_delay_TANK = Get_sys_time_ms();
			}
		}
		
		if(IF_KEY_PRESSED_X)
			Global.input.anti_stauts = 1;
		else
			Global.input.anti_stauts = 0;		
		
}

