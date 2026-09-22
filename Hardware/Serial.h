#ifndef __SERIAL_H
#define __SERIAL_H

void Serial_Init(void);
void Serial_SendBytes(USART_TypeDef * A, int16_t* Data1,int16_t length);
void Serial_ReceiveByte(USART_TypeDef *A,int16_t *Data1);
#endif // __SERIAL_H