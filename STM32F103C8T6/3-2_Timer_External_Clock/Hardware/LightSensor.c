#include "stm32f10x.h"

//光敏电阻D0端连接在B13引脚
void LightSensor_Init(void)
{
    // 初始化光敏传感器引脚
    GPIO_InitTypeDef GPIO_InitStructure;
    // 使能GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    // 配置PB13为输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // 下拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
}

uint8_t LightSensor_Read(void)
{
    // 读取PB13的状态，返回0表示有光，返回1表示无光
    //0->低电平—>有光；1->高电平—>无光
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}