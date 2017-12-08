#include "GPIO.h"

void GPIO_LED_Init(void);
void GPIO_Key_Init(void);
void GPIO_USART2_Init(void);
void GPIO_USART1_Init(void);
void GPIO_ADC_Init(void);

void initGPIO()
{
    GPIO_LED_Init();
    GPIO_Key_Init();
    GPIO_USART2_Init();
    GPIO_USART1_Init();
    GPIO_ADC_Init();

    // PWM GPIO init
    // GPIO_InitTypeDef GPIO_InitStructure;
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    // GPIO_Init(GPIOC, &GPIO_InitStructure);
    // GPIO_ResetBits(GPIOC, GPIO_Pin_13);
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

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIP_Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIP_Key_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_10);
    GPIO_SetBits(GPIOB, GPIO_Pin_11);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

    // GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_11;
    // GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    // GPIP_Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOB, &GPIP_Key_InitStructure);
    // GPIO_SetBits(GPIOB, GPIO_Pin_11);

    // GPIP_Key_InitStructure.GPIO_Pin = GPIO_Pin_12;
    // GPIP_Key_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    // GPIP_Key_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOB, &GPIP_Key_InitStructure);
    // GPIO_SetBits(GPIOB, GPIO_Pin_11);
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

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // GPIO_PinRemapConfig(GPIO_Remap_ADC1_ETRGINJ, ENABLE);
}
