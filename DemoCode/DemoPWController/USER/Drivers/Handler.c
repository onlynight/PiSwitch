#include "Handler.h"

static float led_pwm = 0;
static int dir = 1;

void DMA1_Channel1_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA1_IT_TC1) != RESET)
    {
        //自己的中断处理代码 但是记住程序不要太复杂  最好不要超过中断时间
        UART_SendInt16(USART1, get_ChannelValue(ADC_Channel_0));
        UART_SendInt16(USART1, get_ChannelValue(ADC_Channel_1));
        DMA_ClearITPendingBit(DMA1_IT_TC1);
    }
}

void EXTI15_10_IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        LED_OFF;
        TIM_ITConfig(TIM4, TIM_IT_CC1, DISABLE);
        setSpeed(1);
        EXTI_ClearFlag(EXTI_Line10);         //清除中断标志
        EXTI_ClearITPendingBit(EXTI_Line10); //清除EXTI线路挂起位
    }

    if (EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
        LED_ON;
        TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
        setSpeed(100);
        EXTI_ClearFlag(EXTI_Line11);         //清除中断标志
        EXTI_ClearITPendingBit(EXTI_Line11); //清除EXTI线路挂起位
    }

    if (EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        LED_OFF;
        TIM_SetCompare3(TIM4, 0);
        TIM_SetCompare1(TIM3, 0);

        Delay(1000);
        Device_Enter_Stop_Mode();
        EXTI_ClearFlag(EXTI_Line12);
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
}

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

void USART2_IRQHandler()
{
    uint8_t ch;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        ch = USART_ReceiveData(USART2);
    }
}

void USART1_IRQHandler()
{
    uint8_t ch;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        ch = USART_ReceiveData(USART1);
    }
}
