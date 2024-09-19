#include "cover_headerfile_h.h"
#include "WFLY_ET16_remote_control.h"

void WFLY_remote_control_task(void)//����
{	
	
	if(SBUS_CH.CH14==352)
	{	

			//���ý���
			if(SBUS_CH.CH7==1695&&robot_status.power_management_chassis_output==1)			//			if(SBUS_CH.CH7_SC==1695)
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_SET);//���ÿ�
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);//��ŷ���
				Global.BOOM_mode = BOOM_ON;
				
			}
			else if(SBUS_CH.CH7==352||robot_status.power_management_chassis_output==0)			//			else if(SBUS_CH.CH7_SC==352)
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);//���ù�
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);//��ŷ���
				Global.BOOM_mode = BOOM_OFF;
			}
			else
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);//���ù�
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);//��ŷ���	
				Global.BOOM_mode = BOOM_OFF;
			}		
			
/////////////////////�������̣���ת///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		if(SBUS_CH.CH6==352&&SBUS_CH.CH5==352)
		{
		  Global.input.x_s = (SBUS_CH.CH2 - 1024)/100.0f;//200
      Global.input.y_s = (SBUS_CH.CH1 - 1024)/100.0f;//200
      Global.input.w_s = (SBUS_CH.CH3 - 1024)/500.0f;//500		



			//����
			if(SBUS_CH.CH4>1075)
			{
				ENGINE_Lifting_drive(1,8,2.0f);  //�½�
			}
			else if(SBUS_CH.CH4<975)
			{
				ENGINE_Lifting_drive(-1,8,2.0f); //����				
			}
			else if(SBUS_CH.CH4>975&&SBUS_CH.CH4<1075)
			{	
				
			}	
		
		}

		
///////////////////////������ǰ��,����////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		if(SBUS_CH.CH6==1024&&SBUS_CH.CH5==352)
		{
      Global.input.w_s = (SBUS_CH.CH3 - 1024)/650.0f;//500	
			Global.input.y_s = (float)0.0f;
      Global.input.x_s = (float)0.0f;
		
			//����
			if(SBUS_CH.CH1>1075)
			{
				ENGINE_Lifting_drive(-1,8,2.0f); //����
			}
			else if(SBUS_CH.CH1<975)
			{
				ENGINE_Lifting_drive(1,8,2.0f);  //�½�
			}
			else if(SBUS_CH.CH1>975&&SBUS_CH.CH1<1075)
			{	
				
			}	
			
			//ǰ��
			if(SBUS_CH.CH4>1075)
			{
				ENGINE_Impel_drive(-1,8,5.0f);	//ǰ��
			}
			else if(SBUS_CH.CH4<975)
			{
				ENGINE_Impel_drive(1,8,5.0f);		//����	
			}
			else if(SBUS_CH.CH4>975&&SBUS_CH.CH4<1075)
			{	
				
			}		
			//����
			if(SBUS_CH.CH2>1075)
			{		
        ENGINE_Traverse_drive(1,8,5.0f,-220,220);	 //����						
			}
			else if(SBUS_CH.CH2<975)
			{
        ENGINE_Traverse_drive(-1,8,5.0f,-220,220); //����				
			}
			else if(SBUS_CH.CH2>975&&SBUS_CH.CH2<1075)
			{	
				
			}
				
		}


		
