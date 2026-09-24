
#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Serial.h"
#include "Servo.h"
#include "Ultrasound.h"
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Car_Init();
    Serial_Init();
    Servo_Init();
    Ultrasound_Init();
    while(1)
    {
        
    }
}