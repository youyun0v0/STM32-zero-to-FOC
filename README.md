# STM32-zero-to-FOC
My personal journey of building high-performance motion control algorithms from scratch.

# 🚀 Advanced Motion Control Lab (从零到 FOC 控制实战)

## 📌 项目初衷
该项目是本人为了深入理解电机控制底层的物理逻辑，并最终实现高性能无刷电机 FOC 矢量控制的记录仓库。
用实践检验物理世界的可行性。

## 🎯 路线里程碑 (Milestones)
- **2026.4.25** 配置了vscode+EIDE工作环境，告别陈旧的keil5，建立工程模版方便一键复制。
- **2026.4.26** 完成了流水灯控制，蜂鸣器设置，按钮控制LED，光光敏电阻控制蜂鸣器模块，了解了部分器件的搭建方式，掌握了把功能封装入库的方法。

## 🛠️ 硬件与工具链
- **主控芯片:** STM32F103C8T6 (后续将升级至 STM32G431)
- **开发环境:** Keil uVision 5 / VSCode EIDE
- **库类型:** STM32 Standard Peripheral Library (后续平滑过渡至 HAL 库)

## 📝 排障记录 (Troubleshooting)
- **2026.04.25:** 在点亮 8 位流水灯时，发现灯集体出现忽明忽暗的现象。经排查，定位为一个led灯接触不良导致整体忽明忽暗。认识到了单个引脚对整体的影响。
- **2026.04.26:** 在按钮控制LED灯时出现了一个灯亮一个灯不亮的现象。AI建议我使用代码交换两个灯的控制程序，排查是灯的问题还是按钮的问题，大大简化了排查流程
