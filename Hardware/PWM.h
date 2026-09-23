#ifndef __PWM_H
#define __PWM_H

#include <stdint.h>

void PWM_Init(void);
void PWM_SetCompare1(int8_t Compare);
void PWM_SetCompare2(int8_t Compare);
void PWM_Init2(void);
void PWM2_SetCompare3(int16_t Compare);
#endif
