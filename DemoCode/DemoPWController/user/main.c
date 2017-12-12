#include "SYS.h"

int main(int argc, char const *argv[])
{
	Init_GPIO();
	Init_NVIC();
	Init_USART2();
	Init_USART1();
	Init_TIM();
	Init_DMA();
	Init_ADC();
	Init_EXTI();
	Init_PWR();
	RCC_Configuration();

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
