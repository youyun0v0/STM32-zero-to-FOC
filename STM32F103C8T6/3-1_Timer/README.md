# STM32-zero-to-FOC
My personal journey of building high-performance motion control algorithms from scratch.

# 🚀 Advanced Motion Control Lab (从零到 FOC 控制实战)

## 📌 项目初衷
本项目是本人为了深入理解电机控制底层的物理逻辑，并最终实现高性能无刷电机 FOC 矢量控制的记录仓库。
用实践检验物理世界的可行性。

## 🎯 路线里程碑 (Milestones)
- **2026.4.25** 配置了vscode+EIDE工作环境，告别陈旧的keil5，建立工程模版方便一键复制
- **2026.4.26** 完成了流水灯制作，解锁成就“点灯新手”

## 🛠️ 硬件与工具链
- **主控芯片:** STM32F103C8T6 (后续将升级至 STM32G431)
- **开发环境:** Keil uVision 5 / VSCode EIDE
- **库类型:** STM32 Standard Peripheral Library (后续平滑过渡至 HAL 库)

## 📝 踩坑记录 (Troubleshooting)
- **2026.04.26:** 在点亮 8 位流水灯时，发现灯集体出现忽明忽暗的现象。经排查，定位为一个led灯接触不良导致整体忽明忽暗。认识到了单个引脚对整体的影响。
