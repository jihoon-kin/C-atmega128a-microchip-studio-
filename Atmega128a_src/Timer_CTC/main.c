#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// CTC mode : clear time on compare match -> pdf에 찾아서 설명봐
// 내부클럭을 count해서 0CR0 값과 비교 일치하면 OC0번핀에 특정 주파수 발생
// 64 분주기 1000Hz 만들기
//int main(void)
//{
	//DDRB = 0x10; // 0b00010000 PB4 출력 설정
	//TCCR0 = 0x1C; // 0b00011100 
	//OCR0 = 124; // 비교값 
    //while (1) 
    //{
		//while((TIFR & 0x02) == 0); // 0인지 아닌지 체크
		//TIFR = 0x02; // 다음 비교일치를 위해 해당비트를 클리어
		//OCR0 = 124;  // 새로 다시 시작 하는거니까 재 셋팅
		//
    //}
//}

// 128 분주기 250Hz 짜리 만들기
int main(void)
{
	DDRB = 0x10; // 0b00010000 PB4 출력 설정
	TCCR0 = 0x1D; // 0b00011101
	OCR0 = 249; // 비교값
	while (1)
	{
		while((TIFR & 0x02) == 0); // 0인지 아닌지 체크
		TIFR = 0x02; // 다음 비교일치를 위해 해당비트를 클리어
		OCR0 = 249;  // 새로 다시 시작 하는거니까 재 셋팅
	}
}