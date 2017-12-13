#ifndef __MOTER_H
#define __MOTER_H

#include "main.h"

// max moter speed
#define MAX_SPEED 100
// min moter speed
#define MIN_SPEED 0

#define TIM3_MAX_VALUE 1000
#define TIM3_MIN_VALUE 250

static int current_speed = 0;

extern void setSpeed(int speed);
extern void Moter_Config(void);

#endif
