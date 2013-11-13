#include <avr/io.h>
#include <stdint.h>

#include "button.h"

///////////////////////////
// 标志变量声明
static uint8_t _keystate;
static uint8_t _keyflag;

#define KEYSTATE_NONE		0
#define KEYSTATE_DOWN		1
#define KEYSTATE_KEEPDOWN	2


///////////////////////////
// 脚位定义

#define BTN1_PIN		PIND
#define BTN1_DDR		DDRD
#define BTN1_BIT		5

#define BTN2_PIN		PIND
#define BTN2_DDR		DDRD
#define BTN2_BIT		6

#define BTN3_PIN		PIND
#define BTN3_DDR		DDRD
#define BTN3_BIT		7

///////////////////////////
// 脚位取值

// IO取值
#define VAL_BTN1		(BTN1_PIN & (1 << BTN1_BIT))
#define VAL_BTN2		(BTN2_PIN & (1 << BTN2_BIT))
#define VAL_BTN3		(BTN3_PIN & (1 << BTN3_BIT))


//////////////////////////

void ButtonInit() {
	BTN1_DDR &= ~(1 << BTN1_BIT);
	BTN2_DDR &= ~(1 << BTN2_BIT);
	BTN3_DDR &= ~(1 << BTN3_BIT);

	_keystate = 0;
	_keyflag = 0;

}

uint8_t checkBtn1Value() {
	uint8_t ret = 0;

	switch(_keystate) {
		case KEYSTATE_NONE:
			if(_keyflag == 0 && VAL_BTN1) {
				_keyflag = 1;
				_keystate = KEYSTATE_DOWN;
			}
			break;
		case KEYSTATE_DOWN:
			if(_keyflag && VAL_BTN1 == 0) {
				_keyflag = 0;
				_keystate = KEYSTATE_NONE;
			} else if(_keyflag && VAL_BTN1) {
				ret = 1;
				_keyflag = 1;
				_keystate = KEYSTATE_KEEPDOWN;
			}
			break;
		case KEYSTATE_KEEPDOWN:
			if(_keyflag && VAL_BTN1 == 0) {
				_keyflag = 0;
				_keystate = KEYSTATE_NONE;
			}
			break;
	}
	return ret;
}






