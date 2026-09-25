#include"main_conf.h"

#define CAR_SPEED 70    //速度固定为70，想改整车快慢只改这个数字

void Car_Init(void)
{
    Motor_Init();
}
//直行
void Car_Go_Forward(void)
{
    Motor_Set_Left_Speed(-CAR_SPEED);   // 修改：正speed改为负speed
    Motor_Set_Right_Speed(-CAR_SPEED);  // 修改：正speed改为负speed
}

//倒车
void Car_Go_Backward(void)
{
    Motor_Set_Left_Speed(CAR_SPEED);    // 修改：负speed改为正speed
    Motor_Set_Right_Speed(CAR_SPEED);   // 修改：负speed改为正speed
}

//原地右转
void Car_Self_Right(void)
{
    Motor_Set_Left_Speed(-CAR_SPEED);   // 修改：左轮前进
    Motor_Set_Right_Speed(CAR_SPEED);   // 修改：右轮后退
}

//原地左转
void Car_Self_Left(void)
{
    Motor_Set_Left_Speed(CAR_SPEED);    // 修改：左轮后退
    Motor_Set_Right_Speed(-CAR_SPEED);  // 修改：右轮前进
}
//原地调头
void Car_Self_back(void)
{
    Motor_Set_Left_Speed(-CAR_SPEED);   // 修改：左轮前进
    Motor_Set_Right_Speed(CAR_SPEED);   // 修改：右轮后退
}
//停车
void Car_Stop(void)
{
    Motor_Set_Left_Speed(0);
    Motor_Set_Right_Speed(0);
}
//右转
void Car_Turn_Right(void)
{
    Motor_Set_Left_Speed(-CAR_SPEED);   // 修改：左轮前进
    Motor_Set_Right_Speed(0);   // 修改：右轮不动
}

// 左转
void Car_Turn_Left(void)
{
    Motor_Set_Left_Speed(0);    // 修改：左轮不动
    Motor_Set_Right_Speed(-CAR_SPEED);  // 修改：右轮前进
}
