﻿/*
 * UART_INT_LED.h
 *
 * Created: 2024-04-09 오후 2:19:09
 *  Author: user
 */ 


#ifndef UART_INT_LED_H_
#define UART_INT_LED_H_


#include <avr/io.h>

typedef struct
{
	volatile uint8_t	*port;	//LED가 연결된 포트
	uint8_t				pin;	//LED가 연결된 핀번호
}LED;

void ledInit(LED *led);
void ledOn(LED *led);
void ledOff(LED *led);

void UART0_Init();
void UART0_Transmit(char data);
unsigned char UART0_Receive();



#endif /* UART_INT_LED_H_ */