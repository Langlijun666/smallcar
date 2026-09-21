#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdint.h>

void Motor_Init(void);
void Motor_Set_Left_Speed(int8_t speed);
void Motor_Set_Right_Speed(int8_t speed);

#endif
