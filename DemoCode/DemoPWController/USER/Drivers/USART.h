#ifndef __USART_H
#define __USART_H

#include "main.h"

extern void UART_PutStr(USART_TypeDef *USARTx, uint8_t *str);
extern void UART_SendInt16(USART_TypeDef *USARTx, uint16_t value);

#endif
