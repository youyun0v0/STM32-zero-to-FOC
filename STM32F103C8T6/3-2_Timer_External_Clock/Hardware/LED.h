#ifndef __LED_H
#define __LED_H  //防止重复包含头文件

void LED_Init(void); //声明这个函数可以被外部调用
void LED1_On(void);
void LED1_Off(void);
void LED2_On(void);
void LED2_Off(void);
void LED1_Turn(void); //声明LED1取反函数
void LED2_Turn(void); //声明LED2取反函数

#endif
