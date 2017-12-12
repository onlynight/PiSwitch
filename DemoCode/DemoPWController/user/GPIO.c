#include "GPIO.h"

void GPIO_LED_Init(void);
void GPIO_Key_Init(void);
void GPIO_USART2_Init(void);
void GPIO_USART1_Init(void);
void GPIO_ADC_Init(void);

void Init_GPIO()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_LED_Init();
    GPIO_Key_Init();
    GPIO_USART2_Init();
    GPIO_USART1_Init();
    GPIO_ADC_Init();
}

void GPIO_LED_Init()
{
    // LED GPIO init
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, GPIO_Pin_13);

    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // GPIO_Init(GPIOA, &GPIO_InitStructure);
    // GPIO_SetBits(GPIOA, GPIO_Pin_6);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

void GPIO_Key_Init()
{
    // key gpio init
    GPIO_InitTypeDef GPIP_Key_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);

    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIP_Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIP_Key_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_10);
    GPIO_SetBits(GPIOB, GPIO_Pin_11);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOB, &GPIP_Key_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void GPIO_USART2_Init()
{
    // usart gpio init
    GPIO_InitTypeDef GPIP_Key_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // TX
    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIP_Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIP_Key_InitStructure);

    // RX
    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIP_Key_InitStructure);

    // GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
}

void GPIO_USART1_Init()
{
    // usart gpio init
    GPIO_InitTypeDef GPIP_Key_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // TX
    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIP_Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIP_Key_InitStructure);

    // RX
    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIP_Key_InitStructure);

    // GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
}

void GPIO_ADC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGREG, ENABLE);
}

void RCC_Configuration(void)
{
    ErrorStatus HSEStartUpStatus;

    RCC_HSEConfig(RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS)
    {
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div2);
        RCC_PCLK2Config(RCC_HCLK_Div1);
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_4);
        RCC_PLLCmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
            ;
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08)
            ;
    }
}
