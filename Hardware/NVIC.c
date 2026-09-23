#include "stm32f10x.h"
#include "NVIC.h"
void MyNVIC_Init(void)
{
    //设置2：2优先级分组器
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //初始化NVIC 
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;//打开USART1的优先级通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//设置抢占优先级为0
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//设置子优先级为0
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//使能

    NVIC_Init(&NVIC_InitStruct);//初始化
}
