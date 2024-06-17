/*
 * UART_to_LCD.c
 *
 * Created: 2024-04-12 오후 2:22:36
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "I2C.h"
#include "UART.h"
#include "LCD.h"

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