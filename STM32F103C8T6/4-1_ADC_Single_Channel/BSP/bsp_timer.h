#ifndef __BSP_TIM_H
#define __BSP_TIM_H

void BSP_TIM_EnableClock(TIM_TypeDef *TIMx);

void BSP_TIM_TimeBaseInit(TIM_TypeDef *TIMx,
                          uint16_t Prescaler,
                          uint16_t Period,
                          uint16_t CounterMode);

void BSP_TIM_InternalClockConfig(TIM_TypeDef *TIMx);

void BSP_TIM_ETRClockMode2Config(TIM_TypeDef *TIMx,
                                 uint16_t ExtTRGPSC,
                                 uint16_t ExtTRGPolarity,
                                 uint16_t ExtTRGFilter);

void BSP_TIM_EnableUpdateIRQ(TIM_TypeDef *TIMx,
                             uint8_t IRQChannel,
                             uint8_t PreemptionPriority,
                             uint8_t SubPriority);

#endif
