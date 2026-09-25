#ifndef __SERIAL_H
#define __SERIAL_H
#define CAR_MODE_AUTO   1
#define CAR_MODE_MANUAL 0
#define CAR_MODE_LINE   2
extern volatile uint8_t CarMode;

void Serial_Init(void);
void Serial_SendBytes(USART_TypeDef * A, int8_t* Data1,int16_t length);
void Serial_ReceiveByte(USART_TypeDef *A,int16_t *Data1);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendByte(uint8_t Byte);
void Serial_SendString(char *String);
#endif // __SERIAL_H
