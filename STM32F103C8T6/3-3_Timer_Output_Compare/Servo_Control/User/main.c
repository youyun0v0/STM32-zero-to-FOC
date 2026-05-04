#include "stm32f10x.h"
#include "Delay.h"
#include "Key.h"
#include "Servo.h"
#include "OLED.h"

//呼吸灯实验：LED实现类似模拟信号的缓慢亮灭
uint16_t Key_Num;
float Angle;

int main(void)
{
  OLED_Init();
  Servo_Init(); 
  Key_Init();
  Servo_SetAngle(90);
  OLED_ShowString(1,1,"Angle=");
  while (1)
  {
    Key_Num=Key_GetNum();
    if(Key_Num==1)
    {
      Angle+=30;
      if(Angle>180) Angle=0;
    }
    Servo_SetAngle(Angle);
    OLED_ShowNum(1,7,Angle,3);
  }
}

