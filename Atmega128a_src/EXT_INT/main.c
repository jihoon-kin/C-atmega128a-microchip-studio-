#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> // 인터럽트를 위한 헤더파일
#include <util/delay.h>

ISR(INT4_vect) // int 치고 Ctrl+space 누르면 나온다.
{
	PORTA = 0xff;
}
ISR(INT5_vect)
{
	PORTA = 0x00;
}


int main(void)
{
	DDRA = 0xff;	// LED 출력
	// 외부 인터럽트 INT4(PE4), INT5(PE5) 사용할거다.
	// EICR a, b 인지 찾아야한다. 
	// INT 4, EICR a, b // falling 일떄 (1, 0)
	EICRB |= (1<<ISC41) | (0<<ISC40);
	
	// INT 5, EICR a, b // Rising 일떄 (1. 1) 
	EICRB |= (1<<ISC51) | (1<<ISC50);
	EIMSK |= (1<<INT5) | (1<<INT4);
	
	DDRE &= ~(1<<DDRE4) | ~(1<<DDRE5); // 버튼 4번핀 5번핀
	
	
	sei();
	
    while (1) 
    {
    }
}

