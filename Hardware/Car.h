#ifndef __CAR_H
#define __CAR_H

#include <stdint.h>

void Car_Init(void);
void Car_Go_Forward(int8_t speed);
void Car_Go_Backward(int8_t speed);
void Car_Turn_Left(int8_t speed);
void Car_Turn_Right(int8_t speed);
void Car_Stop(void);

#endif
