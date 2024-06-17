﻿/*
 * LCD_4bit.h
 *
 * Created: 2024-04-11 오후 3:17:30
 *  Author: user
 */ 


#ifndef LCD_4BIT_H_
#define LCD_4BIT_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LCD_DATA_DDR	DDRC		//데이터 나가는선
#define LCD_DATA_PORT	PORTC
#define LCD_DATA_PIN	PINC
#define LCD_E_DDR		DDRF		//명령어 나가는선
#define LCD_RS_DDR		DDRF
#define LCD_RW_DDR		DDRF
#define LCD_RS_PORT		PORTF
#define LCD_RW_PORT		PORTF
#define LCD_E_PORT		PORTF
#define LCD_RS			5
#define LCD_RW			6
#define LCD_E			7

#define COMMAND_DISPLAY_CLEAR	0x01
#define COMMAND_DISPLAY_ON		0x0C
#define COMMAND_DISPLAY_OFF		0x08
#define COMMAND_ENTRY_MODE		0x06
#define COMMAND_8_BIT_MODE		0x38
#define COMMAND_4_BIT_MODE		0x28

//void LCD_Data4bitInit(uint8_t data);

//void LCD_WriteInit(uint8_t commandData);
//void LCD_WritePin();

void LCD_DATA(uint8_t data);
void LCD_Data4bit(uint8_t data);
void LCD_writeMode();
void LCD_ReadPin();
void LCD_EnablePin();
void LCD_WriteCommand(uint8_t commandData);
void LCD_WriteData(uint8_t charData);
void LCD_GotoXY(uint8_t row, uint8_t col);
void LCD_WriteString(char *string);
void LCD_WriteStringXY(uint8_t row, uint8_t col, char *string);
void LCD_Init();




#endif /* LCD_4BIT_H_ */