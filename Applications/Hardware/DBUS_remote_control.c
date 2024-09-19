/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       remote_control.c/h
  * @brief      遥控器处理，遥控器是通过类似SBUS的协议传输，利用DMA传输方式节约CPU
  *             资源，利用串口空闲中断来拉起处理函数，同时提供一些掉线重启DMA，串口
  *             的方式保证热插拔的稳定性。
  * @note       该任务是通过串口中断启动，不是freeRTOS任务
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-01-2019     RM              1. 完成
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#include "cover_headerfile_h.h"
#include "DBUS_remote_control.h"

#define Ka 0.03f // 滤波系数

extern UART_HandleTypeDef huart5;
extern DMA_HandleTypeDef hdma_uart5_rx;



RC_ctrl_t RC_data;
SBUS_CH_Struct SBUS_CH;


void sbus_to_rc(volatile const uint8_t *sbus_buf, RC_ctrl_t *rc_ctrl);

// receive data, 18 bytes one frame, but set 36 bytes
// 接收原始数据，为18个字节，给了36个字节长度，防止DMA传输越界

void remote_control_init(void)
{
		memset(&RC_data, 0, sizeof(RC_ctrl_t));
		memset(&SBUS_CH, 0, sizeof(SBUS_CH_Struct));
}

const RC_ctrl_t *get_remote_control_point(void)
{
  return &RC_data;
}

void sbus_to_rc(volatile const uint8_t *sbus_buf, RC_ctrl_t *rc_ctrl)
{
  if (sbus_buf == NULL || rc_ctrl == NULL)
  {
    return;
  }

  rc_ctrl->rc.ch[0] = (sbus_buf[0] | (sbus_buf[1] << 8)) & 0x07ff;        //!< Channel 0
  rc_ctrl->rc.ch[1] = ((sbus_buf[1] >> 3) | (sbus_buf[2] << 5)) & 0x07ff; //!< Channel 1
  rc_ctrl->rc.ch[2] = ((sbus_buf[2] >> 6) | (sbus_buf[3] << 2) |          //!< Channel 2
                       (sbus_buf[4] << 10)) &
                      0x07ff;
  rc_ctrl->rc.ch[3] = ((sbus_buf[4] >> 1) | (sbus_buf[5] << 7)) & 0x07ff; //!< Channel 3
  rc_ctrl->rc.s[0] = ((sbus_buf[5] >> 4) & 0x0003);                       //!< Switch left
  rc_ctrl->rc.s[1] = ((sbus_buf[5] >> 4) & 0x000C) >> 2;                  //!< Switch right
  rc_ctrl->mouse.x = sbus_buf[6] | (sbus_buf[7] << 8);                    //!< Mouse X axis
  rc_ctrl->mouse.y = sbus_buf[8] | (sbus_buf[9] << 8);                    //!< Mouse Y axis
  rc_ctrl->mouse.z = sbus_buf[10] | (sbus_buf[11] << 8);                  //!< Mouse Z axis
  rc_ctrl->mouse.press_l = sbus_buf[12];                                  //!< Mouse Left Is Press ?
  rc_ctrl->mouse.press_r = sbus_buf[13];                                  //!< Mouse Right Is Press ?
  rc_ctrl->key.v = sbus_buf[14] | (sbus_buf[15] << 8);                    //!< KeyBoard value
  rc_ctrl->rc.ch[4] = sbus_buf[16] | (sbus_buf[17] << 8);                 // NULL

  rc_ctrl->rc.ch[0] -= RC_CH_VALUE_OFFSET;
  rc_ctrl->rc.ch[1] -= RC_CH_VALUE_OFFSET;
  rc_ctrl->rc.ch[2] -= RC_CH_VALUE_OFFSET;
  rc_ctrl->rc.ch[3] -= RC_CH_VALUE_OFFSET;
  rc_ctrl->rc.ch[4] -= RC_CH_VALUE_OFFSET;
}

