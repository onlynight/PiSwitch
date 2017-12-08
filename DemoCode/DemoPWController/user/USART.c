#include "USART.h"

uint8_t start_O = 'O';
uint8_t start_o = 'o';

void int_char(uint16_t i, unsigned char *s);

void USART2_IRQHandler()
{
    uint8_t ch;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        ch = USART_ReceiveData(USART2);

        if (ch == start_O || ch == start_o)
        {
            LED_ON;
        }
    }
}

void USART1_IRQHandler()
{
    uint8_t ch;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        ch = USART_ReceiveData(USART1);

        if (ch == start_O || ch == start_o)
        {
        }
    }
}

void Init_USART2(void)
{
    USART_InitTypeDef USART_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);
}

void Init_USART1()
{
    USART_InitTypeDef usart;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    usart.USART_BaudRate = 115200;
    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
    usart.USART_Parity = USART_Parity_No;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &usart);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

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
        USART_SendData(USARTx, c[i]); //这个是无法输出的
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
            ;
    }
}

void int_char(uint16_t i, unsigned char *s)
{
    *s = i >> 8;
    *(s + 1) = i;
}
