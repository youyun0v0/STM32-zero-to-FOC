#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

//对射式红外传感器实验：挡光片从对射式红外传感器前经过时，DO引脚产生电平变化，Num变量加1，并在OLED上显示Num的值

int main(void)
{
  OLED_Init(); //OLED初始化
  CountSensor_Init(); //计数传感器初始化
  OLED_ShowString(1, 1, "Num="); //在OLED上显示"Num="，位置为(1,1)
  while (1)
  {
    OLED_ShowNum(1, 5, GetNum(), 5); //在OLED上显示Num的值，位置为(1,5)，显示5个字符
  }
}