///////////////////////����PITCH�ᣬ����ROLL�ᣬĩ��pitch�ᣬĩ��roll��//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(SBUS_CH.CH6==1695&&SBUS_CH.CH5==352)
		{
      Global.input.w_s = (float)0.0f;;
			Global.input.y_s = (float)0.0f;
      Global.input.x_s = (float)0.0f;


        //����Pitch��
			if(SBUS_CH.CH1>1075)
			{
				ENGINE_Pitch_Root_drive(1,8,1.0f,0,212);////���� 
			}
			else if(SBUS_CH.CH1<975)
			{
				ENGINE_Pitch_Root_drive(-1,8,1.0f,0,212);////�½�				
			}
			else if(SBUS_CH.CH1>975&&SBUS_CH.CH1<1075)
			{	
				
			}				
				//����Roll��
			if(SBUS_CH.CH2>1075)//1050
			{	
        ENGINE_Roll_drive(1,8,1.0f,-120,120);	//����					
			}
			else if(SBUS_CH.CH2<975)//1000
			{
				ENGINE_Roll_drive(-1,8,1.0f,-120,120); //����	
			}
			else if(SBUS_CH.CH2>975&&SBUS_CH.CH2<1075)
			{	
				
			}	


//				//ĩ��pitch��
			if(SBUS_CH.CH4>1075)
			{
				ENGINE_END_pitch_drive(-1,8,1.0f,-80,80);
			}
			else if(SBUS_CH.CH4<975)
			{
				ENGINE_END_pitch_drive(1,8,1.0f,-80,80);
			}
			else if(SBUS_CH.CH4>975&&SBUS_CH.CH4<1075)
			{}

				
//		  //ĩ��roll��
			if(SBUS_CH.CH3>1075)
	  	{
				ENGINE_END_roll_drive(-1,8,1.0f,-10000,10000);	//����					
			}
			else if(SBUS_CH.CH3<975)
			{
				ENGINE_END_roll_drive(1,8,1.0f,-10000,10000); //����
			}
			else if(SBUS_CH.CH3>975&&SBUS_CH.CH3<1075)
			{}
		}
	
	}
	else if(SBUS_CH.CH14==1695)
	{	
	
		//������������
		if (IF_KEY_PRESSED_SHIFT_Video_transmission)
		{
			Global.speed_mode = speed_accel;
		}
		else
		{
			Global.speed_mode = speed_normal;
		}		
			
		
		if (IF_KEY_PRESSED_W_Video_transmission)
		{
			if (Global.speed_mode == speed_accel)
			{
				if (Global.input.y_s < 3.0f)
					Global.input.y_s += 0.5f;
				else
					Global.input.y_s = 3.0f;
			}
			else 
			{
				if (Global.input.y_s < 1.5f)
					Global.input.y_s += 0.2f;
				else
					Global.input.y_s = 1.5f;
			}
		}
		else if (IF_KEY_PRESSED_S_Video_transmission)
		{
			if (Global.speed_mode == speed_accel)
			{
				if (Global.input.y_s > -3.0f)
					Global.input.y_s -= 0.5f;	
				else
					Global.input.y_s = -3.0f;
			}
			else
			{
				if (Global.input.y_s > -1.5f)
					Global.input.y_s -= 0.2f;
				else
					Global.input.y_s = -1.5f;
			}
		}
		else
			Global.input.y_s = 0;

		if (IF_KEY_PRESSED_A_Video_transmission)
		{
			if (Global.speed_mode == speed_accel)
			{
				if (Global.input.x_s > -3.0f)
					Global.input.x_s -= 0.5f;
				else
					Global.input.x_s = -3.0f;
			}
			else
			{
				if (Global.input.x_s > -1.5f)
					Global.input.x_s -= 0.2f;	
				else
					Global.input.x_s = -1.5f;
			}
		}
		else if (IF_KEY_PRESSED_D_Video_transmission)
		{
			if (Global.speed_mode == speed_accel)
			{
				if (Global.input.x_s < 3.0f)
					Global.input.x_s += 0.5f;	
				else 
					Global.input.x_s = 3.0f;					
			}
			else
			{
				if (Global.input.x_s < 1.5f)
					Global.input.x_s += 0.2f;
				else 
					Global.input.x_s = 1.5f;
			}
		}
		else
			Global.input.x_s = 0;
		
		
		
		
				if (remote_control.keyboard_value==8192)//C 8192
		{
				if (Global.input.w_s > -1.0f)
					Global.input.w_s -= 0.02f;	
				else
					Global.input.w_s = -1.0f;
		}
				else if (remote_control.keyboard_value==16384)//V 16384
		{
				if (Global.input.w_s < 1.0f)
					Global.input.w_s += 0.02f;
				else 
					Global.input.w_s = 1.0f;
		}
		else
			Global.input.w_s = 0;		
		
		
		if(remote_control.keyboard_value==4096)////X 4096
		{

		}
				
		if(remote_control.keyboard_value==2048)////Z 2048
		{
				
		}		
			

		if(remote_control.keyboard_value==2080)//ctrl + Z
		{
			Global.PID_mode = PID_Auto;			
			Automatic_return_to_zero();//һ����λ	
		}
		else if(remote_control.keyboard_value==4128)//ctrl + X
		{
			Global.PID_mode = PID_Auto;			
			Automatic_return_to_second_zero();//һ����ڶ����
		}
		else if(remote_control.keyboard_value==8224)//ctrl + C
		{
			Global.PID_mode = PID_Auto;	
			Automatic_grabbing_ground_mineral();//һ��������ץȡ��������̬			
		}
		else if(remote_control.keyboard_value==36)//ctrl + A
		{
			Global.PID_mode = PID_Auto;	
			Automatic_grabbing_gold_mineral();//һ��������ץȡ������̬			
		}
		else if(remote_control.keyboard_value==34)//ctrl + S
		{
			Global.PID_mode = PID_Auto;
			Automatic_grabbing_silver_mineral();//һ��������ץȡ�������̬			
		}
		else
		{
				if (remote_control.keyboard_value==64)//Q
				{
						ENGINE_Lifting_drive(1,8,2.0f); //�½�
				}
				else if (remote_control.keyboard_value==128)//E
				{
						ENGINE_Lifting_drive(-1,8,2.0f);  //����					
				}
				else
				{}
					
				if(SBUS_CH.CH13==352)
				{
					
						if (remote_control.keyboard_value==2112)//Z+Q
						{
							ENGINE_Traverse_drive(-1,8,5.0f,-220,220); 	 //����				
						}
						else if (remote_control.keyboard_value==2176)//Z+E
						{			
								ENGINE_Traverse_drive(1,8,5.0f,-220,220);	   //����				
						}
						else
						{}
					
						
						if (remote_control.keyboard_value==4160)//X+Q
						{
								ENGINE_Impel_drive(-1,8,5.0f);  //����
						}
						else if (remote_control.keyboard_value==4224)//X+E
						{
								ENGINE_Impel_drive(1,8,5.0f);		//ǰ��								
						}
						else
						{}		

						if (remote_control.keyboard_value==512)//F
						{     
								ENGINE_Pitch_Root_drive(1,8,1.0f,0,212);//-115.0f��97.0f;	-212��0 //���� 
						}
						else if (remote_control.keyboard_value==1024)//G
						{
								ENGINE_Pitch_Root_drive(-1,8,1.0f,0,212);//-115.0f��97.0f;	-212��0  //�½�
						}
						else
						{}

							
						if (remote_control.keyboard_value==8704)//C+F
						{
								ENGINE_Roll_drive(-1,8,1.0f,-120,120);	//����
						}
						else if (remote_control.keyboard_value==9216)//C+G
						{
								ENGINE_Roll_drive(1,8,1.0f,-120,120); //����	
						}
						else
						{}			
							
							
						if (remote_control.keyboard_value==16896)//V+F
						{
								ENGINE_END_pitch_drive(1,8,1.0f,-80,80);//����			
						}
						else if (remote_control.keyboard_value==17408)//V+G
						{
								ENGINE_END_pitch_drive(-1,8,1.0f,-80,80);//����			
						}
						else
						{}			
							

						if (remote_control.keyboard_value==33280)//B+F
						{
								ENGINE_END_roll_drive(1,8,1.0f,-8000,8000); //����			
						}
						else if (remote_control.keyboard_value==33792)//B+G
						{
								ENGINE_END_roll_drive(-1,8,1.0f,-5000,5000); //����			
						}
						else
						{}	
				}
				else if(SBUS_CH.CH13==1695) // custom control
				{
					static uint8_t last_key_val = 0;
					if (last_key_val != custom_robot_data.KEY_value)
					{
						if ( Global.BOOM_mode == BOOM_OFF)
							Global.BOOM_mode = BOOM_ON;
						else
							Global.BOOM_mode = BOOM_OFF;
					}
					last_key_val = custom_robot_data.KEY_value;
					
					if(custom_robot_data.Impel_distance>=5&&custom_robot_data.Impel_distance<=835)
					{
							ENGINE_LOVE_5.Impel_L__set.set_0 =  custom_robot_data.Impel_distance*2.0f;			
							ENGINE_LOVE_5.Impel_R__set.set_0 = -custom_robot_data.Impel_distance*2.0f;
					}
					else if(custom_robot_data.Impel_distance<=5)
					{
							ENGINE_LOVE_5.Impel_L__set.set_0 = 5;			
							ENGINE_LOVE_5.Impel_R__set.set_0 = -5;
					}
					else if(custom_robot_data.Impel_distance>=835)
					{
							ENGINE_LOVE_5.Impel_L__set.set_0 =  1670;			
							ENGINE_LOVE_5.Impel_R__set.set_0 = -1670;
					}
					else
					{}	


					if(custom_robot_data.Traverse_distance>=-300&&custom_robot_data.Traverse_distance<=300)
					{
							ENGINE_LOVE_5.Traverse_set.set_0 = -custom_robot_data.Traverse_distance/1.20f;
					}
					else if(custom_robot_data.Traverse_distance<=-300)
					{
							ENGINE_LOVE_5.Traverse_set.set_0 = 250;
					}
					else if(custom_robot_data.Traverse_distance>=300)
					{
							ENGINE_LOVE_5.Traverse_set.set_0 = -250;
					}
					else
					{}	


					if(custom_robot_data.Pitch_Root>=-90&&custom_robot_data.Pitch_Root<=45)
					{
							ENGINE_LOVE_5.Pitch_Root_set.set_0 = custom_robot_data.Pitch_Root + 167;
					}
					else if(custom_robot_data.Pitch_Root>45)
					{
							ENGINE_LOVE_5.Pitch_Root_set.set_0 = 212;
					}
					else if(custom_robot_data.Pitch_Root<-90)
					{
							ENGINE_LOVE_5.Pitch_Root_set.set_0 = 77;
					}
					else
					{}	


					if(custom_robot_data.Roll_Root>=-120&&custom_robot_data.Roll_Root<=120)
					{
							ENGINE_LOVE_5.Roll_set.set_0 = custom_robot_data.Roll_Root;
					}
					else if(custom_robot_data.Roll_Root<=-120)
					{
							ENGINE_LOVE_5.Roll_set.set_0 = -120;
					}
					else if(custom_robot_data.Roll_Root>=120)
					{
							ENGINE_LOVE_5.Roll_set.set_0 =120;
					}
					else
					{}	


					if(custom_robot_data.Pitch_end>=-80&&custom_robot_data.Pitch_end<=80)
					{ 
								ENGINE_LOVE_5.End_L_set.set_a_0= custom_robot_data.Pitch_end;
								ENGINE_LOVE_5.End_R_set.set_a_0= -custom_robot_data.Pitch_end;	
					}
					else if(custom_robot_data.Pitch_end<=-80)
					{
								ENGINE_LOVE_5.End_L_set.set_a_0= -80;
								ENGINE_LOVE_5.End_R_set.set_a_0=  80;	
					}
					else if(custom_robot_data.Pitch_end>=80)
					{
								ENGINE_LOVE_5.End_L_set.set_a_0=  80;
								ENGINE_LOVE_5.End_R_set.set_a_0= -80;	
					}
					else
					{}	


					if(custom_robot_data.Roll_end>=-10000&&custom_robot_data.Roll_end<=10000)
					{
								ENGINE_LOVE_5.End_L_set.set_b_0 = custom_robot_data.Roll_end;
								ENGINE_LOVE_5.End_R_set.set_b_0 = custom_robot_data.Roll_end;
					}
					else if(custom_robot_data.Roll_end<=-10000)
					{
								ENGINE_LOVE_5.End_L_set.set_b_0 = -10000;
								ENGINE_LOVE_5.End_R_set.set_b_0 = -10000;
					}
					else if(custom_robot_data.Roll_end>=10000)
					{
								ENGINE_LOVE_5.End_L_set.set_b_0 = 10000;
								ENGINE_LOVE_5.End_R_set.set_b_0 = 10000;
					}
					else
					{
					}	

				}
				else
				{}				
							
		}


	}	
		
			//���ý���
			if(SBUS_CH.CH7==1695&&robot_status.power_management_chassis_output==1)			//			if(SBUS_CH.CH7_SC==1695)
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_SET);//���ÿ�
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_RESET);//��ŷ���
				Global.BOOM_mode = BOOM_ON;
				
			}
			else if(SBUS_CH.CH7==352||robot_status.power_management_chassis_output==0)			//			else if(SBUS_CH.CH7_SC==352)
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);//���ù�
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);//��ŷ���
				Global.BOOM_mode = BOOM_OFF;
			}
			else
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,GPIO_PIN_RESET);//���ù�
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);//��ŷ���	
				Global.BOOM_mode = BOOM_OFF;
			}

			
			//���ý���
			if(SBUS_CH.CH8==1695&&robot_status.power_management_chassis_output==1)			//			if(SBUS_CH.CH8_SD==1695)
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_SET);//�����ÿ�
////				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);//���ŷ���
				
