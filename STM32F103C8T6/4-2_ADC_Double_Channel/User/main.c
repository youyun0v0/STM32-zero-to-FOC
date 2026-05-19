#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "ADC.h"

//实验：多通道ADC

uint16_t AD0, AD1, AD2, AD3;

int main(void)
{
  OLED_Init();
  AD_Init();
  OLED_ShowString(1, 1, "AD0:");
  OLED_ShowString(2, 1, "AD1:");
  OLED_ShowString(3, 1, "AD2:");
  OLED_ShowString(4, 1, "AD3:");
  while (1)
  {
    AD0 = AD_GetValue(ADC_Channel_0); //读取第0通道
    AD1 = AD_GetValue(ADC_Channel_1); //读取第1通道
    AD2 = AD_GetValue(ADC_Channel_2); //读取第2通道
    AD3 = AD_GetValue(ADC_Channel_3); //读取第3通道
    OLED_ShowNum(1, 5, AD0, 4);
    OLED_ShowNum(2, 5, AD1, 4); 
    OLED_ShowNum(3, 5, AD2, 4);
    OLED_ShowNum(4, 5, AD3, 4);
    Delay_ms(100);
  }
}

