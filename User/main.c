#include"main_conf.h"
void Auto_Run(void);

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
        //先检测是不是自动模式
        if(CarMode == CAR_MODE_AUTO)
        {
            Auto_Run();
        }
    }
}

void Auto_Run(void)
{
    Car_Stop();
    //先判断能不能前进
    uint32_t a = Ultrasound_GetDistance();
    char *buf = "\nFront distance:";
    Serial_SendString(buf);
    Serial_SendNumber(a,3);
    //不能前进
    if(a < 15)
    {
        //判断右边能不能走
        Car_Stop();
        SetServoAngle(SERVO_RIGHT);
        Delay_ms(1000);
        uint32_t b = Ultrasound_GetDistance();
        char *buf = "\nRight distance:";
        Serial_SendString(buf);
        Serial_SendNumber(b,3);
        if(b > 15)//右边能走
        {
            //转向到右边
            SetServoAngle(SERVO_FRONT);
            Delay_ms(1000);
            Car_Turn_Right();
            Delay_ms(1000);
            Car_Stop();
        }
        else//右边不能走
        {
            //判断左边能不能走
            SetServoAngle(SERVO_LEFT);
            Delay_ms(1000);
            uint32_t c = Ultrasound_GetDistance();
            char *buf = "\nLeft distance:";
            Serial_SendString(buf);
            Serial_SendNumber(c,3);
            if(c > 15)//左边能走
            {
                //转向左边
                SetServoAngle(SERVO_FRONT);
                Delay_ms(1000);
                Car_Turn_Left();
                Delay_ms(1000);
                Car_Stop();
//              Car_Go_Forward();
            }
            else//左边不能走
            {
                //转向后边，判断后边能不能走
                SetServoAngle(SERVO_FRONT);
                Delay_ms(1000);
                Car_Turn_back();
                Delay_ms(2000);
                Car_Stop();
                uint32_t d = Ultrasound_GetDistance();
                char *buf = "\nBack distance:";
                Serial_SendString(buf);
                Serial_SendNumber(d,3);
                if(d > 15)//后边能走
                {
                    return;
                }
                else//后边不能走，停止，等候指令
                {
                    Car_Stop();
                    CarMode = CAR_MODE_MANUAL;
                    return;
                }
            }
        }
    //能前进就直接走
    }
    else Car_Go_Forward();
}
