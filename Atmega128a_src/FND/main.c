#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    uint8_t FND_Number[]
	= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
		// a ~ p -> 0 ~ 9 port 연결
	int count = 0;
	DDRA = 0xff;
	
    while (1) 
    {
		PORTA = FND_Number[count];
		count = (count + 1) % 10; // 나머지값
		_delay_ms(500);
    }
}

