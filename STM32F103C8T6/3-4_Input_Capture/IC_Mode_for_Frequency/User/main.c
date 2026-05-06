#include "stm32f10x.h"
#include "Delay.h"
#include "PWM.h"
#include "OLED.h"
#include "IC.h"

//实验：用A0口输出一个PWM波，再用A6口利用输入捕获测频率
int main(void)
{
  OLED_Init();
  PWM_Init();
  OLED_ShowString(1, 1, "Freq=00000Hz");
  //PA0口的输出波形配置
  PWM_SetPSC(720-1); //待测频率=72MHz/720/100=1kHz
  PWM_SetCompare1(50); //占空比50%

  //PA6口的输入捕获配置
  IC_Init();
  
  while (1)
  {
    OLED_ShowNum(1, 6, IC_GetFreq(),5);//显示频率
  }
}

