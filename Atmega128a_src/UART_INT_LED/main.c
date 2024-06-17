/*
 * UART_INT_LED.c
 *
 * Created: 2024-04-09 오후 2:17:48
 * Author : user
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "UART_INT_LED.h"
#include <string.h>


int main(void)
{
	LED leds[8]=
	{
		{&PORTD, 0},
		{&PORTD, 1},
		{&PORTD, 2},
		{&PORTD, 3},
		{&PORTD, 4},
		{&PORTD, 5},
		{&PORTD, 6},
		{&PORTD, 7}
	};
	
	for(uint8_t i = 0; i < 8; i++)
	{
		ledInit(&leds[i]);
	}
	
	UART0_Init();
	
	uint8_t data[4];
	data[0] = 'N';
	data[1] = 'F';
	data[2] = 'R';
	data[3] = 'L';
	
	while (1)
	{
		data = UART0_Receive();
		UART0_Transmit(data);
		switch (data)
		{
			case ('N'):
			for (uint8_t i = 0; i < 8 ; i++)
			{
				ledOn(&leds[i]);
			}
			break;
			case ('F'):
			for (uint8_t i = 0; i < 8 ; i++)
			{
				ledOff(&leds[i]);
			}
			break;
			case ('R'):
			for (uint8_t i = 0; i < 8 ; i++)
			{
				ledOn(&leds[i]);
				_delay_ms(100);
				ledOff(&leds[i]);
				_delay_ms(100);
			}
			break;
			case ('L'):
			for (uint8_t i = 7; i < 8 ; i--)
			{
				ledOn(&leds[i]);
				_delay_ms(100);
				ledOff(&leds[i]);
				_delay_ms(100);
			}
			break;
		}
		
	}
}