#include "stm32f10x.h"

extern uint16_t Num; //声明外部变量Num

//定时器初始化函数(TIM2)
void Timer_Init(void)
{
  //1.使能定时器时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  //2.选择时基单元的时钟
  //TIM_InternalClockConfig(TIM2); //选择内部时钟，这个可以不写，因为默认就是内部时钟
    //选择外部时钟
      //配置GPIO
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //上拉输入
      GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0; //外部时钟设置在A0
      GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
      GPIO_Init(GPIOA,&GPIO_InitStructure);

  TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00);   //选择外部时钟:TIM2,外部触发PSC,高电平触发,外部采样滤波器
  //3.初始化时基单元
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  //TIM_TimeBaseStructure.TIM_Period = 10000 - 1; //自动重载值ARR，计数器每1/10000秒+1，计数器从0开始，满10000-1=9999时产生更新事件，定时器周期为1秒
  //TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1; //预分频值PSC，定时器时钟频率 = 72MHz/(PSC+1)，设置为7200-1，定时器时钟频率为10kHz
  TIM_TimeBaseStructure.TIM_Period = 10 - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = 1 - 1;//手动计数没这么快，给小一点
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //给数字滤波、死区生成等内部采样时钟分频，在这里没啥影响，不分频即可
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数模式，设置为向上计数（还可以选向下计数，中央对齐）
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //重复计数器，表示计数器重复几次之后才会产生更新事件（高级定时器才有）
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据上面的配置初始化TIM2
  TIM_ClearFlag(TIM2, TIM_FLAG_Update); //清除TIM2的更新事件标志位，避免一开始就进入中断(因为定时器初始化后会有一个更新事件产生)
  //不然在计数实验中，计数起点就是从1开始的，而不是从0开始的
  //4.使能更新中断
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //使能TIM2的更新中断
  //5.NVIC配置，设置TIM2中断优先级
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC分组2，抢占优先级和子优先级各占2位
  NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //TIM2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //子优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //允许CPU响应TIM2中断
  NVIC_Init(&NVIC_InitStructure); //根据上面的配置初始化NVIC
  //6.启动定时器
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