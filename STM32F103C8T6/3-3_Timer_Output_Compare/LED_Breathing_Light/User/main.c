#include "stm32f10x.h"
#include "Delay.h"
#include "Timer.h"
#include "PWM.h"
#include "OLED.h"

//呼吸灯实验：LED实现类似模拟信号的缓慢亮灭


int main(void)
{
  OLED_Init();
  PWM_Init(); 
  while (1)
  {
    for(uint8_t i=0;i<=100;i++)
    {
      PWM_SetCompare1(i);
      Delay_ms(10);
    }
    for(uint8_t i=100;i>0;i--)
    {
      PWM_SetCompare1(i);
      Delay_ms(10);
    }
  }
}

