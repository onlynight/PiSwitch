#include "TIM.h"

static float led_pwm = 0;
static int dir = 1;

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
    {
        if (dir)
            led_pwm += 300.0f;
        else
            led_pwm -= 300.0f;

        if (led_pwm >= 60000)
        {
            dir = 0;
            // LED_OFF;
        }
        if (led_pwm <= 0)
        {
            dir = 1;
            // LED_ON;
        }

        // TIM4->CCR3 = (int)led_pwm;
        TIM_SetCompare3(TIM4, led_pwm);
        TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
    }
}

void Init_TIM(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    // Time base configuration
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Period = 60000 - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = 3 - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x00;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //配置为PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 500;                      //设置跳变值，当计数器计数到这个值时，电平发生跳变
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //当定时器计数值小于CCR1时为高电平
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);                  //使能通道1

    // adc采样外部触发tim4只能用通道4 ADC_ExternalTrigConv_T4_CC4
    // Time Channel 4 pwm config
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 500;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM4, ENABLE);

    TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}
