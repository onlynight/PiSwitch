#include "Moter.h"

static void GPIO_Config(void);
void TIM_PWM_Config(uint16_t fill, uint16_t total);

/**
 * speed 0-100
 *
 */
void setSpeed(int speed)
{
    if (speed >= 100)
    {
        speed = 100;
    }

    if (speed <= -100)
    {
        speed = -100;
    }

    int speed_range = TIM3_MAX_VALUE - TIM3_MIN_VALUE;
    float speed_ratio = speed_range / (float)MAX_SPEED;
    current_speed = speed;
    TIM_SetCompare1(TIM3, TIM3_MIN_VALUE + speed * speed_ratio);
}

void Moter_Config(void)
{
    GPIO_Config();
    TIM_PWM_Config(TIM3_MAX_VALUE/2, TIM3_MAX_VALUE);
}

static void GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TIM_PWM_Config(uint16_t fill, uint16_t total)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_BaseInitStructure.TIM_Period = total;
    TIM_BaseInitStructure.TIM_Prescaler = 1;
    TIM_BaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_BaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_Pulse = fill;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}
