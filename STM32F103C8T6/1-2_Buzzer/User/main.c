#include "stm32f10x.h"
#include "Delay.h"
int main(void)
{
  //蜂鸣器I/O端接入PB12端口。输入低电平时蜂鸣器响，输入高电平时蜂鸣器不响。

	//初始化GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//打开GPIOB时钟（供电）
    GPIO_InitTypeDef GPIO_InitStructure;//引脚工作参数配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//选择GPIOB的B12引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz（电平翻转的最大频率）
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB12引脚
  while(1)
  {
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);//GPIOB12引脚输出低电平，蜂鸣器响
    Delay_ms(500);//延时500ms
    GPIO_SetBits(GPIOB, GPIO_Pin_12);//GPIOB12引脚输出高电平，蜂鸣器不响
    Delay_ms(500);//延时500ms
  }
  //超级大声！被蜂鸣器吓晕了
}

