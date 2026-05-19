#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "ADC.h"

//实验：用电位器的模拟电压测试ADC功能

uint16_t AD_Value; //全局变量，存储ADC转换结果
float AD_Voltage; //全局变量，存储电压值

int main(void)
{
  OLED_Init();
  AD_Init();
  OLED_ShowString(1, 1, "ADValue=");
  OLED_ShowString(2, 1, "ADVoltage=0.00V");
  while (1)
  {
    AD_Value = AD_GetValue();
    OLED_ShowNum(1, 9, AD_Value, 4);
    AD_Voltage = (float)AD_Value * 3.3 / 4096.0; //参考电压为3.3V，12位ADC，线性映射
    OLED_ShowNum(2, 11, AD_Voltage, 1); //整数部分
    OLED_ShowNum(2, 13, (uint16_t)(AD_Voltage * 100) % 100, 2); //小数部分
    Delay_ms(100);
  }
}

