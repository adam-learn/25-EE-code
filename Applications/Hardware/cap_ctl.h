#ifndef __CAP_H__
#define __CAP_H__

#include "cover_headerfile_h.h"


typedef struct // ��?��Y���䨬??��11��?
{
	uint8_t set_max_power; // �����
	uint8_t cache_energy;  // �������

	float remain_vol;	   // ʣ���ѹ
	float prediect_energy; // Ԥ������ 0 - 100%
}__attribute__((packed))	cap_t;
extern cap_t cap;


typedef struct
{
	uint8_t setPower;
	uint16_t cacheEnergy;
}__attribute__((packed))	can_send_cap_t;
extern can_send_cap_t send_data_cap;



void cap_handle_message(uint8_t data[8]);
void cap_update(void);
int cap_set_power(uint8_t set);
float cap_get_remain_vol(void);
float cap_get_predict_energy(void);
#endif







