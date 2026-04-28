#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

//OLED显示器设置

int main(void)
{
  OLED_Init(); //OLED初始化
  //OLED一共4行，每行16列
  OLED_ShowChar(1, 1, 'A'); //在OLED显示器上显示字符'A'，位置为(1, 1)
  OLED_ShowString(1, 3, "STM32F103C8T6"); //在OLED显示器上显示字符串"STM32F103C8T6"，位置为(1, 3)
//  OLED_ShowNum(2, 1, 12345, 5); //在OLED显示器上显示数字12345，位置为(2, 1)，宽度为5
//  OLED_ShowNum(2, 1, 12345, 6); //位置偏大：在前面补零，显示012345
  OLED_ShowNum(2, 1, 12345, 4); //位置偏小：显示2345，前面数字被截断
  OLED_ShowSignedNum(2, 7, -12345, 5); //在OLED显示器上显示有符号数字-12345，位置为(2, 7)，宽度为5
  OLED_ShowSignedNum(2, 14, 66, 2); //在OLED显示器上显示有符号数字66，位置为(2, 14)，宽度为2
  OLED_ShowHexNum(3, 1, 0x1A, 2); //在OLED显示器上显示十六进制数字0x1A，位置为(3, 1)，宽度为2
  OLED_ShowBinNum(3, 4, 0x1A, 8); //在OLED显示器上显示二进制数字00011010，位置为(3, 4)，宽度为8
//  OLED_Clear(); //清屏
  while (1)
  {
    
  }
}

