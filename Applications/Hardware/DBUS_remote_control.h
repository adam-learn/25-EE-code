/**
  ****************************(C) COPYRIGHT 2016 DJI****************************
  * @file       remote_control.c/h
  * @brief      ң��������ң������ͨ������SBUS��Э�鴫�䣬����DMA���䷽ʽ��ԼCPU
  *             ��Դ�����ô��ڿ����ж�������������ͬʱ�ṩһЩ��������DMA������
  *             �ķ�ʽ��֤�Ȳ�ε��ȶ��ԡ�
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. ���
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2016 DJI****************************
  */
#ifndef __REMOTE_CONTROL_H__
#define __REMOTE_CONTROL_H__

#include "cover_headerfile_h.h"

#define SBUS_RX_BUF_NUM 36u//50U//36u

#define RC_FRAME_LENGTH 18u//25U//18u



#define RC_R_SW 0
#define RC_L_SW 1

#define RC_CH_VALUE_MIN         ((uint16_t)364)
#define RC_CH_VALUE_OFFSET      ((uint16_t)1024)
#define RC_CH_VALUE_MAX         ((uint16_t)1684)

//��ť״̬�궨��
#define UP     1
#define MIDDLE 3
#define DOWN   2

/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP                ((uint16_t)1)
#define RC_SW_MID               ((uint16_t)3)
#define RC_SW_DOWN              ((uint16_t)2)
#define switch_is_down(a)       (RC_data.rc.s[a] == RC_SW_DOWN)
#define switch_is_mid(a)        (RC_data.rc.s[a] == RC_SW_MID)
#define switch_is_up(a)         (RC_data.rc.s[a] == RC_SW_UP)
/* ----------------------- PC Key Definition-------------------------------- */
#define KEY_PRESSED_OFFSET_W            ((uint16_t)1 << 0)
#define KEY_PRESSED_OFFSET_S            ((uint16_t)1 << 1)
#define KEY_PRESSED_OFFSET_A            ((uint16_t)1 << 2)
#define KEY_PRESSED_OFFSET_D            ((uint16_t)1 << 3)
#define KEY_PRESSED_OFFSET_SHIFT        ((uint16_t)1 << 4)
#define KEY_PRESSED_OFFSET_CTRL         ((uint16_t)1 << 5)
#define KEY_PRESSED_OFFSET_Q            ((uint16_t)1 << 6)
#define KEY_PRESSED_OFFSET_E            ((uint16_t)1 << 7)
#define KEY_PRESSED_OFFSET_R            ((uint16_t)1 << 8)
#define KEY_PRESSED_OFFSET_F            ((uint16_t)1 << 9)
#define KEY_PRESSED_OFFSET_G            ((uint16_t)1 << 10)
#define KEY_PRESSED_OFFSET_Z            ((uint16_t)1 << 11)
#define KEY_PRESSED_OFFSET_X            ((uint16_t)1 << 12)
#define KEY_PRESSED_OFFSET_C            ((uint16_t)1 << 13)
#define KEY_PRESSED_OFFSET_V            ((uint16_t)1 << 14)
#define KEY_PRESSED_OFFSET_B            ((uint16_t)1 << 15)

#define    IF_KEY_PRESSED         (  RC_data.key.v  )
#define    IF_KEY_PRESSED_W       ( (RC_data.key.v & KEY_PRESSED_OFFSET_W)    != 0 )
#define    IF_KEY_PRESSED_S       ( (RC_data.key.v & KEY_PRESSED_OFFSET_S)    != 0 )
#define    IF_KEY_PRESSED_A       ( (RC_data.key.v & KEY_PRESSED_OFFSET_A)    != 0 )
#define    IF_KEY_PRESSED_D       ( (RC_data.key.v & KEY_PRESSED_OFFSET_D)    != 0 )
#define    IF_KEY_PRESSED_Q       ( (RC_data.key.v & KEY_PRESSED_OFFSET_Q)    != 0 )
#define    IF_KEY_PRESSED_E       ( (RC_data.key.v & KEY_PRESSED_OFFSET_E)    != 0 )
#define    IF_KEY_PRESSED_G       ( (RC_data.key.v & KEY_PRESSED_OFFSET_G)    != 0 )
#define    IF_KEY_PRESSED_X       ( (RC_data.key.v & KEY_PRESSED_OFFSET_X)    != 0 )
#define    IF_KEY_PRESSED_Z       ( (RC_data.key.v & KEY_PRESSED_OFFSET_Z)    != 0 )
#define    IF_KEY_PRESSED_C       ( (RC_data.key.v & KEY_PRESSED_OFFSET_C)    != 0 )
#define    IF_KEY_PRESSED_B       ( (RC_data.key.v & KEY_PRESSED_OFFSET_B)    != 0 )
#define    IF_KEY_PRESSED_V       ( (RC_data.key.v & KEY_PRESSED_OFFSET_V)    != 0 )
#define    IF_KEY_PRESSED_F       ( (RC_data.key.v & KEY_PRESSED_OFFSET_F)    != 0 )
#define    IF_KEY_PRESSED_R       ( (RC_data.key.v & KEY_PRESSED_OFFSET_R)    != 0 )
#define    IF_KEY_PRESSED_CTRL    ( (RC_data.key.v & KEY_PRESSED_OFFSET_CTRL) != 0 )
#define    IF_KEY_PRESSED_SHIFT   ( (RC_data.key.v & KEY_PRESSED_OFFSET_SHIFT) != 0 )


