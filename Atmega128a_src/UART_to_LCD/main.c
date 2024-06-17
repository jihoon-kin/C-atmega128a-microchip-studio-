#include "I2C_LCD.h"
#include "uart0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(USART0_Transmit, NULL, _FDEV_SETUP_WRITE);

ISR(USART0_RX_vect)
{
	USART0_ISR_Process();
}

int main(void)
{
	UART0_init();
	stdout = &OUTPUT;
	LCD_Init();
	while (1)
	{
		UART0_execute();
		//LCD_WriteCommand(COMMAND_DISPLAY_CLEAR);
		uint8_t *data = UART0_readRxBuff();
		LCD_WriteStringXY(0,0,data);
	}
}

