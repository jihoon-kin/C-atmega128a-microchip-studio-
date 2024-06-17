#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define  FND_DATA_DDR DDRA
#define FND_SELECT_DDR DDRC // digit select
#define FND_DATA_PORT PORTA
#define FND_SELECT_PORT PORTC

void FND_Display(uint16_t data); // 4자릿수 사용을 위한 2Byte

int main(void)
{
	FND_DATA_DDR = 0xff;
	FND_SELECT_DDR = 0xff;
	FND_SELECT_PORT = 0x00;
	
	uint16_t count = 0;
	uint32_t timeTick = 0;
	uint32_t prevTime = 0;
	
    while (1) 
    {
		FND_Display(count); // 현재시간 timeTick,  
		if (timeTick - prevTime > 100) // 100ms가 지날때 마다 증가시킬거야
		{
			prevTime = timeTick;
			count++;
		}
		_delay_ms(1); 
		timeTick++;
    }
}
void FND_Display(uint16_t data)
{
	static uint8_t position = 0;
	uint8_t fndData[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
		
	switch (position)// 출력할 자리(position)에 따라 해당 자리 출력
	{
		case 0: 
		// 첫번째 자리 출력위해 , 0번핀 LOW, 1,2,3 HIGH
		FND_SELECT_PORT &= ~(1<<0); // 0 digit ON
		FND_SELECT_PORT |= (1<<1) | (1<<2) | (1<<3); // 1,2,3 digit OFF
		// 입력된 데이터의 천의 자리를 구해서 해당 FND 데이터 값 출력
		FND_DATA_PORT = fndData[data/1000];
		break;
		case 1: // 100의 자리 구하기 [data/1000 % 10]
		// 
		FND_SELECT_PORT &= ~(1<<1);
		FND_SELECT_PORT |= (1<<0) | (1<<2) | (1<<3); 
		FND_DATA_PORT = fndData[data/100 %10];
		break;
		case 2:
		//
		FND_SELECT_PORT &= ~(1<<2);
		FND_SELECT_PORT |= (1<<1) | (1<<0) | (1<<3);
		FND_DATA_PORT = fndData[data/10 %10];
		break;
		case 3:
		//
		FND_SELECT_PORT &= ~(1<<3);
		FND_SELECT_PORT |= (1<<1) | (1<<2) | (1<<0);
		FND_DATA_PORT = fndData[data %10];
		break;
	}
	position++; // 다음 자리 이동
	position = position % 4; // 위치를 표시하는 4, 숫자 X
}
