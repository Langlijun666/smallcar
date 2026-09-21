#include "stm32f10x.h" 
#include "motor.h"
#include "Car.h"
#include "Delay.h"

void Car_Init(void)
{
    Motor_Init();
}

// 修改：原来传入正speed，现在传入负speed
void Car_Go_Forward(int8_t speed)
{
    Motor_Set_Left_Speed(-speed);   // 修改：正speed改为负speed
    Motor_Set_Right_Speed(-speed);  // 修改：正speed改为负speed
}

// 修改：原来传入负speed，现在传入正speed
void Car_Go_Backward(int8_t speed)
{
    Motor_Set_Left_Speed(speed);    // 修改：负speed改为正speed
    Motor_Set_Right_Speed(speed);   // 修改：负speed改为正speed
}

// 修改：左轮前进，右轮后退
void Car_Turn_Right(int8_t speed)
{
    Motor_Set_Left_Speed(-speed);   // 修改：左轮前进
    Motor_Set_Right_Speed(speed);   // 修改：右轮后退
}

// 修改：左轮后退，右轮前进
void Car_Turn_Left(int8_t speed)
{
    Motor_Set_Left_Speed(speed);    // 修改：左轮后退
    Motor_Set_Right_Speed(-speed);  // 修改：右轮前进
}

void Car_Stop(void)
{
    Motor_Set_Left_Speed(0);
    Motor_Set_Right_Speed(0);
}
