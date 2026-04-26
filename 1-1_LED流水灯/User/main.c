#include "stm32f10x.h"
#include "Delay.h"
int main(void)
{

	//初始化GPIOA
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开GPIOA时钟（供电）
    GPIO_InitTypeDef GPIO_InitStructure;//引脚工作参数配置
    //批量设置GPIOA的A0-A7引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//选择GPIOA的A0-A7引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz（电平翻转的最大频率）
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
  
  //开始点灯
  //几个函数的功能：
  //GPIO_ResetBits(GPIOA, GPIO_Pin_0);//给A0引脚设为0V(低电平)，点亮LED灯
  //GPIO_SetBits(GPIOA, GPIO_Pin_0);//给A0引脚设为3.3V(高电平)，熄灭LED灯
  //GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);//给A0引脚设为0V(低电平)，点亮LED灯
  //GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);//给A0引脚设为3.3V(高电平)，熄灭LED灯

  //这里点灯代码用开漏输出也可以
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出
  //GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
  //GPIO_ResetBits(GPIOA, GPIO_Pin_0);//给A0引脚设为0V(低电平)，点亮LED灯
  /*
  //这个是3-1的传统点灯法
  while(1)
  {
    GPIO_SetBits(GPIOA, GPIO_Pin_7);//把A7灯熄灭
    GPIO_ResetBits(GPIOA, GPIO_Pin_0);//点亮A0灯
    Delay_ms(100);//延时100ms
    GPIO_SetBits(GPIOA, GPIO_Pin_0);//熄灭A0灯
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);//点亮A1灯
    Delay_ms(100);//延时100ms
    GPIO_SetBits(GPIOA, GPIO_Pin_1);//熄灭A1灯
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);//点亮A2灯
    Delay_ms(100);//延时100ms
    GPIO_SetBits(GPIOA, GPIO_Pin_2);//熄灭A2灯
    GPIO_ResetBits(GPIOA, GPIO_Pin_3);//点亮A3灯
    Delay_ms(100);//延时100ms
    GPIO_SetBits(GPIOA, GPIO_Pin_3);//熄灭A3灯
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);//点亮A4灯
    Delay_ms(100);//延时100ms
    GPIO_SetBits(GPIOA, GPIO_Pin_4);//熄灭A4灯
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);//点亮A5灯
    Delay_ms(100);//延时100ms
    GPIO_SetBits(GPIOA, GPIO_Pin_5);//熄灭A5灯
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);//点亮A6灯
    Delay_ms(100);//延时100ms
    GPIO_SetBits(GPIOA, GPIO_Pin_6);//熄灭A6灯
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);//点亮A7灯
    Delay_ms(100);//延时100ms
  }
  */
  //也可以用一点二进制方式进行点亮
  //点亮所有灯：
  GPIO_Write(GPIOA, 0x00FF);//0000 0000 1111 1111，点亮A0-A7灯
  Delay_ms(100);//延时100ms
  while(1)
  {
    GPIO_Write(GPIOA, ~0x0001);//0000 0000 0000 0001，点亮A0灯
    //注意要取反。数值设为0是低电平，点亮灯
    Delay_ms(100);//延时100ms 
    GPIO_Write(GPIOA, ~0x0002);//0000 0000 0000 0010，点亮A1灯
    Delay_ms(100);//延时100ms
    GPIO_Write(GPIOA, ~0x0004);//0000 0000 0000 0100，点亮A2灯
    Delay_ms(100);//延时100ms
    GPIO_Write(GPIOA, ~0x0008);//0000 0000 0000 1000，点亮A3灯
    Delay_ms(100);//延时100ms
    GPIO_Write(GPIOA, ~0x0010);//0000 0000 0001 0000，点亮A4灯
    Delay_ms(100);//延时100ms
    GPIO_Write(GPIOA, ~0x0020);//0000 0000 0010 0000，点亮A5灯
    Delay_ms(100);//延时100ms
    GPIO_Write(GPIOA, ~0x0040);//0000 0000 0100 0000，点亮A6灯
    Delay_ms(100);//延时100ms
    GPIO_Write(GPIOA, ~0x0080);//0000 0000 1000 0000，点亮A7灯
    Delay_ms(100);//延时100ms
  }
  //}
}

