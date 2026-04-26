#include "stm32f10x.h"
#include "Delay.h"
int main(void)
{

	//初始化GPIOA
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开GPIOA时钟（供电）
  GPIO_InitTypeDef GPIO_InitStructure;//引脚工作参数配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//选择GPIOA的A0引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出PUSH-PULL
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz（电平翻转的最大频率）
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
  
  //开始点灯
  //几个函数的功能：
  //GPIO_ResetBits(GPIOA, GPIO_Pin_0);//给A0引脚设为0V(低电平)，点亮LED灯
  //GPIO_SetBits(GPIOA, GPIO_Pin_0);//给A0引脚设为3.3V(高电平)，熄灭LED灯
  //GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);//给A0引脚设为0V(低电平)，点亮LED灯
  //GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);//给A0引脚设为3.3V(高电平)，熄灭LED灯
  //GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)0);//BitAction是一个枚举类型，0对应Bit_RESET,低电平
  //GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)1);//BitAction=1对应Bit_SET,高电平

  //这里点灯代码用开漏输出也可以
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出OPEN-DRAIN
  //GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
  //GPIO_ResetBits(GPIOA, GPIO_Pin_0);//给A0引脚设为0V(低电平)，点亮LED灯

  //闪烁代码
  while(1)
  {
    GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);//点亮
    Delay_ms(1000);//延时1秒
    GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);//熄灭
    Delay_ms(1000);//延时1秒
  }
  
}

