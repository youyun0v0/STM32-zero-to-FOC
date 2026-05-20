#include "stm32f10x.h"
#include "bsp_gpio.h"
#include "bsp_timer.h"

void PWM_Init(void)
{
    //1.配置时基单元
    BSP_TIM_InternalClockConfig(TIM2);//选择内部时钟
    BSP_TIM_TimeBaseInit(TIM2, 720 - 1, 100 - 1, TIM_CounterMode_Up);//初始化时基单元
    //1.5 如果需要用到引脚重映射，配置如下
    //    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//打开AFIO时钟
    //    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//重映射函数：部分重映射可以把TIM2CH1端口从A0重映射到A15
    //    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//解除PA15端口原来自带的端口功能，把PA15变成普通的GPIO口
    //2.初始化输出比较单元
        TIM_OCInitTypeDef TIM_OCInitStructure;
        TIM_OCStructInit(&TIM_OCInitStructure);//结构体赋初始值
        TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//设置输出比较模式:PWM1
        TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//设置输出比较极性：REF有效时，输出高电平
        TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//设置输出使能
        TIM_OCInitStructure.TIM_Pulse=0;//设置CCR,CCR=500时，高电平为0.5ms，由于舵机要求，参数范围为500-2500
        //剩下的结构体成员都是高级定时器才需要用的.由于只给部分成员赋值，为了避免不确定的问题，我们需要给结构体先赋一个初值，再修改我们关心的成员
    //3.初始化GPIO    
        TIM_OC1Init(TIM2,&TIM_OCInitStructure); 
        BSP_GPIO_InitPin(GPIOA, GPIO_Pin_0, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);//初始化PA0为TIM2CH1
    //4.启动定时器
        TIM_Cmd(TIM2, ENABLE); //使能TIM2
}
void PWM_SetCompare1(uint16_t Compare)
{
    TIM_SetCompare1(TIM2,Compare);//在运行过程中更改CH1的CCR值
}
void PWM_SetCompare2(uint16_t Compare)
{
    TIM_SetCompare2(TIM2,Compare);//在运行过程中更改CH2的CCR值
}

void PWM_SetCompare3(uint16_t Compare)
{
    TIM_SetCompare3(TIM2,Compare);//在运行过程中更改CH3的CCR值
}

void PWM_SetPSC(uint16_t PSC)
{
    TIM_PrescalerConfig(TIM2,PSC,TIM_PSCReloadMode_Immediate);//在运行过程中更改PSC值,写入的值立即生效（而非在更新事件生效）
}