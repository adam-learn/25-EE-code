#include "cover_headerfile_h.h"
#include "can_receive_send.h"

////��Դ��sethome&DM����

// �������
motor_measure_t motor_data[33];

// CAN�Ĵ�����������
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;//����ԭ����fdcan.c�ļ�
/**
************************************************************************
* @brief:      	can_filter_init(void)
* @param:       void
* @retval:     	void
* @details:    	CAN�˲�����ʼ��
************************************************************************
**/
void can_filter_init(void)
{
	FDCAN_FilterTypeDef fdcan_filter;
	
	fdcan_filter.IdType = FDCAN_STANDARD_ID;                       //��׼ID
	fdcan_filter.FilterIndex = 0;                                  //�˲�������                   
	fdcan_filter.FilterType = FDCAN_FILTER_RANGE; 	
	fdcan_filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;           //������0������FIFO0  
	fdcan_filter.FilterID1 = 0x0000;                              
	fdcan_filter.FilterID2 = 0xFFFF;

	HAL_FDCAN_ConfigFilter(&hfdcan1, &fdcan_filter);
	HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE);
	HAL_FDCAN_Start(&hfdcan1);
	HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
		
	HAL_FDCAN_ConfigFilter(&hfdcan2, &fdcan_filter);
	HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE);
	HAL_FDCAN_Start(&hfdcan2);
	HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);

	HAL_FDCAN_ConfigFilter(&hfdcan3, &fdcan_filter);
	HAL_FDCAN_ConfigGlobalFilter(&hfdcan3, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE);
	HAL_FDCAN_Start(&hfdcan3);
	HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);

//__HAL_FDCAN_ENABLE_IT(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE);//��FIFO0����Ϣ�ж�
//HAL_NVIC_EnableIRQ(FDCAN1_IT0_IRQn);//��FDCAN1_IT0_IRQn�жϣ�	

//  if(HAL_FDCAN_ConfigFilter(&hfdcan1, &fdcan_filter) != HAL_OK)
//	{
//		Error_Handler();
//	}
//  if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* Start the FDCAN module */
//  if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
//  {
//    Error_Handler();
//  }	
//	/* ����RX FIFO0���������ж� */
//  if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
//  {
//    Error_Handler();
//  }


//	__HAL_FDCAN_ENABLE_IT(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE);//��FIFO0����Ϣ�ж�
//	HAL_NVIC_EnableIRQ(FDCAN2_IT0_IRQn);//��FDCAN2_IT0_IRQn�жϣ�	

//  if(HAL_FDCAN_ConfigFilter(&hfdcan2, &fdcan_filter) != HAL_OK)
//	{
//		Error_Handler();
//	}
//  if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* Start the FDCAN module */
//  if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
//  {
//    Error_Handler();
//  }	
//	/* ����RX FIFO0���������ж� */
//  if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
//  {
//    Error_Handler();
//  }

//	__HAL_FDCAN_ENABLE_IT(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE);//��FIFO0����Ϣ�ж�
//	HAL_NVIC_EnableIRQ(FDCAN3_IT0_IRQn);//��FDCAN3_IT0_IRQn�жϣ�	
//	
//  if(HAL_FDCAN_ConfigFilter(&hfdcan3, &fdcan_filter) != HAL_OK)

//	{
//		Error_Handler();
//	}
//  if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan3, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
//  {
//    Error_Handler();
//  }	
//  /* Start the FDCAN module */
//  if (HAL_FDCAN_Start(&hfdcan3) != HAL_OK)
//  {
//    Error_Handler();
//  }	
//	/* ����RX FIFO0���������ж� */
//  if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
//  {
//    Error_Handler();
//  }

}


