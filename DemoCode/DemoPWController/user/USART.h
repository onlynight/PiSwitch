#ifndef __USART_H
#define __USART_H

#include "SYS.h"

void Init_USART2(void);
void Init_USART1(void);
void UART_PutStr(USART_TypeDef *USARTx, uint8_t *str);
void UART_SendInt16(USART_TypeDef *USARTx, uint16_t value);

#endif
