/**
 * @file IMU_updata.h
 * @author sethome
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */



#ifndef __IMU_UPDATA__
#define __IMU_UPDATA__

#include "cover_headerfile_h.h"

extern unsigned  long ulTdleCycleCount;	

//struct IMU_t
//{
//	fp32 gyro[3];  // rad/s
//	fp32 accel[3]; // m/s^2
//	fp32 mag[3];   // ut
//	fp32 temp;	   // 温度
//	
//	float calibration[3];//角速度校准error

//	Attitude_3D_t KF; //卡尔曼滤波结果

//	struct
//	{
//		fp32 q[4];			   //四元数
//		fp32 pitch, yaw, roll; //欧拉角
//	} Mahony;

//	struct
//	{
//		fp32 q[4];			   //四元数
//		fp32 pitch, yaw, roll; //欧拉角
//	} madgwick;

//	struct
//	{
//		fp32 q[4];			   //四元数
//		fp32 pitch, yaw, roll; //欧拉角
//		int8_t err_code;
//		fp32 last_yaw;
//		fp32 yaw_rad_cnt;
//		fp32 yaw_angle_cnt;
//	} AHRS;

//	struct
//	{
//		fp32 q[4];			   //四元数
//		fp32 pitch, yaw, roll; //欧拉角
//		fp32 heading;		   //航向角(0-360)
//		int16_t error_code;
//		uint8_t accel_calibration_status;
//		uint8_t gyro_calibration_status;
//		fp32 last_yaw;
//	} BSX;
//};
//extern struct IMU_t IMU_data;


	typedef struct 
	{
		fp32 q[4];			   //四元数
		fp32 pitch, yaw, roll; //欧拉角
	} Mahony_t;

	typedef struct 
	{
		fp32 q[4];			   //四元数
		fp32 pitch, yaw, roll; //欧拉角
	} madgwick_t; 

	typedef struct 
	{
		fp32 q[4];			   //四元数
		fp32 pitch, yaw, roll; //欧拉角
		int8_t err_code;
		fp32 last_yaw;
		fp32 yaw_rad_cnt;
		fp32 yaw_angle_cnt;
	} AHRS_t;		
	
	typedef struct 
	{
		fp32 q[4];			   //四元数
		fp32 pitch, yaw, roll; //欧拉角
		fp32 heading;		   //航向角(0-360)
		int16_t error_code;
		uint8_t accel_calibration_status;
		uint8_t gyro_calibration_status;
		fp32 last_yaw;
	} BSX_t;

	
	
	
	typedef struct 
	{
		fp32 gyro[3];  // rad/s
		fp32 accel[3]; // m/s^2
		fp32 mag[3];   // ut
		fp32 temp;	   // 温度
		fp32 calibration[3];//角速度校准error					
		Attitude_3D_t KF; //卡尔曼滤波结果			
		Mahony_t Mahony;
		madgwick_t madgwick; 			
		AHRS_t AHRS;			
		BSX_t BSX;
	} IMU_t;
	extern IMU_t IMU_data;



// 外部调用
void IMU_init(void);   // IMU初始化
void IMU_updata(void); // IMU数据更新

void MagZero(void); // 清零地磁计
void Get_angle(fp32 q[4], fp32 *yaw, fp32 *pitch, fp32 *roll);//非调用Lib版本
void process_IMU_data(void);
float rad2degree(float a);
float degree2rad(float a);
#endif
	
	
	
	
	
// end of flie