/**
************************************************************************
* @brief:      	fdcanx_send_data(FDCAN_HandleTypeDef *hfdcan, uint16_t id, uint8_t *data, uint32_t len)
* @param:       hfdcan��FDCAN���
* @param:       id��CAN�豸ID
* @param:       data�����͵�����
* @param:       len�����͵����ݳ���
* @retval:     	void
* @details:    	��������
************************************************************************
**/
int a;
uint8_t fdcanx_send_data(FDCAN_HandleTypeDef *hfdcan, uint16_t id, uint8_t *data, uint32_t len)
{	
	FDCAN_TxHeaderTypeDef TxHeader;
	
  TxHeader.Identifier = id;
  TxHeader.IdType = FDCAN_STANDARD_ID;																// ��׼ID 
  TxHeader.TxFrameType = FDCAN_DATA_FRAME;														// ����֡ 
  TxHeader.DataLength = len << 16;																		// �������ݳ��� 
  TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;										// ���ô���״ָ̬ʾ 								
  TxHeader.BitRateSwitch = FDCAN_BRS_OFF;															// �������ɱ䲨���� 
  TxHeader.FDFormat = FDCAN_CLASSIC_CAN;															// ��ͨCAN��ʽ 
  TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;										// ���ڷ����¼�FIFO����, ���洢 
  TxHeader.MessageMarker = 0x00; 			// ���ڸ��Ƶ�TX EVENT FIFO����ϢMaker��ʶ����Ϣ״̬����Χ0��0xFF                
    
  if(HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TxHeader, data)!=HAL_OK) 
		a = 1;
		//return 1;//����
	return 0;	
}

/**
************************************************************************
* @brief:      	fdcanx_receive(FDCAN_HandleTypeDef *hfdcan, uint8_t *buf)
* @param:       hfdcan��FDCAN���
* @param:       buf���������ݻ���
* @retval:     	���յ����ݳ���
* @details:    	��������
************************************************************************
**/
uint8_t fdcanx_receive(FDCAN_HandleTypeDef *hfdcan,	FDCAN_RxHeaderTypeDef *fdcan_RxHeader, uint8_t *buf)
{	
  if(HAL_FDCAN_GetRxMessage(hfdcan,FDCAN_RX_FIFO0,fdcan_RxHeader, buf)!=HAL_OK)
		return 0;//��������
  return fdcan_RxHeader->DataLength>>16;	
}

// ������ݶ�ȡ
void get_motor_measure(motor_measure_t *ptr, uint8_t data[])
{
  (ptr)->last_ecd = (ptr)->ecd;
  (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);
  (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);
  (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]);
  (ptr)->temperate = (data)[6];
}


void process_motor_data(motor_measure_t *motor_data)
{
  // ������Ȧ��
  if (motor_data->last_ecd > 7000 && motor_data->ecd < 1000)
    motor_data->ecd_cnt += ((ECD_MAX - motor_data->last_ecd) + motor_data->ecd);
  else if (motor_data->last_ecd < 1000 && motor_data->ecd > 7000)
    motor_data->ecd_cnt -= ((ECD_MAX - motor_data->ecd) + motor_data->last_ecd);
  else
    motor_data->ecd_cnt += (motor_data->ecd - motor_data->last_ecd);
}



void decode_as_3508(can_id motorID)
{
  // ��������ٶ�
  motor_data[motorID].round_speed = motor_data[motorID].speed_rpm / 60.0f / M3508_P;
  // �����ܽǶ�
  motor_data[motorID].angle_cnt = motor_data[motorID].ecd_cnt / ECD_MAX / M3508_P * 360.00f;
}


void decode_as_2006(can_id motorID)
{
  // ��������ٶ�
  motor_data[motorID].round_speed = motor_data[motorID].speed_rpm / 60.0f / M2006_P;
  // �����ܽǶ�
  motor_data[motorID].angle_cnt = motor_data[motorID].ecd_cnt / ECD_MAX / M2006_P * 360.00f;
}

