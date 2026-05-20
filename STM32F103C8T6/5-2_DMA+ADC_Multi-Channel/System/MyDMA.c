#include "stm32f10x.h"

uint16_t MyDMA_Size;

/**
 * @brief DMA初始化函数
 * 
 * @param AddrA 外设起始地址
 * @param AddrB 存储器起始地址
 * @param Size 缓存区大小，单位为数据单元个数
 */
void MyDMA_Init(uint32_t AddrA,uint32_t AddrB,uint32_t Size)
{
  //1.时钟使能
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  //2.用结构体进行参数配置
  DMA_InitTypeDef DMA_InitStructure;
  DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA; //外设：起始地址
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设：数据宽度(字节)
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable; // 外设：地址是否自增
  DMA_InitStructure.DMA_MemoryBaseAddr = AddrB; // 存储器：起始地址
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // 存储器：数据宽度
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // 存储器：地址是否自增
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // 方向：外设到存储器
  MyDMA_Size = Size; //全局变量保存数据单元个数，后续转运完成后会用到(这个不属于结构体)
  DMA_InitStructure.DMA_BufferSize = Size; // 缓存区大小：数据单元个数
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; //是否使用自动重装：不使用
  DMA_InitStructure.DMA_Priority = DMA_Priority_High; //高优先级(当多个通道同时请求时，优先级高的先被服务)
  DMA_InitStructure.DMA_M2M = DMA_M2M_Enable; // 选择软件触发or硬件触发：软件触发
  
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  //3.开关控制
  DMA_Cmd(DMA1_Channel1, DISABLE);//不让DMA立刻工作，调用Transfer函数再转运
}

void MyDMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);//先关掉DMA，才能修改寄存器
    DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size); //重新设置数据单元个数
    DMA_Cmd(DMA1_Channel1, ENABLE); //重新打开DMA，DMA立刻工作
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); //等待转运完成
}