////				HAL_GPIO_WritePin(GPIOI,GPIO_PIN_6,GPIO_PIN_SET);//�����ÿ�
////				HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_RESET);//�ҵ�ŷ���	
				
				Global.BOOM_other_mode = BOOM_other_ON;		
			}
			else if(SBUS_CH.CH8==352||robot_status.power_management_chassis_output==0)			//			else if(SBUS_CH.CH8_SD==352)
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET);//�����ù�
////				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);//���ŷ���
				
////				HAL_GPIO_WritePin(GPIOI,GPIO_PIN_6,GPIO_PIN_RESET);//�����ù�
////				HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_SET);//�ҵ�ŷ���	

				Global.BOOM_other_mode = BOOM_other_OFF;				
			}
			else
			{
////				HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET);//�����ù�
////				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET);//���ŷ���	
				
////				HAL_GPIO_WritePin(GPIOI,GPIO_PIN_6,GPIO_PIN_RESET);//�����ù�
////				HAL_GPIO_WritePin(GPIOI,GPIO_PIN_7,GPIO_PIN_SET);//�ҵ�ŷ���

				Global.BOOM_other_mode = BOOM_other_OFF;						
			}			
		
		
			//ͼ������
			if(SBUS_CH.CH8==352)
			{	
				__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, 1700);//����
			}
			else if(SBUS_CH.CH8==1695)
			{
				__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3, 2300);//����	
			}
			else
			{
				__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_3,2000);
			}			
			
			//����ģʽ
	    if(SBUS_CH.CH16==1695)
				Global.mode = LOCK;
			else
				Global.mode = NORMAL;				

}



