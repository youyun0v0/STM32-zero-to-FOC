#include "stm32f10x.h"

volatile uint16_t Num; //计数变量，记录挡光片经过的次数

void CountSensor_Init(void) //外部中断配置
{
  //1.打开GPIO时钟,AFIO时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //配置外部中断需要用到AFIO
      //EXTI，NVIC两个外设无需手动开启时钟，库函数会自动开启
  //2.配置GPIOB.13引脚为输入上拉模式
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //选择GPIOB.13引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //输入上拉模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //GPIO速度，这个参数对输入引脚没有影响，可以随便设置
  GPIO_Init(GPIOB, &GPIO_InitStructure); //根据上面的配置初始化PB13
  //3.配置外部中断
  EXTI_InitTypeDef EXTI_InitStructure;
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13); //把PB13连接到EXTI13
    EXTI_InitStructure.EXTI_Line = EXTI_Line13; //选择EXTI13
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //中断模式(还可以选事件模式)
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发（拿出挡光器时Num++）
    EXTI_InitStructure.EXTI_LineCmd = ENABLE; //打开外部中断线
  EXTI_Init(&EXTI_InitStructure); //根据上面的配置初始化外部中断
  //4.配置NVIC
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC分组2，抢占优先级和响应优先级各占2位（都是0-3）
  NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn; //EXTI10-15全都合并在这个通道中
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应优先级0
    //只有一个中断，不存在优先级冲突，所以抢占优先级和响应优先级设置成什么都无所谓
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //允许CPU响应EXTI13
  NVIC_Init(&NVIC_InitStructure); //根据上面的配置初始化NVIC
}

//中断函数
//函数名是固定的，可以在startup_stm32f10x.s文件中找到这个函数的入口地址，并且在stm32f10x.h文件中找到这个函数对应的中断向量表位置(EXTI15_10_IRQn)，当外部中断14发生时，CPU会自动跳转到这个函数执行
void EXTI15_10_IRQHandler(void) 
{
  if(EXTI_GetITStatus(EXTI_Line13) == SET) //检查EXTI14的中断标志位是否被置位
  {
    Num++;// 处理EXTI13的逻辑
    EXTI_ClearITPendingBit(EXTI_Line13); // 清除中断标志位
  }
}

uint16_t GetNum(void)
{
  return Num;
}
