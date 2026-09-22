
#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Serial.h"

int main(void)
{
    Car_Init();
    Serial_Init();
    Car_RemoteControl();//自动接收手机指令并按规则移动

    while(1)
    {
        
    }
}