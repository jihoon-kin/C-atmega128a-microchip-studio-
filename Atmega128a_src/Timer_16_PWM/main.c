/*
 * Timer_16_PWM.c
 * 64 prescaler, 100Hz
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// 100Hz짜리 64분주기
//int main(void)
//{
	//DDRB = (1<<PORTB5); // 0b00100000
	//TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	//TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	//
	//OCR1A = 625; // duty 비 2499*0.25 // 25%만 쓸려고
	//ICR1 = 2499; // top 값
	//
    //while (1) 
    //{
    //}
//}


// 50Hz짜리 만들기 64분주기
//int main(void)
//{
	//DDRB = (1<<PORTB5); // 0b00100000
	//TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	//TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	//
	//OCR1A = 1250; // duty 비 2499*0.25 // 25%만 쓸려고
	//ICR1 = 4999; // top 값
	//
	//while (1)
	//{
	//}
//}

int main(void)
{
	DDRB = (1<<PORTB5); // 0b00100000
	TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);
	
	OCR1A = 375; // duty 비 
	ICR1 = 4999; // top 값
	
	while (1)
	{
		OCR1A = 103;
		_delay_ms(1000);
		OCR1A = 640;
		_delay_ms(1000);
		
	}
}