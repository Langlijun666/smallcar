
#include "stm32f10x.h" 
#include "motor.h"
#include "Car.h"
#include "Delay.h"
#include "Serial.h"

#define CAR_SPEED 70    //速度固定为70，想改整车快慢只改这个数字

void Car_Init(void)
{
    Motor_Init();
}

// 修改：原来传入正speed，现在传入负speed
void Car_Go_Forward(void)
{
    Motor_Set_Left_Speed(-CAR_SPEED);   // 修改：正speed改为负speed
    Motor_Set_Right_Speed(-CAR_SPEED);  // 修改：正speed改为负speed
}

// 修改：原来传入负speed，现在传入正speed
void Car_Go_Backward(void)
{
    Motor_Set_Left_Speed(CAR_SPEED);    // 修改：负speed改为正speed
    Motor_Set_Right_Speed(CAR_SPEED);   // 修改：负speed改为正speed
}

// 修改：左轮前进，右轮后退
void Car_Turn_Right(void)
{
    Motor_Set_Left_Speed(-CAR_SPEED);   // 修改：左轮前进
    Motor_Set_Right_Speed(CAR_SPEED);   // 修改：右轮后退
}

// 修改：左轮后退，右轮前进
void Car_Turn_Left(void)
{
    Motor_Set_Left_Speed(CAR_SPEED);    // 修改：左轮后退
    Motor_Set_Right_Speed(-CAR_SPEED);  // 修改：右轮前进
}

void Car_Stop(void)
{
    Motor_Set_Left_Speed(0);
    Motor_Set_Right_Speed(0);
}

//蓝牙遥控：手机蓝牙串口发一个字符，小车按下面的规则自动行动
//F或1-前进  B或2-后退  L或3-左转  R或4-右转  其余字符-停止
void Car_RemoteControl(void)
{
    int16_t cmd;
    while (1)
    {   
        Serial_ReceiveByte(USART1, &cmd);//一直等，手机发来一个字符就继续
        if (cmd >= 'a' && cmd <= 'z')//小写字母自动当大写处理
        {
            cmd = cmd - 'a' + 'A';
        }
        switch (cmd)
        {
            case 'F': case '1': Car_Go_Forward();  break;
            case 'B': case '2': Car_Go_Backward(); break;
            case 'L': case '3': Car_Turn_Left();   break;
            case 'R': case '4': Car_Turn_Right();  break;
            default:            Car_Stop();        break;//S和不认识的字符都停车
        }
    }
}