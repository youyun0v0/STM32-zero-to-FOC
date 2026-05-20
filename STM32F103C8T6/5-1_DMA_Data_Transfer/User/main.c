#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"

uint8_t DataA[]={0x01, 0x02, 0x03, 0x04};
uint8_t DataB[8];

int main(void)
{
  MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, sizeof(DataA)); //DMA暂时不工作，调用Transfer函数再转运
  OLED_Init();
  OLED_ShowString(1, 1, "DataA:");
  OLED_ShowString(3, 1, "DataB:");
  OLED_ShowHexNum(1, 8, (uint32_t)DataA, 8); //显示DataA地址
  OLED_ShowHexNum(3, 8, (uint32_t)DataB, 8); //显示DataB地址

  OLED_ShowHexNum(2, 1, (uint32_t)DataA[0], 2); //显示DataA
  OLED_ShowHexNum(2, 4, (uint32_t)DataA[1], 2); 
  OLED_ShowHexNum(2, 7, (uint32_t)DataA[2], 2);
  OLED_ShowHexNum(2, 10, (uint32_t)DataA[3], 2);
  OLED_ShowHexNum(4, 1, (uint32_t)DataB[0], 2); //显示DataB
  OLED_ShowHexNum(4, 4, (uint32_t)DataB[1], 2);
  OLED_ShowHexNum(4, 7, (uint32_t)DataB[2], 2);
  OLED_ShowHexNum(4, 10, (uint32_t)DataB[3], 2);

  
  MyDMA_Transfer(); //DMA工作，DataA转运到DataB

  while (1)
  {
    DataA[0]++;
    DataA[1]++;
    DataA[2]++;
    DataA[3]++;
  OLED_ShowHexNum(2, 1, (uint32_t)DataA[0], 2); //显示DataA
  OLED_ShowHexNum(2, 4, (uint32_t)DataA[1], 2); 
  OLED_ShowHexNum(2, 7, (uint32_t)DataA[2], 2);
  OLED_ShowHexNum(2, 10, (uint32_t)DataA[3], 2);
  OLED_ShowHexNum(4, 1, (uint32_t)DataB[0], 2); //显示DataB
  OLED_ShowHexNum(4, 4, (uint32_t)DataB[1], 2);
  OLED_ShowHexNum(4, 7, (uint32_t)DataB[2], 2);
  OLED_ShowHexNum(4, 10, (uint32_t)DataB[3], 2);
  Delay_ms(1000);
    MyDMA_Transfer(); //DMA工作，DataA转运到DataB
  OLED_ShowHexNum(2, 1, (uint32_t)DataA[0], 2); //显示DataA
  OLED_ShowHexNum(2, 4, (uint32_t)DataA[1], 2); 
  OLED_ShowHexNum(2, 7, (uint32_t)DataA[2], 2);
  OLED_ShowHexNum(2, 10, (uint32_t)DataA[3], 2);
  OLED_ShowHexNum(4, 1, (uint32_t)DataB[0], 2); //显示DataB
  OLED_ShowHexNum(4, 4, (uint32_t)DataB[1], 2);
  OLED_ShowHexNum(4, 7, (uint32_t)DataB[2], 2);
  OLED_ShowHexNum(4, 10, (uint32_t)DataB[3], 2);
  Delay_ms(1000);
  }
}

