#include "stm32f10x.h"

void Buzzer_OFF(void)
{
    // 设置PB12为低电平，关闭蜂鸣器
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

void Buzzer_Init(void)
{
    // 初始化蜂鸣器引脚B12
    GPIO_InitTypeDef GPIO_InitStructure;
    // 使能GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    // 配置PB12为推挽输出
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
    // 初始状态为关闭
    Buzzer_OFF();
}

void Buzzer_ON(void)
{
    // 设置PB12为高电平，打开蜂鸣器
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}



void Buzzer_Turn(void)
{
    // 切换PB12的状态
    if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == Bit_SET)
    {
        Buzzer_OFF();
    }
    else
    {
        Buzzer_ON();
    }
}