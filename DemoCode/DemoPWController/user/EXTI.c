#include "EXTI.h"

void EXTI15_10_IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line10))
    {
        LED_OFF;
        TIM_ITConfig(TIM2, TIM_IT_CC1, DISABLE);
        EXTI_ClearFlag(EXTI_Line10);         //清除中断标志
        EXTI_ClearITPendingBit(EXTI_Line10); //清除EXTI线路挂起位
    }

    if (EXTI_GetITStatus(EXTI_Line11))
    {
        LED_ON;
        EXTI_ClearFlag(EXTI_Line11); //清除中断标志
        TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
        EXTI_ClearITPendingBit(EXTI_Line11); //清除EXTI线路挂起位
    }

    if (EXTI_GetITStatus(EXTI_Line12))
    {
        Stop_Controller();
        EXTI_ClearITPendingBit(EXTI_Line12); //清除EXTI线路挂起位
    }
}

void Init_EXTI(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

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
