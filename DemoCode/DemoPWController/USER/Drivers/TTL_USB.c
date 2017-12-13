#include "TTL_USB.h"

static void GPIO_Config(void);
static void USART_Config(void);

void TTL_USB_Config(void)
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
    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIP_Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIP_Key_InitStructure);

    // RX
    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIP_Key_InitStructure);
}

static void USART_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef usart;

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
