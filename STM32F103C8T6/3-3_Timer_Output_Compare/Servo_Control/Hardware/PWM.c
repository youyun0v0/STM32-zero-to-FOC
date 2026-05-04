#include "stm32f10x.h"

void PWM_Init(void)
{
    //1.配置时基单元，可以找Timer.c代码，不需要打开中断，配置NVIC
        //1.使能定时器时钟
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
        //2.选择时基单元的时钟
        TIM_InternalClockConfig(TIM2); //选择内部时钟
        //3.初始化时基单元
        TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
        TIM_TimeBaseStructure.TIM_Period = 20000 - 1; //自动重载值ARR，分辨率1/(ARR+1)=1%
        TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; //预分频值PSC，舵机要求50Hz
        TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //给数字滤波、死区生成等内部采样时钟分频，在这里没啥影响，不分频即可
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数模式，设置为向上计数（还可以选向下计数，中央对齐）
        TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //重复计数器，表示计数器重复几次之后才会产生更新事件（高级定时器才有）
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据上面的配置初始化TIM2
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
        TIM_OC2Init(TIM2,&TIM_OCInitStructure); //由于我们使用的是TIM2的OC2通道，查引脚定义表可知其复用在PA1引脚上
    //3.初始化GPIOA
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开GPIOA时钟（供电）
        GPIO_InitTypeDef GPIO_InitStructure;//引脚工作参数配置
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//选择GPIOA的A1引脚
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//选择复用推挽输出（引脚不再由普通GPIO控制，而是给了片上的外设TIM2_CH1控制）
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz（电平翻转的最大频率）
        GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA
    //4.启动定时器
        TIM_Cmd(TIM2, ENABLE); //使能TIM2
}

void PWM_SetCompare2(uint16_t Compare)
{
    TIM_SetCompare2(TIM2,Compare);//在运行过程中更改CH1的CCR值
}