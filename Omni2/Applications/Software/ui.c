#include <ui.h>
#include "referee_handle_pack.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "Global_status.h"
#include "string.h"
#include "shoot.h"
#include "NUC_communication.h"
#include "Stm32_time.h"


void ui_init(){
  ui_self_id=get_robot_id();
  osDelay(20);
  _ui_init_default_Ungroup_0();
  osDelay(20);		
  _ui_init_default_Ungroup_1();
	osDelay(20);		
  _ui_init_default_Ungroup_2();
	osDelay(20);		
  _ui_init_default_Ungroup_3();
	osDelay(20);		
  _ui_init_default_Ungroup_4();
  osDelay(20);		
  _ui_init_default_Ungroup_5();
	osDelay(20);		
}

void ui_updata(){
  _ui_update_default_Ungroup_4();
  osDelay(2);
  _ui_update_default_Ungroup_0();
  osDelay(2);
  _ui_update_default_Ungroup_1();
  osDelay(2);
  _ui_update_default_Ungroup_2();
  osDelay(2);
  _ui_update_default_Ungroup_3();
  osDelay(2);
  _ui_update_default_Ungroup_5();
  osDelay(2);
}

void ui_supercap(float votage){
  float cnt=votage*votage;
  float percent=(cnt-49.0f)/480.0f;
  if(percent>=1)
    percent=1;
  if(percent<=0)
    percent = 0;
  if(percent >=0.6)
    ui_default_Ungroup_EnergyLine->color = 2;//��ɫ
  if(percent<=0.6)
    ui_default_Ungroup_EnergyLine->color = 3;//��ɫ
  if(percent <=0.3)
    ui_default_Ungroup_EnergyLine->color = 4;//�Ϻ�ɫ
  ui_default_Ungroup_EnergyLine->end_x = ui_default_Ungroup_EnergyLine->start_x +795.0f*percent;
  
  if(Global.cap != FULL){
    ui_default_Ungroup_NewRect->color=6;
    ui_default_Ungroup_NewRect->width=1;
  }
  else{
    ui_default_Ungroup_NewRect->color=1;
    ui_default_Ungroup_NewRect->width=8;

  }
}


void char_change(){
  //����ģʽ  anti->������
	ui_default_Ungroup_anti->start_x = 1350;
	ui_default_Ungroup_anti->start_y = 660;
	strcpy(ui_default_Ungroup_anti->string, "ANTI");
  if(Global.input.anti_stauts!=1){
    ui_default_Ungroup_anti->color=7;
    ui_default_Ungroup_anti->font_size=30;
  }else{
    ui_default_Ungroup_anti->color=2;
    ui_default_Ungroup_anti->font_size=30;
  }
  
  //����״̬ ->���ո� ����
	strcpy(ui_default_Ungroup_Cover->string, "NORMAL");
  if(Global.input.lid==1)
	{
	  strcpy(ui_default_Ungroup_Cover->string, "COVER");
    ui_default_Ungroup_Cover->color=2;
    ui_default_Ungroup_Cover->font_size=30;
		
  }
	else
	{
	  strcpy(ui_default_Ungroup_Cover->string, "NORMAL");
		ui_default_Ungroup_Cover->color=7;
    ui_default_Ungroup_Cover->font_size=30;
	}

  //��������
  if(Global.input.shoot_num == 1){
	  strcpy(ui_default_Ungroup_Bullet->string, "HIGH ");
    ui_default_Ungroup_Bullet->color=2;
    ui_default_Ungroup_Bullet->font_size=30;
  }else{
	  strcpy(ui_default_Ungroup_Bullet->string, "LOW  ");
    ui_default_Ungroup_Bullet->color=7;
    ui_default_Ungroup_Bullet->font_size=30;
  }
  
  //Ħ����
   if(shoot.shoot_speed[1] < 6500){
    ui_default_Ungroup_DropPoint->color=7;
  }else{
    ui_default_Ungroup_DropPoint->color=2;
  }

}

void ui_chassis(float angle){
    float angle_start,angle_end;
    while(angle>360)
      angle-=360;
    angle_start=angle-20.0f;
    angle_end=angle+20.0f;
    if(angle_start<=0.0f)
      angle_start+=360.0f;
    if(angle_end<=0.0f)
      angle_end+=360.0f;

    if(angle_end>=360.0f)
      angle_end-=360.0f;
    if(angle_start>=360.0f)
      angle_start-=360.0f;
    ui_default_Ungroup_Chassis->start_angle=angle_start;
    ui_default_Ungroup_Chassis->end_angle=angle_end;
    
    

}


void ui_auto(uint8_t status){//�������ui
   switch (status)//����Ȧ
	 {
		 case 0:		 
      ui_default_Ungroup_AutoRound->color=4;//�Ϻ�ɫ
			break;
		 case 1:
      ui_default_Ungroup_AutoRound->color=3;//��ɫ
			break;
		 case 2:
      ui_default_Ungroup_AutoRound->color=2;//��ɫ
			break;
			default:
      ui_default_Ungroup_AutoRound->color=4;//�Ϻ�ɫ
			break;			
	 }	
	 
	 //�����
	 ui_default_Ungroup_AutoRect->end_y = 697;
   if(Global.input.vision_status!=1)
     ui_default_Ungroup_AutoRect->color=8;
   else
     ui_default_Ungroup_AutoRect->color=2;
   if(Global.input.vision_online==0){//�������
     ui_default_Ungroup_AutoRound->color=4;//�Ϻ�ɫ
     ui_default_Ungroup_AutoRect->color=7;
   }

	if((int32_t)fromNUC.target_id != 255)
	ui_default_Ungroup_AutoRobot->number=(int32_t)fromNUC.target_id;
	else
	ui_default_Ungroup_AutoRobot->number=0;
}

void ui_chassisline(){
  if(Global.input.fly_status==1){
    ui_default_Ungroup_MoveLineleft->end_y = 408;
    ui_default_Ungroup_MoveLineright->end_y = 408;
  }else{
    ui_default_Ungroup_MoveLineleft->end_y = 1;
    ui_default_Ungroup_MoveLineright->end_y = 1;
  }
}

void ui_WarningLight(){
	static float warningtime=0;
	if((Get_sys_time_ms()-warningtime)>1000){
	if(ui_default_Ungroup_WarningLight->color==0)
		ui_default_Ungroup_WarningLight->color=1;
	else
		ui_default_Ungroup_WarningLight->color=0;
	  warningtime=Get_sys_time_ms();
  }
}


void ui_Spin(){
	static float spinstoptime=0;
	if(Global.input.x!=0||Global.input.y!=0||Global.mode==SPIN)
		spinstoptime=Get_sys_time_ms();
	if(Global.mode == SPIN)
	{
      strcpy(ui_default_Ungroup_Spin->string, "          ");
  }
	else
	{
	  if(Global.input.y==0&&Global.input.x==0&&(Get_sys_time_ms()-spinstoptime>2000))
       strcpy(ui_default_Ungroup_Spin->string, "SPIN!");
		else
      strcpy(ui_default_Ungroup_Spin->string, "          ");
	}
}
