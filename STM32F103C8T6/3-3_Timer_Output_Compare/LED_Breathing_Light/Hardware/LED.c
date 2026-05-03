//封装思想：
//1.注意要把Hardware文件夹添加进项目资源和C++编译器的包含路径中，否则会找不到
//2.LED.c负责主体代码，.h文件负责声明函数，定义宏，定义结构体等

#include "STM32F10x.h"

void LED_Init(void)
{
  //初始化GPIOA
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开GPIOA时钟（供电）
  GPIO_InitTypeDef GPIO_InitStructure;//引脚工作参数配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 ;//选择GPIOA的A1和A2引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出PUSH-PULL
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz（电平翻转的最大频率）
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
  GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2); //默认关闭LED（GPIO输出高电平）
}

void LED1_On(void)
{
  GPIO_ResetBits(GPIOA, GPIO_Pin_1); //GPIO输出低电平，点亮LED1
}

void LED1_Off(void)
{
  GPIO_SetBits(GPIOA, GPIO_Pin_1); //GPIO输出高电平，关闭LED1
}

void LED2_On(void)
{
  GPIO_ResetBits(GPIOA, GPIO_Pin_2); //GPIO输出低电平，点亮LED2
}

void LED2_Off(void)
{
  GPIO_SetBits(GPIOA, GPIO_Pin_2); //GPIO输出高电平，关闭LED2
}
//取反函数
void LED1_Turn(void)
{
  if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) //如果LED1当前是点亮的（GPIO输出低电平）
  //ReadOutputDataBit函数读取GPIOA的A1引脚的输出电平，如果返回值为0，说明当前输出电平为低电平，即LED1点亮了
    GPIO_SetBits(GPIOA, GPIO_Pin_1); //关闭LED1
  else
    GPIO_ResetBits(GPIOA, GPIO_Pin_1); //点亮LED1
}

void LED2_Turn(void)
{
  if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0) //如果LED2当前是点亮的（GPIO输出低电平）
    GPIO_SetBits(GPIOA, GPIO_Pin_2); //关闭LED2
  else
    GPIO_ResetBits(GPIOA, GPIO_Pin_2); //点亮LED2
}
