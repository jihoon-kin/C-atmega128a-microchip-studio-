/*
 * bluetooth.c
 *
 * Created: 2024-05-29 오후 4:47:36
 * Author : user
 */ 

typedef unsigned char INT8;
typedef unsigned int INT16;

#define F_CPU 8000000
#define BAUD 9600
#define U2X_S 2
#define MYUBRR ((F_CPU*U2X_S)/(16L*BAUD)-1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "USART_ch0.h"
#include "USART_ch1.h"

volatile INT16 KeyScan;

ISR(USART0_RX_vect)
{
	KeyScan = UDR0;
}

int main(void)
{
	USART0_Init(MYUBRR); // BL
	USART1_Init(MYUBRR); // RS-232

	sbi(UCSR0B, RXCIE);  // RX
	sei();
	
	USART1_Transmit_NewLine();//USART0_Transmit 단어 한글자 보내는 것
	USART1_Transmit('S'); USART1_Transmit('L');
	USART1_Transmit('A'); USART1_Transmit('V');
	USART1_Transmit('E');
	
	char ch;
	
	while(1)
	{
		ch = USART0_Receive();
		USART1_Transmit_NewLine();
		USART1_Transmit(ch); //띄우고 싶은거 담아서 보내면 터미널에 뜬다
		_delay_ms(500);
	}
}