/*
 * ADC_CDS.c
 *
 * Created: 2024-04-15 오전 10:14:55
 * Author : user
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL, _FDEV_SETUP_WRITE);

void ADC_Init()
{
	ADMUX |= (1<<REFS0); // 기준전압 설정
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // 128 분주
	ADCSRA |= (1<<ADEN); // 인에이블 
	ADCSRA |= (1<<ADFR); // 러닝모드?
}

int read_ADC(uint8_t channel)
{
	ADMUX = ((ADMUX & 0xf0) | (channel & 0x0f)); // 단일 입력 채널선택
	// (ADMUX & 0xf0) >> 내가 원하는 값을 꺼내기 위한것, and 연산을 걸어서 상위비트 네자리만 뽑을수있다.
	ADCSRA |= (1<<ADSC); // 변환 시작
	while(!(ADCSRA & (1<<ADIF))); // 변환 종료 대기
	
	return ADC;
}

int main(void)
{
	int read;
	ADC_Init();
	UART0_Init();
	stdout = &OUTPUT;
	
    while (1) 
    {
		read = read_ADC(0);
		printf("channel 0 : %d\n", read);
		_delay_ms(1000);
    }
}

