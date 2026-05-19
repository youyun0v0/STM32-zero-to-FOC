#include "stm32f10x.h"

//打开内部时钟：先调用BSP_TIM_InternalClockConfig(TIMx)选择内部时钟源，再调用BSP_TIM_TimeBaseInit(TIMx, Prescaler, Period, CounterMode)配置时基单元，最后调用TIM_Cmd(TIMx, ENABLE)启动定时器
//打开外部时钟：先调用BSP_TIM_ETRClockMode2Config(TIMx, ExtTRGPSC, ExtTRGPolarity, ExtTRGFilter)选择外部时钟源，再调用BSP_TIM_TimeBaseInit(TIMx, Prescaler, Period, CounterMode)配置时基单元，最后调用TIM_Cmd(TIMx, ENABLE)启动定时器

/**
 * @brief 打开TIM时钟
 * 
 * @param TIMx 选择定时器 TIM1、TIM2、TIM3、TIM4
 */
void BSP_TIM_EnableClock(TIM_TypeDef *TIMx)
{
    if (TIMx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }
    else if (TIMx == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }
    else if (TIMx == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }
    else if (TIMx == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }
}
/**
 * @brief 初始化时基单元
 * 
 * @param TIMx 选择定时器
 * @param Prescaler PSC预分频值
 * @param Period ARR自动重载值
 * @param CounterMode 计数模式，可选值有 TIM_CounterMode_Up、TIM_CounterMode_Down、TIM_CounterMode_CenterAligned1、TIM_CounterMode_CenterAligned2
 */
void BSP_TIM_TimeBaseInit(TIM_TypeDef *TIMx,
                          uint16_t Prescaler,
                          uint16_t Period,
                          uint16_t CounterMode)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    BSP_TIM_EnableClock(TIMx);

    TIM_TimeBaseStructure.TIM_Period = Period;
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//给数字滤波、死区生成等内部采样时钟分频，这里默认不分频
    TIM_TimeBaseStructure.TIM_CounterMode = CounterMode;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//高级计时器才有的重复计数器

    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
}
/**
 * @brief 选择内部时钟
 * 
 * @param TIMx 
 */
void BSP_TIM_InternalClockConfig(TIM_TypeDef *TIMx)
{
    BSP_TIM_EnableClock(TIMx);
    TIM_InternalClockConfig(TIMx);
}

/**
 * @brief 选择外部时钟：定时器外部时钟模式2
 * 
 * @param TIMx 定时器选择
 * @param ExtTRGPSC 外部触发预分频器。分频值可选1,2,4,8.可选择TIM_ExtTRGPSC_OFF,TIM_ExtTRGPSC_DIV2,TIM_ExtTRGPSC_DIV4
 * @param ExtTRGPolarity 外部触发极性，选择哪种边沿作为有效触发，可选择TIM_ExtTRGPolarity_NonInverted(上升沿), TIM_ExtTRGPolarity_Inverted

 * @param ExtTRGFilter 外部触发滤波器，0x00-0x0F之间
 */
void BSP_TIM_ETRClockMode2Config(TIM_TypeDef *TIMx,
                                 uint16_t ExtTRGPSC,
                                 uint16_t ExtTRGPolarity,
                                 uint16_t ExtTRGFilter)
{
    BSP_TIM_EnableClock(TIMx);
    TIM_ETRClockMode2Config(TIMx, ExtTRGPSC, ExtTRGPolarity, ExtTRGFilter);
}
/**
 * @brief NVIC配置，内含一次清空中断标志。例如BSP_TIM_EnableUpdateIRQ(TIM2, TIM2_IRQn, 2, 1);
 * 
 * @param TIMx 选择定时器
 * @param IRQChannel 定时器对应的NVIC中断通道，如TIM2_IRQn
 * @param PreemptionPriority 抢占优先级
 * @param SubPriority 子优先级
 */
void BSP_TIM_EnableUpdateIRQ(TIM_TypeDef *TIMx,
                             uint8_t IRQChannel,
                             uint8_t PreemptionPriority,
                             uint8_t SubPriority)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}