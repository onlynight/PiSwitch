#ifndef __LED_H
#define __LED_H

#include "main.h"

#define LED_DISABLE false
#define LED_ENABLE true

extern void LED_Config(void);
extern void Set_LED_State(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, bool enable);

#define LED_ON Set_LED_State(GPIOC, GPIO_Pin_13, LED_ENABLE);
#define LED_OFF Set_LED_State(GPIOC, GPIO_Pin_13, LED_DISABLE);

#endif
