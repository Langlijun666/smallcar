
#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Serial.h"

int main(void)
{
    Car_Init();
    Serial_Init();
    while(1)
    {
        
    }
}