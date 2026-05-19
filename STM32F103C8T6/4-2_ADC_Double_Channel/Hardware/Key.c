#include "stm32f10x.h"
#include "delay.h"

//按键设置在B1
//按键选择上拉输入模式：有一个上拉电阻。不触发按钮时，默认为高电平；触发按钮时，电平变为低电平
void Key_Init(void)
{
  //初始化GPIOB
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//打开GPIOB时钟（供电）
  GPIO_InitTypeDef GPIO_InitStructure;//引脚工作参数配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//选择GPIOB的B1引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入INPUT PULL-UP
  //不需要填频率，因为输入引脚不输出电平，不需要翻转，所以频率无意义
  //翻转频率指的是引脚电压从高电平变为低电平，或者从低电平变为高电平的最大“速度”
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB 
}

uint8_t Key_GetNum(void) //uint8_t=unsigned char，返回值是一个8位无符号整数，范围0-255
{
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) //如果B1引脚电平为低，说明按键被按下了
    {
        //阻塞式按键检测实例
        Delay_ms(20); //消抖，延时20ms(因为按下按键时，电平可能会有抖动，导致误判，所以需要延时20ms来消除抖动的影响)
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0); //按住不放时程序空转，防止重复触发
        Delay_ms(20); //消抖，延时20ms
        return 1; //返回1，表示按键1被按下了
    }
    else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0) //如果B11引脚电平为低，说明按键被按下了
    {
        Delay_ms(20); //消抖，延时20ms
        while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0); //等待按键释放，按键被按下时电平为低，按键被释放时电平为高，所以当电平为低时一直循环等待
        Delay_ms(20); //消抖，延时20ms
        return 2; //返回2，表示按键2被按下了
    }
    else
        return 0; //返回0，表示没有按键被按下
}