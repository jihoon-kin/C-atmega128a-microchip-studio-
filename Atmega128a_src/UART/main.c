/*
 * UART.c
 *
 * Created: 2024-04-08 오전 9:48:45
 * Author : user
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"

// PE0, PE1 번핀 사용할거임 
// 보드에 파란 버튼을 오른쪽으로 하면 우리 컴퓨터와 통신이 된다. (UART0)
// 속도 9600 설정, 2배속 모드, 
// 비동기, 8bit, parity 없음, 1bit stop bit
int main(void)
{
	UART0_Init();
	
    while (1) 
    {
		UART0_Transmit(UART0_Receive()); // 받은 내용을 그대로 보내는거임
    }
}

