/**
 * @file global_status.h
 * @author sethome
 * @brief ȫ��״̬��
 * @version 0.1
 * @date 2022-03-25
 *
 * @copyright sethome Copyright (c) 2022
 *
 */
#ifndef __GLOBAL_STATUS_H__
#define __GLOBAL_STATUS_H__

#include "cover_headerfile_h.h"

// ������
enum err_e
{
    GIMBAL_ERR = 0,
    CHASSIS_ERR,
    SHOOT_ERR,
    CAP_ERR,
    REMOTE_ERR,
    PC_ERR,
};
enum ctl_e
{
	RC=0,
	PC,
};
// �ʺ�ʮ������״̬�����
struct GlobalStatus_t
{
    uint8_t err[6];
	
    enum mode_e
    {
				NORMAL = 0,
        LOCK, 
        FLOW,
        TANK,
        SPIN,
				LEAN,			
    } mode;

    enum PID_mode_e
    {
        PID_NORMAL = 0,
        PID_Auto,			
    } PID_mode;			
		

    enum speed_mode_e
    {
        speed_normal = 0,
        speed_accel,			
    } speed_mode;	

    enum BOOM_mode_e
    {
        BOOM_OFF = 0,
        BOOM_ON,			
    } BOOM_mode;

    enum BOOM_other_mode_e
    {
        BOOM_other_OFF = 0,
        BOOM_other_ON,			
    } BOOM_other_mode;	
		
    enum cap_e
    {
        STOP = 0, // ��ʱ����Ӧ�ڳ��
        FULL,     // ȫ����Ӧ
    } cap;		
		
    struct
    {
			/* data *///30
			float x_s, y_s, w_s; // �����ƶ�  //12
			float pitch, yaw;                 //8
			uint8_t vision_status;            //1
			uint8_t anti_stauts;              //1
			
			uint8_t shooter_status;           //1
			uint8_t shoot_fire;               //1
			uint8_t shoot_num;			          //1
			uint8_t trigger_begin;            //1
			uint8_t	trigger_kill;             //1
			uint8_t	trigger_kill_cnt;	        //1
			uint8_t lid;		                  //1
      enum ctl_e ctl;	                  //1
    } input;

};
extern struct GlobalStatus_t Global;

void Global_set_err(enum err_e err, uint8_t status);

#endif




// end of file
