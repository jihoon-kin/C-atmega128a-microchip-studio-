
#include "uart0.h"

uint8_t uart0RxBuff [100];
uint8_t uart0RxCFlag;

void UART0_init()
{
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0); // Enable Rx and Rx
	UCSR0A |= (1 << U2X0); // Double the speed of internal clock
	UBRR0L = 207; // 16: 115200bps, 207: 9600 bps
	UCSR0B |= (1 << RXCIE0); // Enable Receiver interrupt
	sei();				
}

uint8_t UART0_getRxFlag()
{
	return uart0RxCFlag;
}

void UART0_clearRxFlag()
{
	uart0RxCFlag = 0;
}

void UART0_setReadyRxFlag()
{
	uart0RxCFlag = 1;
}

uint8_t *UART0_readRxBuff()
{
	return uart0RxBuff;
}

void USART0_Transmit( unsigned char data )
{	 	
	while ( !( UCSR0A & (1 << UDRE0)));	
	UDR0 = data;
}

unsigned char USART0_Receive( void )
{	 
	while ( !(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void UART0_print(char *str)
{
	for (int i = 0; str[i]; i++)
	{
		USART0_Transmit(str[i]);
	}
	USART0_Transmit('\n');
}

uint8_t UART0_Avail()
{
	// If there is RxData, return 0. Otherwise, return 1.
	if ( !(UCSR0A & (1 << RXC0)) )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void USART0_ISR_Process() // 인터럽트가 걸리면 여기가 실행이 된다. 
{ // 정적/전역변수는 프로그램이 끝나도 초기화되지 않는다. 지역변수는 자기가 속해있는 함수가 끝나면 삭제된다.
	// 정적변수는 초기화시켜줘야하고, 전역변수는 끝나면 알아서 초기화된다.
	uint8_t rx0Data = UDR0; 
	static uint8_t uart0RxTail = 0; // 인덱스넘버를 설정해주기 위한 것. static으로 해주는 이유 : 정적변수이기 때문에 
	// Insert null (\0) at the end of corresponding string and initialize a tail to 0 when \n detected
	if (rx0Data == '\n') // a,a,a,\n 를 입력해준다고 생각하고 봐라
	{
		uart0RxBuff[uart0RxTail] = rx0Data;
		uart0RxTail++; // 증가시키고
		uart0RxBuff[uart0RxTail] = '\0'; // 배열에서 문자열의 끝을 알림 // 그 뒤로는 다 초기화시키고
		uart0RxTail = 0; // 다음걸 받기 위해서 인덱스를 초기화시키고
		UART0_setReadyRxFlag(); // 배열에 문자가 들어왔어라고 알려주는 플래그를 1로 만든것
	}
	else
	{
		uart0RxBuff[uart0RxTail] = rx0Data; // 0번 인덱스에다가 rx0Data를 넣어준다
		uart0RxTail++; // 그리고 인덱스를 1로 만든다 // 0번 방은 a 로 찼기 때문에 다음 1번 방 인덱스로 간다.
	}
}

void UART0_execute() // 얘만 계속 실행된다. while 안에 얘밖에 없어서
// 플래그를 갖고와봤더니, 플래그의 상태는 set 이 있고 clear 가 있다.
// 0이면 딜레이, 1이면 플래그를 0으로 만들어주고, 
// UART0_readRxBuff 라는데에 있는 애를 rxString이라는 포인터변수에 집어넣어준거다 .
{	   
	if (UART0_getRxFlag())  
	{
		UART0_clearRxFlag(); // clear = 0; 위에 0으로 선언해줬다.
		uint8_t *rxString = UART0_readRxBuff();
		
		printf(rxString);
	}
	_delay_ms(300);
}
// 새로운 입력을 주면 기존꺼는 지워진다.
// 배열 선언할때, 