void decode_as_6020(can_id motorID)
{
  // ��������ٶ�
  motor_data[motorID].round_speed = motor_data[motorID].speed_rpm / ECD_MAX * 360.0f;
  // �����ܽǶ�
  motor_data[motorID].angle_cnt = motor_data[motorID].ecd_cnt/ ECD_MAX * 360.00f;

  // ������ԽǶ� -180~180 �������ȶ�ʧ �ܽǶȹ���ʱ
  float angle = motor_data[motorID].angle_cnt - motor_data[motorID].angle_zero;
  uint32_t mul = abs((int)angle) / 180;
  if (angle > 180.0f)
  {
    if (mul % 2 == 1) // ����-180��
      angle -= (mul + 1) * 180;
    else // ����180��
      angle -= mul * 180;
  }
  if (angle < -180.0f)
  {
    if (mul % 2 == 1) // ����180��
      angle += (mul + 1) * 180;
    else // ����-180��
      angle += mul * 180;
  }
  motor_data[motorID].angle = angle;
}




void decode_as_3508_Yaw_Root(can_id motorID)//  19*52.56/28.65
{
  // ��������ٶ�
  motor_data[motorID].round_speed = motor_data[motorID].speed_rpm / 60.0f / 34.86f;
  // �����ܽǶ�
  motor_data[motorID].angle_cnt = motor_data[motorID].ecd_cnt / ECD_MAX / 34.86f * 360.00f;
}

void decode_as_3508_Pitch_Root(can_id motorID)//  19*70.03/22.28
{
  // ��������ٶ�
  motor_data[motorID].round_speed = motor_data[motorID].speed_rpm / 60.0f / 59.72f;
  // �����ܽǶ�
  motor_data[motorID].angle_cnt = motor_data[motorID].ecd_cnt / ECD_MAX / 59.72f * 360.00f;
}

void decode_as_2006_Roll_Root(can_id motorID)//  36*91.5/33
{
  // ��������ٶ�
  motor_data[motorID].round_speed = motor_data[motorID].speed_rpm / 60.0f / 99.82f;
  // �����ܽǶ�
  motor_data[motorID].angle_cnt = motor_data[motorID].ecd_cnt / ECD_MAX / 99.82f * 360.00f;
}

void decode_as_2006_pitch_end(can_id motorID)
{
  // ��������ٶ�
  motor_data[motorID].round_speed = motor_data[motorID].speed_rpm / 60.0f / 60.0f;
  // �����ܽǶ�
  motor_data[motorID].angle_cnt = motor_data[motorID].ecd_cnt / ECD_MAX / 60.0f * 360.00f;
}









// �����������
motor_measure_t get_motor_data(can_id motorID) // ��ȡ�������
{
  return motor_data[motorID];
}

// ����������
void set_motor(int16_t val, can_id motorID) // �趨������
{
  motor_data[motorID].set = val; // val
}

void set_motor_offset(can_id motorID, float angle)
{
  motor_data[motorID].angle_zero = angle;
}

void clear_motor_cnt(can_id motorID)
{
  motor_data[motorID].ecd_cnt = 0;
}


