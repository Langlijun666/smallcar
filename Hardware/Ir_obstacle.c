#include"main_conf.h"

void Ir_obstacle_Init(void)
{
    //初始化四个接收红外循迹模块信号的引脚
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
    //初始化四个反映红外循迹信号情况的LED灯GPIO口
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
}
void Ir_obstacle_Run(void)
{
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == RESET) GPIO_SetBits(GPIOB,GPIO_Pin_14);
    else GPIO_ResetBits(GPIOB,GPIO_Pin_14);
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10) == RESET) GPIO_SetBits(GPIOB,GPIO_Pin_15);
    else GPIO_ResetBits(GPIOB,GPIO_Pin_15);
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == RESET) GPIO_SetBits(GPIOA,GPIO_Pin_8);
    else GPIO_ResetBits(GPIOA,GPIO_Pin_8);
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) == RESET) GPIO_SetBits(GPIOA,GPIO_Pin_11);
    else GPIO_ResetBits(GPIOA,GPIO_Pin_11);
}
