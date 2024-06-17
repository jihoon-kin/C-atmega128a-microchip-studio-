/*
 * I2C.c
 *
 * Created: 2024-04-12 오후 4:49:46
 *  Author: user
 */ 
#include "I2C.h"

void I2C_Init()
{
	I2C_DDR |= (1<<I2C_SCL) | (1<<I2C_SDA); // 출력 설정
	TWBR = 72; // 100kHz
	//TWBR = 32; // 200kHz
	//TWBR = 12; // 400kHz
}
// 여기서 부터 필기파일에 표를 코드한거임
void I2C_Start() // 1, 2
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// TWINT에 1을 셋트하여 인터럽트를 발생시키는것 같지만
	// 소프트웨어적으로 1을 셋트하여 플래그를 클리어 하는것임!!
	while (!(TWCR & (1<<TWINT))); // 하드웨어적으로 TWINT를 클리어함
	// 미리 1을 넣었다가 1이 들어와서 클리어시키려고 하는것임.
	// 왜냐하면 하드웨어가 작업을 완료하면 자기가 알아서 1로 셋트함
}

void I2C_Stop() // 7
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); // stop bit 설정
}

void I2C_TxData(uint8_t data) // 1byte // 5, 6
{
	TWDR = data; // 저장이된거고
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // 전송 완료 대기
}

void I2C_TxByte(uint8_t devAddRw, uint8_t data) //
{
	I2C_Start();
	I2C_TxData(devAddRw);
	I2C_TxData(data);
	I2C_Stop();
}