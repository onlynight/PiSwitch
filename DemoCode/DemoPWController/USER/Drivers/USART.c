#include "USART.h"

void int_char(uint16_t i, unsigned char *s);

void UART_PutChar(USART_TypeDef *USARTx, uint8_t Data)
{
    USART_SendData(USARTx, Data);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
        ;
}

void UART_PutStr(USART_TypeDef *USARTx, uint8_t *str)
{
    while (0 != *str)
    {
        UART_PutChar(USARTx, *str);
        str++;
    }
}

void UART_SendInt16(USART_TypeDef *USARTx, uint16_t value)
{
    int i = 0;
    unsigned char c[2];
    int_char(value, c);
    for (i = 0; i < 2; i++)
    {
        USART_SendData(USARTx, c[i]);
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
            ;
    }
}

void int_char(uint16_t i, unsigned char *s)
{
    *s = i >> 8;
    *(s + 1) = i;
}
