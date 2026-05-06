#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

void BSP_GPIO_EnableClock(GPIO_TypeDef *GPIOx);

/**
 * @brief 初始化单个 GPIO 引脚，并自动开启对应 GPIO 端口时钟
 *
 * @param GPIOx GPIO 端口，例如 GPIOA、GPIOB、GPIOC。
 * @param GPIO_Pin GPIO 引脚，例如 GPIO_Pin_0、GPIO_Pin_6。
 * @param GPIO_Mode GPIO 模式，例如 GPIO_Mode_Out_PP、GPIO_Mode_AF_PP、GPIO_Mode_IN_PP。
 * @param GPIO_Speed GPIO 输出速度，例如 GPIO_Speed_50MHz。输入模式下该参数影响不大。
 */
void BSP_GPIO_InitPin(GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin,
    GPIOMode_TypeDef GPIO_Mode,
    GPIOSpeed_TypeDef GPIO_Speed);

#endif 