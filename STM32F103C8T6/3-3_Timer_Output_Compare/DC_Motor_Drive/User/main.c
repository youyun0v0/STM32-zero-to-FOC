#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "Motor.h"
#include "OLED.h"

//转动电机
uint8_t KeyNum;
int8_t Speed;

int main(void)
{
  Key_Init();
  Motor_Init(); 
  OLED_Init();
  OLED_ShowString(1,1,"Speed=");
  Motor_SetSpeed(20);
  while (1)
  {
    KeyNum=Key_GetNum();
    if(KeyNum==1)
    {
      Speed+=20;
      if(Speed>100)
      {
        Speed=-100;
      }
    }
    Motor_SetSpeed(Speed);
    OLED_ShowSignedNum(1,7,Speed,3);
  }
}

