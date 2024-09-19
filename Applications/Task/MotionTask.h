#ifndef  __MOTIONTASK_H__
#define  __MOTIONTASK_H__

#include "cover_headerfile_h.h"


typedef struct 
{
	float x_s, y_s, w_s;
	float sin_beta, cos_beta;
	float relative_angle;
	uint32_t mul;
	pid_t chassis_rapid;
}__attribute__((packed)) MotionTask_data_t;

extern MotionTask_data_t MotionTask_data;

void LockModeTask(void);
void NormalModeTask(void);
void FlowModeTask(void);
void TankModeTask(void);
void SpinModeTask(void);
void LeanModeTask(void);

void MotionTask_mode_choose(uint8_t status);


#endif



