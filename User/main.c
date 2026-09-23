
#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Serial.h"
#include "Servo.h"
int main(void)
{
    Car_Init();
    Serial_Init();
    Servo_Init();
    while(1)
    {
        
    }
}