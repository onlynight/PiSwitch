#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x_conf.h"
#include "Delay.h"
#include "GPIO.h"
#include "TIM.h"
#include "NVIC.h"
#include "USART.h"
#include "ADC.h"
#include "DMA.h"
#include "EXTI.h"
#include "PWR.h"

#ifndef LED_OPERATE
#define LED_ON GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define LED_OFF GPIO_SetBits(GPIOC, GPIO_Pin_13)

#define LED1_ON GPIO_ResetBits(GPIOA, GPIO_Pin_6)
#define LED1_OFF GPIO_SetBits(GPIOA, GPIO_Pin_6)
#endif

#ifndef bool
#define bool int
#define false 0
#define true 1
#endif

#ifndef NUM_CHANNEL
#define NUM_CHANNEL 2
#endif

#ifndef AD_VALUE
static uint16_t ad_value[NUM_CHANNEL] = {0};
#endif

#endif
