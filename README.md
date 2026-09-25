# STM32 智能小车

基于 STM32F103C8T6 的蓝牙智能小车项目，使用 Keil MDK / VS Code EIDE 开发，基于 STM32F10x 标准外设库。

## 项目简介

本项目实现了一个可通过 HC-06 蓝牙串口遥控的智能小车，主要功能包括：

- 四轮小车前进、后退、左转、右转、停止
- 左右电机独立 PWM 调速
- 四路红外循迹检测，并通过四个 LED 显示检测状态
- SG90 舵机角度控制
- HC-SR04 超声波测距
- OLED 等基础外设驱动
- 通过 USART1 中断自动接收蓝牙指令，不需要在主循环中反复判断

## 硬件模块

| 模块 | 文件 | 功能 |
|------|------|------|
| Car | `Hardware/Car.c/.h` | 小车运动控制 |
| Motor | `Hardware/motor.c/.h` | 左右电机方向和速度控制 |
| PWM | `Hardware/PWM.c/.h` | 电机 PWM 和舵机 PWM |
| Serial | `Hardware/Serial.c/.h` | USART1 蓝牙通信 |
| Ir_obstacle | `Hardware/Ir_obstacle.c/.h` | 四路红外循迹检测和状态灯显示 |
| Servo | `Hardware/Servo.c/.h` | SG90 舵机控制 |
| Ultrasound | `Hardware/Ultrasound.c/.h` | HC-SR04 超声波测距 |
| OLED | `Hardware/OLED.c/.h` | OLED 显示驱动 |
| MyDelay | `System/MyDelay.c/.h` | TIM4 计时，用于超声波测距 |

## 软件架构

```text
├── Start/          # 启动文件、CMSIS 和系统文件
├── Library/        # STM32F10x 标准外设库
├── System/         # 延时和系统计时
├── Hardware/       # 硬件模块驱动
├── User/           # 主程序
├── Project.uvprojx # Keil MDK 工程
└── .eide/          # VS Code EIDE 工程配置
```

## 引脚分配

### 电机控制

小车使用 TB6612 电机驱动模块。左右两侧电机分别由两路 PWM 控制，四轮小车可以将同侧电机并联使用。

| 功能 | GPIO | 定时器通道 | 说明 |
|------|------|------------|------|
| 左电机 PWM | PA0 | TIM2_CH1 | 左电机调速 |
| 右电机 PWM | PA1 | TIM2_CH2 | 右电机调速 |
| 左电机 AIN1 | PA4 | GPIO | 左电机方向 |
| 左电机 AIN2 | PA5 | GPIO | 左电机方向 |
| 右电机 BIN1 | PA6 | GPIO | 右电机方向 |
| 右电机 BIN2 | PA7 | GPIO | 右电机方向 |

TB6612 的 `STBY` 引脚需要接高电平，否则电机驱动不会工作。

### 蓝牙模块

| 功能 | GPIO | 说明 |
|------|------|------|
| USART1 TX | PA9 | 接 HC-06 RX |
| USART1 RX | PA10 | 接 HC-06 TX |

USART1 配置为 `9600 8N1`，即波特率 9600、8 个数据位、无校验、1 个停止位。HC-06 的 TX/RX 需要与 STM32 交叉连接。

### 舵机

| 功能 | GPIO | 定时器通道 | 说明 |
|------|------|------------|------|
| SG90 信号线 | PB0 | TIM3_CH3 | 舵机 PWM 信号 |

SG90 舵机建议使用独立 5V 电源供电，并与 STM32 共地。

### 超声波模块

| 功能 | GPIO | 说明 |
|------|------|------|
| HC-SR04 TRIG | PB5 | 触发信号 |
| HC-SR04 ECHO | PB6 | 回波信号，使用 EXTI6 中断测量 |

### 红外循迹模块

每个红外循迹模块使用一路数字输出信号，并对应一个状态指示灯。

| 模块 | 传感器信号 | GPIO 模式 | 状态灯 | LED GPIO |
|------|------------|------------|--------|----------|
| 红外 1 | DO | 输入 | 灯 1 | PB14 |
| 红外 2 | DO | 输入 | 灯 2 | PB15 |
| 红外 3 | DO | 输入 | 灯 3 | PA8 |
| 红外 4 | DO | 输入 | 灯 4 | PA11 |

对应关系：

```text
PB7  红外1 -> PB14 灯1
PB10 红外2 -> PB15 灯2
PB12 红外3 -> PA8  灯3
PB13 红外4 -> PA11 灯4
```

