#include "EXTI.h"

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
        Stop_Controller();
        EXTI_ClearFlag(EXTI_Line12);
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
}

void Init_EXTI(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);

    EXTI_InitStructure.EXTI_Line = EXTI_Line10;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);

    EXTI_InitStructure.EXTI_Line = EXTI_Line11;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);

    EXTI_InitStructure.EXTI_Line = EXTI_Line12;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
}