int filtering_algorithm(int data, uint8_t channel) // 遥控器数据滤波算法
{

  static int filtered_data[5] = {0};

  if (filtered_data[channel] < 50 && filtered_data[channel] > -50)
    filtered_data[channel] = data;
  else
    filtered_data[channel] = Ka * (data - filtered_data[channel]) + filtered_data[channel];

  return filtered_data[channel];
}

void romote_filter(void) // 滤波调用
{
  RC_data.rc.ch[0] = filtering_algorithm(RC_data.rc.ch[0], 0);
  RC_data.rc.ch[1] = filtering_algorithm(RC_data.rc.ch[1], 1);
  RC_data.rc.ch[2] = filtering_algorithm(RC_data.rc.ch[2], 2);
  RC_data.rc.ch[3] = filtering_algorithm(RC_data.rc.ch[3], 3);
  RC_data.rc.ch[4] = filtering_algorithm(RC_data.rc.ch[4], 4);
}


//将sbus信号转化为通道值
void update_sbus(volatile const uint8_t *sbus_buf,SBUS_CH_Struct *SBUS_CH)
{

  if (sbus_buf == NULL || SBUS_CH == NULL)
  {
    return;
  }	
        SBUS_CH->ConnectState = 1;
        SBUS_CH->CH1 =  (((uint16_t)sbus_buf[1] >> 0 | ((uint16_t)sbus_buf[2] << 8 )) & 0x07FF);
        SBUS_CH->CH2 =  (((uint16_t)sbus_buf[2] >> 3 | ((uint16_t)sbus_buf[3] << 5 )) & 0x07FF);
        SBUS_CH->CH3 =  (((uint16_t)sbus_buf[3] >> 6 | ((uint16_t)sbus_buf[4] << 2 ) | (int16_t)sbus_buf[5] << 10 ) & 0x07FF);
        SBUS_CH->CH4 =  (((uint16_t)sbus_buf[5] >> 1 | ((uint16_t)sbus_buf[6] << 7 )) & 0x07FF);
        SBUS_CH->CH5 =  (((int16_t)sbus_buf[6] >> 4 | ((int16_t)sbus_buf[7] << 4 )) & 0x07FF);
        SBUS_CH->CH6 =  (((int16_t)sbus_buf[7] >> 7 | ((int16_t)sbus_buf[8] << 1 ) | (int16_t)sbus_buf[9] << 9 ) & 0x07FF);
        SBUS_CH->CH7 =  (((int16_t)sbus_buf[9] >> 2 | ((int16_t)sbus_buf[10] << 6 )) & 0x07FF);
        SBUS_CH->CH8 =  (((int16_t)sbus_buf[10] >> 5 | ((int16_t)sbus_buf[11] << 3 )) & 0x07FF);
        SBUS_CH->CH9 =  (((int16_t)sbus_buf[12] << 0 | ((int16_t)sbus_buf[13] << 8 )) & 0x07FF);
        SBUS_CH->CH10 = (((int16_t)sbus_buf[13] >> 3 | ((int16_t)sbus_buf[14] << 5 )) & 0x07FF);
        SBUS_CH->CH11 = (((int16_t)sbus_buf[14] >> 6 | ((int16_t)sbus_buf[15] << 2 ) | (int16_t)sbus_buf[16] << 10 ) & 0x07FF);
        SBUS_CH->CH12 = (((int16_t)sbus_buf[16] >> 1 | ((int16_t)sbus_buf[17] << 7 )) & 0x07FF);
        SBUS_CH->CH13 = (((int16_t)sbus_buf[17] >> 4 | ((int16_t)sbus_buf[18] << 4 )) & 0x07FF);
        SBUS_CH->CH14 = (((int16_t)sbus_buf[18] >> 7 | ((int16_t)sbus_buf[19] << 1 ) | (int16_t)sbus_buf[20] << 9 ) & 0x07FF);
        SBUS_CH->CH15 = (((int16_t)sbus_buf[20] >> 2 | ((int16_t)sbus_buf[21] << 6 )) & 0x07FF);
        SBUS_CH->CH16 = (((int16_t)sbus_buf[21] >> 5 | ((int16_t)sbus_buf[22] << 3 )) & 0x07FF);

}
