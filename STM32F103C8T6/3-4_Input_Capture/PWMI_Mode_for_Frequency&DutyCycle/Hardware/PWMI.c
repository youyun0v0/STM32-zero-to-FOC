#include "stm32f10x.h"
#include "bsp_gpio.h"
#include "bsp_timer.h"

uint16_t PSC_PWMI=72-1;
uint16_t ARR_PWMI=65536-1;

void PWMI_Init(void)
{
    //1.GPIO初始化,开启GPIO时钟
    BSP_GPIO_InitPin(GPIOA, GPIO_Pin_6, GPIO_Mode_IPU, GPIO_Speed_50MHz);//初始化PA6为上拉输入
    //2.配置时基单元，开启TIM时钟
    TIM_InternalClockConfig(TIM3); //选择内部时钟TIM3.TIM2已经被用作生成PWM波
    BSP_TIM_TimeBaseInit(TIM3, PSC_PWMI, ARR_PWMI, TIM_CounterMode_Up); //初始化时基单元
        //ARR给最大，防止计数溢出；标准频率fc=72MHz/72=1MHz
    //3.配置两个输入捕获单元
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1; //选择通道1
    TIM_ICInitStructure.TIM_ICFilter = 0xf; //滤波
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; //上升沿捕获
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; //不分频
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //直连通道输入
       //这里也可以选择做两次ICInit，但是有更快捷的函数
    TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);//初始化PWMI  -> 这是与IC唯一不同的代码
    //4.选择从模式触发源
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);//触发源选择TI1FP1
    //5.选择从模式的触发操作
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);//从模式设置为复位
    //6.开启定时器
    TIM_Cmd(TIM3, ENABLE);
}

uint32_t PWMI_GetFreq(void)
{
    int fc=72*1e6/(PSC_PWMI+1);
    return fc/ (TIM_GetCapture1(TIM3)+1); //频率=fc/N ,N读取的是CCR的值
    //实际计数时，由于CNT是从0开始计数的，1000个计数单位对应CCR=999,所以要+1  
}

uint32_t PWMI_GetDuty(void) //读取占空比
{
    return 100*(1+TIM_GetCapture2(TIM3))/(1+TIM_GetCapture1(TIM3)); // CCR2 / CCR1 即可，同理两个数都各自+1
    //注意要乘100，因为返回值是无符号整数，不乘100绝对会返回0
    //而且100要乘前面（经典的csapp问题）
}