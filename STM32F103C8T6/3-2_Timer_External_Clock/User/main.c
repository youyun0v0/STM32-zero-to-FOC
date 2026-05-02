#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Timer.h"

//外部时钟实验：利用对射式红外传感器做为外部时钟：挡光片从对射式红外传感器前经过时，DO引脚产生电平变化，CNT++，CNT>9时清零，执行中断函数（即Num++）

int main(void)
{
  OLED_Init(); //OLED初始化
  Timer_Init();
  OLED_ShowString(1, 1, "Num="); //在OLED上显示"Num="，位置为(1,1)
  OLED_ShowString(2, 1, "CNT=");
  while (1)
  {
    OLED_ShowNum(1, 5, GetNum(), 5); //在OLED上显示Num的值，位置为(1,5)，显示5个字符
    OLED_ShowNum(2, 5, Timer_GetCounter(), 5);
  }
}

