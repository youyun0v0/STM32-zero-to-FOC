#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"

uint8_t key_num = 0; //定义一个全局变量key_num，初始值为0，用于存储按键状态

//理想功能：按键1被按下时，LED1点亮，再按一下LED1熄灭；按键2被按下时，LED2点亮，再按一下LED2熄灭；没有按键被按下时，LED1和LED2都熄灭

int main(void)
{
  LED_Init(); //调用LED初始化函数
  Key_Init(); //调用按键初始化函数
  while(1)
  {
    key_num = Key_GetNum(); //调用按键检测函数，并将返回值存储在key_num变量中
    if(key_num == 1) //如果key_num的值为1，说明按键1被按下了
    {
      LED1_Turn(); //翻转LED2状态
    }
    if(key_num == 2) //如果key_num的值为2，说明按键2被按下了
    {
      LED2_Turn(); //翻转LED1状态
    }
  }

}

