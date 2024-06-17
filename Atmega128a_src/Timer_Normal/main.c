/*
 * Timer_Normal.c
 * CTC Mode와 같은 의미인데, 출력을 OCn 의 핀으로 출력하는 것이 아니라 
 * 내가 지정할 수 있다.
 */

#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
	DDRD = 0xff;
	PORTD = 0x00; // LOW 로 시작해서 TOP만나면 토글
	//TCCR0 = 0b00000101;
	// TCCR0 |= ((1<<CS02) | (1<<CS00));
	// TCCR0 = TCCR0 | ((1<<CS02) | (1<<CS00));
	TCCR0 = (1<<CS02); // (1<<2)
	TCCR0 = (1<<CS00); // (1<<0)
	
	
    while (1) 
    {
    }
}

