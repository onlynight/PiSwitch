#include "Moter.h"

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
