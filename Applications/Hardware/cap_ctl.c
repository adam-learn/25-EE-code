
#include "cover_headerfile_h.h"
#include "cap_ctl.h"

extern FDCAN_HandleTypeDef hfdcan1;

cap_t cap;
can_send_cap_t send_data_cap;


void cap_handle_message(uint8_t data[8])
{
	static float rev_vol;

	memcpy(&rev_vol, data, sizeof(rev_vol));

	cap.remain_vol = rev_vol;
}

void cap_update(void)
{	
	static uint8_t can_send_data[8];
  static FDCAN_TxHeaderTypeDef tx_message;
//	uint32_t send_mail_box;

  tx_message.Identifier = 0x306;
  tx_message.IdType = FDCAN_STANDARD_ID;																// ��׼ID 
  tx_message.TxFrameType = FDCAN_DATA_FRAME;														// ����֡ 
  tx_message.DataLength = 0x08;																		// �������ݳ��� 
  tx_message.ErrorStateIndicator = FDCAN_ESI_ACTIVE;										// ���ô���״ָ̬ʾ 								
  tx_message.BitRateSwitch = FDCAN_BRS_OFF;															// �������ɱ䲨���� 
  tx_message.FDFormat = FDCAN_CLASSIC_CAN;															// ��ͨCAN��ʽ 
  tx_message.TxEventFifoControl = FDCAN_NO_TX_EVENTS;										// ���ڷ����¼�FIFO����, ���洢 
  tx_message.MessageMarker = 0x00; 			// ���ڸ��Ƶ�TX EVENT FIFO����ϢMaker��ʶ����Ϣ״̬����Χ0��0xFF 

	send_data_cap.setPower = cap.set_max_power;
	send_data_cap.cacheEnergy = cap.cache_energy;

	memcpy(can_send_data, &send_data_cap, sizeof(can_send_cap_t));

	HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1,&tx_message,can_send_data);
}

int cap_set_power(uint8_t set)
{
	if (set > 200 || set < 50)
		return -1;
	cap.set_max_power = set;
	cap_update();
	return 0;
}

float cap_get_remain_vol(void)
{
	return cap.remain_vol;
}

float cap_get_predict_energy(void)
{
	return cap.prediect_energy;
}
