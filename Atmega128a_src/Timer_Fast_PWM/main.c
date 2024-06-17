/*
 * Timer_Fast_PWM.c
 * 8bit Timer PWM
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = (1<<PORTB4);	// 0x10; // 0b00010000
	
	TCCR0 |= (1<<WGM00) | (1<<WGM01);
	TCCR0 |= (1<<COM01) | (1<<COM00);
	TCCR0 |= (1<<CS02) | (1<<CS01) |(0<<CS00);
	TCCR0 = 0x6D;
	//OCR0 = 64;
	
    while (1) 
    {
		//for (int i=0; i<=255; i++)
		//{
			//OCR0 = i;
			//_delay_ms(15);
		//}
    }
}

