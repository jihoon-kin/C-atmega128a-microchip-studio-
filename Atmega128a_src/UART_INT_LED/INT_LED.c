/*
 * INT_LED.c
 *
 * Created: 2024-04-09 오후 2:20:38
 *  Author: user
 */ 
#include "UART_INT_LED.h"

void ledInit(LED *led)
{
	*(led->port - 1) |= (1<<led->pin);
}

void ledOn(LED *led)
{
	// 해당핀을 high 설정
	*(led->port) |= (1 << led->pin);
}

void ledOff(LED *led)
{
	// 해당 핀을 Low 로 설정
	*(led->port) &= ~(1 << led->pin);
}