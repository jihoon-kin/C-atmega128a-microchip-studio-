/*
 * CFile1.c
 *
 * Created: 2024-04-09 오후 3:41:21
 *  Author: user
 */ 
#include "UART.h"

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