// CAN1���͵���
void CAN1_send_current(void) // ���͵�����Ƶ���
{
  uint8_t can_send_data[8];
  static FDCAN_TxHeaderTypeDef tx_message;
//  uint32_t send_mail_box;

	
  // ����ǰ4��
  tx_message.Identifier = CAN_1_4_SIGN_ID;
  tx_message.IdType = FDCAN_STANDARD_ID;																// ��׼ID 
  tx_message.TxFrameType = FDCAN_DATA_FRAME;														// ����֡ 
  tx_message.DataLength = 0x08;																		// �������ݳ��� 
  tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;										// ���ô���״ָ̬ʾ 								
  tx_message.BitRateSwitch = FDCAN_BRS_OFF;															// �������ɱ䲨���� 
  tx_message.FDFormat = FDCAN_CLASSIC_CAN;															// ��ͨCAN��ʽ 
  tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;										// ���ڷ����¼�FIFO����, ���洢 
  tx_message.MessageMarker = 0x00; 			// ���ڸ��Ƶ�TX EVENT FIFO����ϢMaker��ʶ����Ϣ״̬����Χ0��0xFF 	

	
  can_send_data[0] = (motor_data[CAN_1_1].set >> 8);
  can_send_data[1] = motor_data[CAN_1_1].set;

  can_send_data[2] = (motor_data[CAN_1_2].set >> 8);
  can_send_data[3] = motor_data[CAN_1_2].set;

  can_send_data[4] = (motor_data[CAN_1_3].set >> 8);
  can_send_data[5] = motor_data[CAN_1_3].set;

  can_send_data[6] = (motor_data[CAN_1_4].set >> 8);
  can_send_data[7] = motor_data[CAN_1_4].set;
	
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &tx_message, can_send_data);

  // ���ͺ�4��
  tx_message.Identifier = CAN_5_8_SIGN_ID;

  can_send_data[0] = (motor_data[CAN_1_5].set >> 8);
  can_send_data[1] = motor_data[CAN_1_5].set;

  can_send_data[2] = (motor_data[CAN_1_6].set >> 8);
  can_send_data[3] = motor_data[CAN_1_6].set;

  can_send_data[4] = (motor_data[CAN_1_7].set >> 8);
  can_send_data[5] = motor_data[CAN_1_7].set;

  can_send_data[6] = (motor_data[CAN_1_8].set >> 8);
  can_send_data[7] = motor_data[CAN_1_8].set;
	
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &tx_message, can_send_data);
}


// CAN2���͵���
void CAN2_send_current(void) // ���͵�����Ƶ���
{
  uint8_t can_send_data[8];
  static FDCAN_TxHeaderTypeDef tx_message;
//  uint32_t send_mail_box;

	
  // ����ǰ4��
  tx_message.Identifier = CAN_1_4_SIGN_ID;
  tx_message.IdType = FDCAN_STANDARD_ID;																// ��׼ID 
  tx_message.TxFrameType = FDCAN_DATA_FRAME;														// ����֡ 
  tx_message.DataLength = 0x08;																		// �������ݳ��� 
  tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;										// ���ô���״ָ̬ʾ 								
  tx_message.BitRateSwitch = FDCAN_BRS_OFF;															// �������ɱ䲨���� 
  tx_message.FDFormat = FDCAN_CLASSIC_CAN;															// ��ͨCAN��ʽ 
  tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;										// ���ڷ����¼�FIFO����, ���洢 
  tx_message.MessageMarker = 0x00; 			// ���ڸ��Ƶ�TX EVENT FIFO����ϢMaker��ʶ����Ϣ״̬����Χ0��0xFF 	

	
  can_send_data[0] = (motor_data[CAN_2_1].set >> 8);
  can_send_data[1] = motor_data[CAN_2_1].set;

  can_send_data[2] = (motor_data[CAN_2_2].set >> 8);
  can_send_data[3] = motor_data[CAN_2_2].set;

  can_send_data[4] = (motor_data[CAN_2_3].set >> 8);
  can_send_data[5] = motor_data[CAN_2_3].set;

  can_send_data[6] = (motor_data[CAN_2_4].set >> 8);
  can_send_data[7] = motor_data[CAN_2_4].set;
	
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &tx_message, can_send_data);

  // ���ͺ�4��
  tx_message.Identifier = CAN_5_8_SIGN_ID;

  can_send_data[0] = (motor_data[CAN_2_5].set >> 8);
  can_send_data[1] = motor_data[CAN_2_5].set;

  can_send_data[2] = (motor_data[CAN_2_6].set >> 8);
  can_send_data[3] = motor_data[CAN_2_6].set;

  can_send_data[4] = (motor_data[CAN_2_7].set >> 8);
  can_send_data[5] = motor_data[CAN_2_7].set;

  can_send_data[6] = (motor_data[CAN_2_8].set >> 8);
  can_send_data[7] = motor_data[CAN_2_8].set;
	
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &tx_message, can_send_data);
}



