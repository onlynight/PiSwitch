#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "main.h"

extern uint16_t get_ChannelValue(uint8_t ADC_Channel);
extern void Joystick_Config(void);

#define NUM_CHANNEL 2

static uint16_t ad_value[NUM_CHANNEL] = {0};

#endif
