#include "stm32f10x.h"
#include "bsp_timer.h"
#include "bsp_gpio.h"

extern uint16_t Num; //声明外部变量Num

//定时器初始化函数(TIM2)
void Timer_Init(void)
{
  //1.选择外部时钟
  BSP_TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);
  //2.配置GPIO
  BSP_GPIO_InitPin(GPIOA, GPIO_Pin_0, GPIO_Mode_IPU, GPIO_Speed_50MHz); //配置PA0为上拉输入
  //3.初始化时基单元
  BSP_TIM_TimeBaseInit(TIM2, 1 - 1, 10 - 1, TIM_CounterMode_Up);
  //4.NVIC配置，设置TIM2中断优先级
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC分组2，抢占优先级和子优先级各占2位
  BSP_TIM_EnableUpdateIRQ(TIM2, TIM2_IRQn, 2, 1);
  //5.启动定时器
  TIM_Cmd(TIM2, ENABLE); //使能TIM2
}

//中断函数
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) //检查TIM2的更新中断标志位是否被置位
  {
    Num++; //每当TIM2产生一次更新事件，Num变量加1
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除TIM2的更新中断标志位
  }
}

//观察CNT的值
uint16_t Timer_GetCounter(void)
{
  return TIM_GetCounter(TIM2);
}