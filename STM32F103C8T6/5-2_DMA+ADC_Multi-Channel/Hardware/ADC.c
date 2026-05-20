#include "stm32f10x.h"
#include "bsp_gpio.h"

void AD_Init(void) //与ADC_Init要区分一下
{
    //1.开启ADC时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6); //PCLK2就是APB2时钟（72MHz），72MHz/6=12MHz (ADC时钟不能超过14MHz)
    //2.配置GPIO
    BSP_GPIO_InitPin(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3, GPIO_Mode_AIN, GPIO_Speed_50MHz); //注意要配置为模拟输入AIN模式
    //3.配置多路开关，需要加通道就继续加配置函数就行
    //ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); //ADC1的第0通道，序列选择1（序列1上面写入CH0通道），采样时间为55.5周期（采样周期越短，转换越快，越长，转换越稳定）
    //4.配置ADC
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //单次转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//触发源：使用软件触发
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据对齐：右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1; //扫描模式下，选用多少个通道
    ADC_Init(ADC1, &ADC_InitStructure);
    //5.开启ADC
    ADC_Cmd(ADC1, ENABLE);
    //6.校准ADC
    ADC_ResetCalibration(ADC1); //复位校准寄存器
    while(ADC_GetResetCalibrationStatus(ADC1)); //等待复位校准完成
    ADC_StartCalibration(ADC1); //开始校准
    while(ADC_GetCalibrationStatus(ADC1)); //等待校准完成
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
    ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);//每次读取之前都指定一次通道
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); //软件触发，开始转换
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)); //等待转换完成(EOC=1时退出循环)
    return ADC_GetConversionValue(ADC1); //返回数据寄存器结果
}