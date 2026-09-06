# STM32 循迹小车

基于 STM32F103 的智能循迹小车项目，完全开源。

## 项目简介

这是一个使用 STM32F103 系列 MCU 开发的循迹小车项目，采用 Keil MDK 开发环境，使用 STM32 标准外设库。

## 硬件模块

| 模块 | 文件 | 说明 |
|------|------|------|
| LED | `Hardware/LED.c/.h` | LED 指示灯驱动 |
| Key | `Hardware/Key.c/.h` | 按键输入检测 |
| OLED | `Hardware/OLED.c/.h` | OLED 显示屏驱动 |
| PWM | `Hardware/PWM.c/.h` | PWM 电机控制 |

## 软件架构

```
├── Start/          # 启动文件与 CMSIS 核心
├── Library/        # STM32F10x 标准外设库
├── System/         # 系统级驱动（延时等）
├── Hardware/       # 硬件模块驱动
├── User/           # 用户应用代码（main.c）
└── .eide/          # EIDE 工程配置
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

- **v1.0** - 基础框架搭建，OLED 显示功能

## 开源协议

本项目完全开源，欢迎学习交流。

## 作者

Langlijun
