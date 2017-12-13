#include "BT04-A.h"

static void GPIO_Config(void);
static void USART_Config(void);

void BT04_A_Config(void)
{
    GPIO_Config();
    USART_Config();
}

static void GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // usart gpio init
    GPIO_InitTypeDef GPIP_Key_InitStructure;

    // TX
    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIP_Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIP_Key_InitStructure);

    // RX
    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIP_Key_InitStructure);
}

static void USART_Config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    USART_InitTypeDef USART_InitStructure;

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
