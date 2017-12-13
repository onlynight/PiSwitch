#ifndef __USART_H
#define __USART_H

#include "main.h"

extern void UART_SendStr(USART_TypeDef *USARTx, uint8_t *str);
extern void UART_SendInt(USART_TypeDef *USARTx, int value);

#endif
