#ifndef __COUNTSENSOR_H
#define __COUNTSENSOR_H

void CountSensor_Init(void); //计数传感器初始化函数
//中断函数不需要声明，因为它的函数名是固定的，CPU会自动识别并调用这个函数执行中断处理逻辑
uint16_t GetNum(void); //获取计数值的函数声明

#endif