当前代码按照“传感器输出低电平表示检测到黑色”的逻辑点亮对应 LED。不同红外模块的输出极性可能相反，需要根据实际模块调整。

### 其他外设

| 功能 | GPIO | 说明 |
|------|------|------|
| SWD | PA13/PA14 | 调试和烧录接口 |

## 蓝牙控制指令

蓝牙收到字符后，由 `USART1_IRQHandler` 自动处理，主函数中不需要手动调用控制函数。

| 指令 | 功能 |
|------|------|
| `F` / `1` | 前进 |
| `B` / `2` | 后退 |
| `L` / `3` | 左转 |
| `R` / `4` | 右转 |
| `5` | 舵机转到 0° |
| `6` | 舵机转到 90° |
| `7` | 舵机转到 180° |
| `S` | 停车并切换到手动模式 |
| `A` / `0` | 恢复自动避障模式 |
| 其他字符 | 停车并切换到手动模式 |

小写字母 `f`、`b`、`l`、`r` 会自动按大写字母处理。
自动模式下，主程序会调用 `Auto_Run()` 进行超声波避障；发送 `F`、`B`、`L`、`R`、`S` 等指令后会切换到手动模式，发送 `A` 或 `0` 可恢复自动模式。

## 运动控制 API

```c
#include "Car.h"

Car_Init();           // 初始化电机
Car_Go_Forward();     // 前进
Car_Go_Backward();    // 后退
Car_Turn_Left();      // 左转
Car_Turn_Right();     // 右转
Car_Stop();           // 停止
```

整车速度在 `Hardware/Car.c` 中定义：

```c
#define CAR_SPEED 70
```

修改 `CAR_SPEED` 可以调整整车速度。

## 红外循迹 API

```c
#include "Ir_obstacle.h"

Ir_obstacle_Init();   // 初始化四个传感器和四个状态灯
Ir_obstacle_Run();    // 读取传感器并刷新状态灯
```

为了实时显示传感器状态，需要在主循环中持续调用 `Ir_obstacle_Run()`：

```c
while (1)
{
    Ir_obstacle_Run();
}
```

## 舵机 API

```c
#include "Servo.h"

Servo_Init();
SetServoAngle(0);     // 0°
SetServoAngle(90);    // 90°
SetServoAngle(180);   // 180°
```

角度范围为 `0~180`，超出范围不会设置输出。

## 超声波 API

```c
#include "Ultrasound.h"

Ultrasound_Init();
uint32_t distance = Ultrasound_GetDistance();
```

`Ultrasound_GetDistance()` 返回单位为厘米的距离值。当前实现会连续测量 10 次并取平均值，因此一次测量大约需要 0.6 秒。

## 开发环境

- **MCU**：STM32F103C8T6
- **电机驱动**：TB6612
- **蓝牙模块**：HC-06
- **红外循迹模块**：4 路数字输出红外传感器
- **舵机**：SG90
- **超声波模块**：HC-SR04
- **开发工具**：Keil MDK、VS Code EIDE
- **固件库**：STM32F10x 标准外设库

## 使用方法

1. 克隆仓库：

```bash
git clone https://github.com/Langlijun666/smallcar.git
```

2. 使用 Keil 打开 `Project.uvprojx`，或者使用 VS Code EIDE 打开工程。

3. 编译工程并烧录到 STM32F103C8T6。

4. 按照引脚分配连接 TB6612、HC-06、SG90、HC-SR04 和四路红外循迹模块。

5. 使用蓝牙串口工具连接 HC-06，发送 `F`、`B`、`L`、`R` 等指令控制小车。

## 版本记录

- **v3.2**：移除未使用 KEY/LED 模块，修正 TIM4 和 `Car_Turn_back()`，增加自动/手动模式
- **v3.1**：新增四路红外循迹检测和状态灯显示
- **v3.0**：新增 HC-06 蓝牙中断遥控、SG90 舵机控制、HC-SR04 超声波测距
- **v2.0**：新增 TB6612 四轮电机驱动和运动控制
- **v1.0**：基础框架、OLED、LED、按键和 PWM 功能

## v3.2 更新说明

- 移除未使用的 KEY/LED 模块及其工程配置。
- `Car_Turn_back()` 当前按右转方向执行，具体旋转角度由调用处的延时控制。
- TIM4 时基参数明确设置为 `TIM_ClockDivision = TIM_CKD_DIV1`。
- 增加自动/手动模式切换，蓝牙指令不会被自动避障逻辑覆盖。
- 补齐源码文件末尾换行，清理工程文件中的已删除模块引用。

## 开源说明

本项目用于学习和交流，欢迎提出问题和改进建议。

## 作者

Langlijun