#define    IF_KEY_PRESSED_Video_transmission         (  remote_control.keyboard_value )
#define    IF_KEY_PRESSED_W_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_W)    != 0 )
#define    IF_KEY_PRESSED_S_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_S)    != 0 )
#define    IF_KEY_PRESSED_A_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_A)    != 0 )
#define    IF_KEY_PRESSED_D_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_D)    != 0 )
#define    IF_KEY_PRESSED_Q_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_Q)    != 0 )
#define    IF_KEY_PRESSED_E_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_E)    != 0 )
#define    IF_KEY_PRESSED_G_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_G)    != 0 )
#define    IF_KEY_PRESSED_X_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_X)    != 0 )
#define    IF_KEY_PRESSED_Z_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_Z)    != 0 )
#define    IF_KEY_PRESSED_C_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_C)    != 0 )
#define    IF_KEY_PRESSED_B_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_B)    != 0 )
#define    IF_KEY_PRESSED_V_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_V)    != 0 )
#define    IF_KEY_PRESSED_F_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_F)    != 0 )
#define    IF_KEY_PRESSED_R_Video_transmission       ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_R)    != 0 )
#define    IF_KEY_PRESSED_CTRL_Video_transmission    ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_CTRL) != 0 )
#define    IF_KEY_PRESSED_SHIFT_Video_transmission   ( (remote_control.keyboard_value & KEY_PRESSED_OFFSET_SHIFT) != 0 )





/* ��ȡ���������ƶ��ٶ� */
#define    MOUSE_X_MOVE_SPEED    (RC_data.mouse.x)
#define    MOUSE_Y_MOVE_SPEED    (RC_data.mouse.y)
#define    MOUSE_Z_MOVE_SPEED    (RC_data.mouse.z)


#define    MOUSE_X_MOVE_SPEED_Video_transmission    (remote_control.mouse_x)
#define    MOUSE_Y_MOVE_SPEED_Video_transmission    (remote_control.mouse_y)
#define    MOUSE_Z_MOVE_SPEED_Video_transmission    (remote_control.mouse_z)



/* �����갴��״̬ 
   ����Ϊ1��û����Ϊ0*/
#define    IF_MOUSE_PRESSED_LEFT    (RC_data.mouse.press_l == 1)
#define    IF_MOUSE_PRESSED_RIGH    (RC_data.mouse.press_r == 1)


#define    IF_MOUSE_PRESSED_LEFT_Video_transmission    (remote_control.left_button_down == 1)
#define    IF_MOUSE_PRESSED_RIGH_Video_transmission    (remote_control.right_button_down == 1)


/* ----------------------- Data Struct ------------------------------------- */

void remote_control_init(void);


#pragma pack(1)

typedef struct
{
        __packed struct
        {
                int16_t ch[5];
                char s[2];
        } rc;
        __packed struct
        {
                int16_t x;
                int16_t y;
                int16_t z;
                uint8_t press_l;
                uint8_t press_r;
        } mouse;
        __packed struct
        {
                uint16_t v;
        } key;
} RC_ctrl_t;

#pragma pack()



extern RC_ctrl_t RC_data;

void sbus_to_rc(volatile const uint8_t *sbus_buf, RC_ctrl_t *rc_ctrl);
extern const RC_ctrl_t *get_remote_control_point(void);
void romote_filter(void);
int filtering_algorithm(int data, uint8_t channel);


typedef struct
{
	uint16_t CH1;//ͨ��1��ֵ
	uint16_t CH2;//ͨ��2��ֵ
	uint16_t CH3;//ͨ��3��ֵ
	uint16_t CH4;//ͨ��4��ֵ
	uint16_t CH5;//ͨ��5��ֵ
	uint16_t CH6;//ͨ��6��ֵ
	uint16_t CH7;//ͨ��7��ֵ
	uint16_t CH8;//ͨ��8��ֵ
	uint16_t CH9;//ͨ��9��ֵ
	uint16_t CH10;//ͨ��10��ֵ
	uint16_t CH11;//ͨ��11��ֵ
	uint16_t CH12;//ͨ��12��ֵ
	uint16_t CH13;//ͨ��13��ֵ
	uint16_t CH14;//ͨ��14��ֵ
	uint16_t CH15;//ͨ��15��ֵ
	uint16_t CH16;//ͨ��16��ֵ
	uint8_t ConnectState;//ң���������������״̬ 0=δ���ӣ�1=��������
}SBUS_CH_Struct;

extern SBUS_CH_Struct SBUS_CH;

void update_sbus(volatile const uint8_t *sbus_buf,SBUS_CH_Struct *SBUS_CH);

#endif






