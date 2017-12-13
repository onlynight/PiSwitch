#include "main.h"

int main(int argc, char const *argv[])
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	TIM_Config();
	Moter_Config();
	LED_Config();
	Joystick_Config();
	BT04_A_Config();
	TTL_USB_Config();
	Keys_Config();
	PWR_Config();
	Init_NVIC();

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
