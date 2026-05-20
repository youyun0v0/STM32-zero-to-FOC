#include "stm32f10x.h"
#include "bsp_timer.h"
#include "bsp_gpio.h"

void Encoder_Init(void)
{
  //1.配置GPIO
  BSP_GPIO_InitPin(GPIOA, GPIO_Pin_6 | GPIO_Pin_7, GPIO_Mode_IPU, GPIO_Speed_50MHz); //PA6和PA7配置为上拉输入

  //2.配置时基单元(无需再额外配置外部时钟了)
  BSP_TIM_TimeBaseInit(TIM3, 0, 65535, TIM_CounterMode_Up); //PSC=0 不分频；ARR最大，计数模式这里选择没有意义

  //3.配置输入捕获单元：只使用CH1,2的边沿检测与极性选择模块，其他模块可以删掉
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_ICStructInit(&TIM_ICInitStructure);//由于部分单元注释掉了，所以要先把结构体初始化为默认值，避免未配置的单元出现问题
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //选择通道1
    TIM_ICInitStructure.TIM_ICFilter = 0xf; //滤波
    //TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //这个模块之后还要在编码器接口模式配置函数里配置，不必重复配置
    //TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
    //TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //这俩模块无关
    TIM_ICInit(TIM3, &TIM_ICInitStructure);//初始化输入捕获单元

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2; //选择通道2
    TIM_ICInitStructure.TIM_ICFilter = 0xf; //滤波
    TIM_ICInit(TIM3, &TIM_ICInitStructure);//初始化输入捕获单元

  //4.配置编码器接口模式
  TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising); //编码器接口模式选择TI12，CH1和CH2电平均不反相
  
  //5.启动定时器
  TIM_Cmd(TIM3, ENABLE);
}

int16_t Encoder_GetCount(void)
{
  int16_t tmp;
  tmp = TIM_GetCounter(TIM3);
  TIM_SetCounter(TIM3, 0); //读完CNT的值后就清零，准备下一次计数
  return tmp;//返回CNT的值(这里的值指的是速度，CNT/delay时间)
}