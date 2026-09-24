
#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Serial.h"
#include "Servo.h"
#include "Ultrasound.h"
#include"Ir_obstacle.h"
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//分配好两种中断优先级的位数占比
    Car_Init();//初始化小车运动模块
    Serial_Init();//初始化串口模块
    Servo_Init();//初始化舵机模块
    Ultrasound_Init();//初始化超声波测距模块
    Ir_obstacle_Init();//初始化红外检测模块
    while(1)
    {
        
    }
}