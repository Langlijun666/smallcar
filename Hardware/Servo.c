#include "stm32f10x.h"
#include "Servo.h"
#include "PWM.h"
//舵机模块初始化
void Servo_Init(void)
{
    PWM_Init2();
}
//设置舵机模块转动角度
void SetServoAngle(float angle)
{   
    if(angle <= 180.0 && angle >= 0.0)
    PWM2_SetCompare3(angle / 180 * 2000 + 500);
}
