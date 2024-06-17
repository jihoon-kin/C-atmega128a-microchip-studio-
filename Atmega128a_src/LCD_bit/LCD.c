/*
 * LCD.c
 *
 * Created: 2024-04-11 오전 10:38:59
 *  Author: user
 */ 
#include "LCD.h"

void LCD_Data(uint8_t data)
{
	LCD_DATA_PORT = data; // 데이터핀에 데이터 출력
}
void LCD_WritePin()
{
	LCD_RW_PORT &= ~(1<<LCD_RW); // RW핀을 LOW로 설정하면 -> 쓰기 모드
}
void LCD_ReadPin()
{
	LCD_RW_PORT |= (1<<LCD_RW); // RW핀을 HIGH로 설정하면 -> 읽기 모드
}
void LCD_EnablePin()
{ // data sheet
	LCD_E_PORT &= ~(1<<LCD_E);	// E 핀을 LOW로 설정
	LCD_E_PORT |= (1<<LCD_E);	// E 핀을 HIGH로 설정
	LCD_E_PORT &= ~(1<<LCD_E);	// E 핀을 LOW로 설정
	_delay_us(1600); // 일정시간 대기
}
void LCD_WriteCommand(uint8_t commandData)
{
	LCD_RS_PORT &= ~(1<<LCD_RS); // RS 핀을 LOW로 설정하면 -> 명령어모드
	LCD_WritePin(); // 데이터(명령어)를 쓸거야
	LCD_Data(commandData); // 명령어 데이터를 데이터핀에 전송
	LCD_EnablePin(); // LCD 동작 신호 전송
}
void LCD_WriteData(uint8_t charData)
{
	LCD_RS_PORT |= (1<<LCD_RS); // RS 핀을 HIGH로 설정하면 -> 문자데이터 설정
	LCD_WritePin(); // 데이터(실제 문자?)를 쓸거야
	LCD_Data(charData); // 문자 데이터를 데이터핀에 전송
	LCD_EnablePin(); // LCD 동작 신호 전송
}
// 커서 위치 잡는 함수
void LCD_GotoXY(uint8_t row, uint8_t col)
{
	col %= 16;	// col 인덱스를 16으로 제한 (16개 열)
	row %= 2;	// row 인덱스를 2로 제한 (2행)
	uint8_t address = (0x40 * row) + col; // 주소 계산
	uint8_t command = 0x80 + address; // 커맨드값 계산(주소설정)
	LCD_WriteCommand(command); // 주소 설정 커맨드를 LCD 전송
}
void LCD_WriteString(char *string) // 배열로 받아서 한 문자씩 출력할거다.
{
	for (uint8_t i = 0; string[i]; i++)
	{
		LCD_WriteData(string[i]); // 문자열의 각 문자를 출력
	}
}
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string)
{
	LCD_GotoXY(row, col); // 지정된 위치로 이동
	LCD_WriteString(string); // 문자열을 해당 위치부터 출력
}
void LCD_Init() // data sheet 에서 HD44780 초기화 과정 그대로 적어준거임
{
	LCD_DATA_DDR = 0xff; // data 핀을 출력으로 설정
	LCD_RS_DDR |= (1<<LCD_RS); // RS 핀을 출력으로 설정
	LCD_RW_DDR |= (1<<LCD_RW); // RW 핀을 출력으로 설정
	LCD_E_DDR |= (1<<LCD_E); // E 핀을 출력으로 설정
	
	_delay_ms(20); // 15ms 이상 기다림
	LCD_WriteCommand(COMMAND_8_BIT_MODE); // 8bit 모드 설정 0x38
	_delay_ms(5); // 4ms 이상 기다림
	LCD_WriteCommand(COMMAND_8_BIT_MODE);
	_delay_ms(5); // 100us 이상 기다림
	LCD_WriteCommand(COMMAND_8_BIT_MODE);
	LCD_WriteCommand(COMMAND_8_BIT_MODE);
	LCD_WriteCommand(COMMAND_DISPLAY_ON); // 화면 켬
	LCD_WriteCommand(COMMAND_DISPLAY_CLEAR); // 화면 클리어
	LCD_WriteCommand(COMMAND_ENTRY_MODE); // 엔트리모드
}