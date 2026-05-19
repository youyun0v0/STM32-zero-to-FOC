#include "stm32f10x.h"
#include "PWM.h"

void Motor_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开GPIOA时钟（供电）
    GPIO_InitTypeDef GPIO_InitStructure;//引脚工作参数配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 ;//初始化电机方向控制脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出PUSH-PULL
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz（电平翻转的最大频率）
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA

    PWM_Init();
}

void Motor_SetSpeed(int8_t Speed) //速度值在-100到100之间
{
    if(Speed>=0) //正转
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
        GPIO_ResetBits(GPIOA,GPIO_Pin_5); //设置电机旋转方向
        PWM_SetCompare3(Speed);
    }
    else{
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        GPIO_SetBits(GPIOA,GPIO_Pin_5); //设置电机旋转方向
        PWM_SetCompare3(-Speed);//CCR值必须是正数
    }
}