// CAN3���͵���
void CAN3_send_current(void) // ���͵�����Ƶ���
{
  uint8_t can_send_data[8];
  static FDCAN_TxHeaderTypeDef tx_message;
//  uint32_t send_mail_box;

	
  // ����ǰ4��
  tx_message.Identifier = CAN_1_4_SIGN_ID;
  tx_message.IdType = FDCAN_STANDARD_ID;																// ��׼ID 
  tx_message.TxFrameType = FDCAN_DATA_FRAME;														// ����֡ 
  tx_message.DataLength = 0x08;																		// �������ݳ��� 
  tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;										// ���ô���״ָ̬ʾ 								
  tx_message.BitRateSwitch = FDCAN_BRS_OFF;															// �������ɱ䲨���� 
  tx_message.FDFormat = FDCAN_CLASSIC_CAN;															// ��ͨCAN��ʽ 
  tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;										// ���ڷ����¼�FIFO����, ���洢 
  tx_message.MessageMarker = 0x00; 			// ���ڸ��Ƶ�TX EVENT FIFO����ϢMaker��ʶ����Ϣ״̬����Χ0��0xFF 	

	
  can_send_data[0] = (motor_data[CAN_3_1].set >> 8);
  can_send_data[1] = motor_data[CAN_3_1].set;

  can_send_data[2] = (motor_data[CAN_3_2].set >> 8);
  can_send_data[3] = motor_data[CAN_3_2].set;

  can_send_data[4] = (motor_data[CAN_3_3].set >> 8);
  can_send_data[5] = motor_data[CAN_3_3].set;

  can_send_data[6] = (motor_data[CAN_3_4].set >> 8);
  can_send_data[7] = motor_data[CAN_3_4].set;
	
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &tx_message, can_send_data);

  // ���ͺ�4��
  tx_message.Identifier = CAN_5_8_SIGN_ID;

  can_send_data[0] = (motor_data[CAN_3_5].set >> 8);
  can_send_data[1] = motor_data[CAN_3_5].set;

  can_send_data[2] = (motor_data[CAN_3_6].set >> 8);
  can_send_data[3] = motor_data[CAN_3_6].set;

  can_send_data[4] = (motor_data[CAN_3_7].set >> 8);
  can_send_data[5] = motor_data[CAN_3_7].set;

  can_send_data[6] = (motor_data[CAN_3_8].set >> 8);
  can_send_data[7] = motor_data[CAN_3_8].set;
	
	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan3, &tx_message, can_send_data);
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	
  FDCAN_RxHeaderTypeDef rx_header; // CAN ����ָ��
  uint8_t rx_data[8];            // ��ȡ��������
		
  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
  {
		if(hfdcan == &hfdcan1)
		{			
			fdcanx_receive(hfdcan,&rx_header,rx_data);		
			get_motor_measure(&motor_data[rx_header.Identifier - CAN_ID1], rx_data);
			process_motor_data(&motor_data[rx_header.Identifier - CAN_ID1]);			
		}
	  else if(hfdcan == &hfdcan2)
		{
			fdcanx_receive(hfdcan,&rx_header,rx_data);							
			get_motor_measure(&motor_data[11+rx_header.Identifier - CAN_ID1], rx_data);
			process_motor_data(&motor_data[11+rx_header.Identifier - CAN_ID1]);
		}
		else if(hfdcan == &hfdcan3)
		{
			fdcanx_receive(hfdcan,&rx_header,rx_data);							
			get_motor_measure(&motor_data[22+rx_header.Identifier - CAN_ID1], rx_data);
			process_motor_data(&motor_data[22+rx_header.Identifier - CAN_ID1]);
		}
	}
}

















