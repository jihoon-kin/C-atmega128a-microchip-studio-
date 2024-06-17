#ifndef BUTTON_2_H_
#define BUTTON_2_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// 위에 두개는 출력 밑에 두개는 입력
#define LED_DDR			DDRA
#define LED_PORT		PORTA
#define BUTTON_DDR		DDRC
#define BUTTON_PIN		PINC
#define BUTTON_ON		0
#define BUTTON_OFF		1
#define BUTTON_TOGGLE	2

enum{PUSHED, RELEASED};
enum{NO_ACT, ACT_PUSHED, ACT_RELEASED};
	
typedef struct _button
{
	volatile uint8_t *ddr; // volatile = 최적화하지말라
	volatile uint8_t *pin;
	uint8_t btnPin;
	uint8_t prevState; // 현재 누르고있는 버튼의 상태
	
}Button;

void Button_Init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum);

uint8_t BUTTON_getState(Button *button);

#endif /* BUTTON_2_H_ */