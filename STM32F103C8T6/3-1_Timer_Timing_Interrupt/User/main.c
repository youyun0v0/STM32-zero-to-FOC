#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

//显示器每秒变量+1
uint16_t Num=0;

int main(void)
{
  OLED_Init(); //OLED初始化
  Timer_Init(); //定时器初始化
  OLED_ShowString(1, 1, "Num="); //在OLED上显示"Num="，位置为(1,1)
  while (1)
  {
    TIM2_IRQHandler(); //调用定时器中断函数，更新Num变量
    OLED_ShowNum(1, 5, Num, 5); //在OLED上显示Num变量，位置为(1,5)，宽度为5位
    OLED_ShowNum(2, 5, TIM_GetCounter(TIM2), 5); //在OLED上显示TIM2的当前CNT值，位置为(2,5)，宽度为5位
    //从0自增到9999
  }
}

