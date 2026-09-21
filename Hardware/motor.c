#include "stm32f10x.h" 
#include "motor.h" 
#include "PWM.h"

void Motor_Init(void)
{
    //初始化PA4567,这四个GPIO口用来控制两个电机的正反转
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    PWM_Init();
}

//设置左电机的速度，如果速度大于0，则电机正转，如果速度小于0，则电机反转，如果速度等于0，则电机停止
void Motor_Set_Left_Speed(int8_t speed)
{
  if(speed > 0){
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    PWM_SetCompare1(speed);
  } else if(speed == 0){
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
    PWM_SetCompare1(0);
  } else {
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
    PWM_SetCompare1(-speed);
  }
}

//设置右电机的速度，如果速度大于0，则电机正转，如果速度小于0，则电机反转，如果速度等于0，则电机停止
//注意：右电机物理安装方向与左电机相反，所以正反转逻辑需要对调
void Motor_Set_Right_Speed(int8_t speed)
{
  if(speed > 0){
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);  // 修改：BIN1=低
    GPIO_SetBits(GPIOA, GPIO_Pin_7);    // 修改：BIN2=高
    PWM_SetCompare2(speed);
  } else if(speed == 0){
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);
    PWM_SetCompare2(0);
  } else {
    GPIO_SetBits(GPIOA, GPIO_Pin_6);    // 修改：BIN1=高
    GPIO_ResetBits(GPIOA, GPIO_Pin_7);  // 修改：BIN2=低
    PWM_SetCompare2(-speed);
  }
}
