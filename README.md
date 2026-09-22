# STM32 循迹小车

基于 STM32F103 的智能循迹小车项目，完全开源。

## 项目简介

这是一个使用 STM32F103 系列 MCU 开发的循迹小车项目，采用 Keil MDK 开发环境，使用 STM32 标准外设库。项目实现了四轮驱动小车的运动控制，支持前进、后退、左转、右转和停止等基本功能。

## 硬件模块

| 模块 | 文件 | 说明 |
|------|------|------|
| Car | `Hardware/Car.c/.h` | 小车运动控制（前进、后退、转向） |
| Motor | `Hardware/motor.c/.h` | 电机驱动（正转、反转、调速） |
| PWM | `Hardware/PWM.c/.h` | PWM 电机控制 |
| LED | `Hardware/LED.c/.h` | LED 指示灯驱动 |
| Key | `Hardware/Key.c/.h` | 按键输入检测 |
| OLED | `Hardware/OLED.c/.h` | OLED 显示屏驱动 |

## 软件架构

```
├── Start/          # 启动文件与 CMSIS 核心
├── Library/        # STM32F10x 标准外设库
├── System/         # 系统级驱动（延时等）
├── Hardware/       # 硬件模块驱动
├── User/           # 用户应用代码（main.c）
└── .eide/          # EIDE 工程配置
```

## 引脚分配

### 电机控制引脚

| 功能 | GPIO引脚 | 说明 |
|------|----------|------|
| 左电机 AIN1 | PA4 | 左电机正转控制 |
| 左电机 AIN2 | PA5 | 左电机反转控制 |
| 右电机 BIN1 | PA6 | 右电机正转控制 |
| 右电机 BIN2 | PA7 | 右电机反转控制 |

### PWM输出引脚

| 功能 | GPIO引脚 | 定时器通道 |
|------|----------|------------|
| 左电机PWM | PA0 | TIM2_CH1 |
| 右电机PWM | PA1 | TIM2_CH2 |

### 其他外设引脚

| 功能 | GPIO引脚 | 说明 |
|------|----------|------|
| LED1 | PA3 | 指示灯1 |
| LED2 | PA2 | 指示灯2 |
| 按键1 | PB1 | 按键输入1 |
| 按键2 | PB11 | 按键输入2 |

## 运动控制API

```c
#include "Car.h"

// 初始化小车
Car_Init();

// 前进（速度固定为70，改 Hardware/Car.c 里的 CAR_SPEED 可调整）
Car_Go_Forward();

// 后退
Car_Go_Backward();

// 左转
Car_Turn_Left();

// 右转
Car_Turn_Right();

// 停止
Car_Stop();
```

## 开发环境

- **MCU**: STM32F103 系列
- **IDE**: Keil MDK / VS Code (EIDE)
- **库**: STM32F10x 标准外设库

## 使用方法

1. 克隆本仓库
2. 使用 Keil MDK 或 EIDE 打开工程文件
3. 编译并烧录到 STM32 开发板

## 版本

- **v2.0** - 新增四电机驱动功能，支持小车运动控制
- **v1.0** - 基础框架搭建，OLED 显示功能

## 开源协议

本项目完全开源，欢迎学习交流。

## 作者

Langlijun
