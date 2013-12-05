#include <avr/io.h>
#include <stdint.h>

#include "button.h"



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

// 按键相对于按键1的bit位置偏移作为index号...
// 这里有点奇怪的写法没找到其他写法啊...
#define BTN_GLOBAL_PIN		PIND
#define VAL_BTN(index)		(BTN_GLOBAL_PIN & (1 << (BTN1_BIT + index)))

//////////////////////////

void ButtonInit() {
	BTN1_DDR &= ~(1 << BTN1_BIT);
	BTN2_DDR &= ~(1 << BTN2_BIT);
	BTN3_DDR &= ~(1 << BTN3_BIT);

}

static uint8_t _keystate[] = {0, 0, 0};

uint8_t checkBtnValue(uint8_t btnIndex) {
	
	uint8_t ret = 0;

	switch(_keystate[btnIndex]) {
		case KEYSTATE_NONE:
			if(!VAL_BTN(btnIndex)) {
				_keystate[btnIndex] = KEYSTATE_DOWN;
			}
			break;
		case KEYSTATE_DOWN:
			if(VAL_BTN(btnIndex)) {
				_keystate[btnIndex] = KEYSTATE_NONE;
			} else {
				ret = 1;
				_keystate[btnIndex] = KEYSTATE_KEEPDOWN;
			}
			break;
		case KEYSTATE_KEEPDOWN:
			if(VAL_BTN(btnIndex)) {
				_keystate[btnIndex] = KEYSTATE_NONE;
			}
			break;
	}
	return ret;
}






