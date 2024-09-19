/*
 * @Author: sethome
 * @Date: 2021-12-09 11:32:02
 * @FilePath: \RMc_Adam_GenralRobotSystem Ver1.0.4.20210818 Alpha\Algorithm\small_tool.h
 */

#ifndef __SMALL_TOOLS_H
#define	__SMALL_TOOLS_H

#include "cover_headerfile_h.h"

//键盘陀螺仪模式下鼠标统计yaw偏移量,此值会自己缓慢减小,防止甩头过快
typedef struct 
{
    float data[5];
    unsigned char index;
}sliding_variance;

void sliding_variance_init(sliding_variance *obj);
float sliding_variance_cal(sliding_variance *obj, float new);


typedef struct 
{
    float data[5];
    float sum;
    unsigned char index;
}sliding_average;
void sliding_average_init(sliding_average *obj);
float sliding_average_cal(sliding_average *obj, float new);
float Slope_function(float *now, float buffer, float ramp);

//end of file

#endif
