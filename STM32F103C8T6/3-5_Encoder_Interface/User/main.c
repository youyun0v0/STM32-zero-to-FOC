#include "stm32f10x.h"
#include "Delay.h"
#include "PWM.h"
#include "OLED.h"
#include "Encoder.h"

//实验：用编码器接口测速
//接线：A相-PA6-TIM3_CH1；B相-PA7-TIM3_CH2；
int main(void)
{
  Encoder_Init();
  OLED_Init();
  OLED_ShowString(1, 1, "CNT=");
  while (1)
  {
    OLED_ShowSignedNum(1, 5, Encoder_GetCount(), 5);  //读速度
    Delay_ms(1000); //每1s读一次，这样CNT的值每秒的转数（即转速）
  }
}

