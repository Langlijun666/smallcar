#include"stm32f10x.h"
#include"MyDelay.h"
volatile uint32_t Currents;
void MyDelay_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
    TIM_TimeBaseInitstruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitstruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitstruct.TIM_Period = 999;
    TIM_TimeBaseInitstruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInitstruct.TIM_Prescaler = 71;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitstruct);
//  TIM_Cmd(TIM4,ENABLE);
    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

void TIM4_IRQHandler()
{
    if(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update) == SET)
    {
        TIM_ClearFlag(TIM4,TIM_FLAG_Update);
        Currents ++;
    }
}
