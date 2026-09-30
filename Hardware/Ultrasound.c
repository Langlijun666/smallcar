#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Ultrasound_Init(){
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//trig
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//echo
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM4);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 60000 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

}
float Ultrasound_GetDistance()
{
    uint16_t start;
    uint16_t rise;
    uint16_t fall;
    uint16_t pulse;

    TIM_SetCounter(TIM4, 0);
    TIM_Cmd(TIM4, ENABLE);  
	start = TIM_GetCounter(TIM4);
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	Delay_us(20);
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==RESET){
        if((uint16_t)(TIM_GetCounter(TIM4) - start) > 25000)
        {   
            TIM_Cmd(TIM4, DISABLE);
            return 400;
        }
	};
    rise = TIM_GetCounter(TIM4);
	TIM_Cmd(TIM4, ENABLE);
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)==SET){
        if((uint16_t)(TIM_GetCounter(TIM4) - rise) > 25000)
        {
            TIM_Cmd(TIM4, DISABLE);
            return 400;
        }
	};
    fall = TIM_GetCounter(TIM4);
    pulse = fall - rise;
	TIM_Cmd(TIM4, DISABLE);
	float distance=(pulse*1.0/10*0.34)/2;
	TIM4->CNT=0;
	Delay_ms(100);
	return distance;
}