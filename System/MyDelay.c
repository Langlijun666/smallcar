#include"stm32f10x.h"
#include"MyDelay.h"
void MyDelay_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
    TIM_TimeBaseInitstruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitstruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitstruct.TIM_Period = 0xFFFF;
    TIM_TimeBaseInitstruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInitstruct.TIM_Prescaler = 71;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitstruct);
    TIM_Cmd(TIM4,ENABLE);
    TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
    TIM_ClearFlag(TIM4,TIM_FLAG_Update);
    TIM_SetCounter(TIM4, 0);
    TIM_Cmd(TIM4, DISABLE);
}

