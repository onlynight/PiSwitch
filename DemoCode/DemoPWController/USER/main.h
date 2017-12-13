#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x_conf.h"

#include "TIM.h"
#include "BT04-A.h"
#include "Delay.h"
#include "Device_PWR.h"
#include "Handler.h"
#include "Joystick.h"
#include "keys.h"
#include "LED.h"
#include "Moter.h"
#include "TTL_USB.h"
#include "USART.h"

#include "NVIC.h"

#define LED_ON GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define LED_OFF GPIO_ResetBits(GPIOC, GPIO_Pin_13)

#endif
