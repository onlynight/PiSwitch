#include "SYS.h"

int main(int argc, char const *argv[])
{
	initGPIO();
	Init_NVIC();
	Init_USART2();
	Init_USART1();
	ADC1_ExternalTriger_T4_CC4_Init();
	Init_DMA();
	Init_ADC();

	Timer_Init();
	Init_EXTI();

	Init_PWR();

	LED_OFF;

	while (1)
	{
		// UART_SendInt16(USART2, 65535);
		// Delay(3000000);
		// UART_PutStr(USART2, "Hello Nexus5");
		// Delay(3000000);
		
		// UART_SendInt16(USART2, 65535);
		// Delay(3000000);
		// UART_PutStr(USART2, "Hello Nexus5");
		// Delay(3000000);

		UART_SendInt16(USART2, get_ChannelValue(ADC_Channel_0));
		Delay(3000000);
		UART_SendInt16(USART2, get_ChannelValue(ADC_Channel_1));
		Delay(3000000);
	}
}
