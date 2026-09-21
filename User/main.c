#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h" 
#include "Car.h"
int main(void)
{
    Car_Init();
    while (1)
    {
        Car_Go_Backward(50);
        Delay_ms(1000);
        Car_Stop();
        Delay_ms(1000);
    }
}
