#include "Delay.h"

void Delay(u32 d_time)
{
	for (; d_time > 0; d_time--)
		;
}
