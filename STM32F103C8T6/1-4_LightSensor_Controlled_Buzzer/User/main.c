#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Buzzer.h"
#include "LightSensor.h"
//理想功能：当光敏电阻检测到有光时，蜂鸣器关闭；当光敏电阻检测到无光时，蜂鸣器打开。

int main(void)
{
  Buzzer_Init();
  LightSensor_Init();
  while (1)
  {
    if(LightSensor_Read() == 0) //有光
    {
      Buzzer_OFF();
    }
    else //无光
    {
      Buzzer_ON();
    }
  }
}

