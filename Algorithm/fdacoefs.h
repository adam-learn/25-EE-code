#ifndef  __FDACOEFS_H__
#define  __FDACOEFS_H__

/*
 * ��ɢʱ�� FIR �˲���(ʵ��)
 * ----------------
 * �˲����ṹ  : ֱ���� FIR
 * �˲�������  : 26
 * �ȶ�     : ��
 * ������λ   : �� (Type 2)
 */
/*
 * Warning - Filter coefficients were truncated to fit specified data type.  
 *   The resulting response may not match generated theoretical response.
 *   Use the Filter Design & Analysis Tool to design accurate
 *   single-precision filter coefficients.
 */
#define IMU_FIR_FILTER_LENGTH 26

extern float IMU_FIR_COFFES[IMU_FIR_FILTER_LENGTH];
/**
 * @brief 
 * 
 * @param state FIR�˲���״̬ ����ΪFIR_FILTER_LENGTH + 1
 * @param x 
 * @param y 
 * @param N 
 */
void FIR_process(float state[], float *x,float *y,int N, const float FIR_coffes[], int FIR_len);


#endif




