/*
 * LED.c
 *
 * Created: 2024-04-08 오후 2:21:18
 *  Author: mujukpopo
 */ 

#include "LED.h"

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