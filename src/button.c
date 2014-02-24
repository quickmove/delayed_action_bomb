#include <avr/io.h>
#include <stdint.h>

#include "button.h"

// 空闲
#define KEYSTATE_IDLE					0
// 等待按下确认(防抖)
#define KEYSTATE_WAIT_DOWN_VALID		1
// 等待按下释放
#define KEYSTATE_WAIT_DOWN_RELEASE		2
// 等待连发释放
#define KEYSTATE_WAIT_BURST_RELEASE	3

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

uint8_t ButtonCheckBtnValue(uint8_t btnIndex) {
	
	uint8_t ret = 0;

	switch(_keystate[btnIndex]) {
		case KEYSTATE_IDLE:
			if(!VAL_BTN(btnIndex)) {
				_keystate[btnIndex] = KEYSTATE_WAIT_DOWN_VALID;
			}
			break;
		case KEYSTATE_WAIT_DOWN_VALID:
			if(VAL_BTN(btnIndex)) {
				_keystate[btnIndex] = KEYSTATE_IDLE;
			} else {
				_keystate[btnIndex] = KEYSTATE_WAIT_DOWN_RELEASE;
				//TODO: keydown
			}
			break;
		case KEYSTATE_WAIT_DOWN_RELEASE:
			if(!VAL_BTN(btnIndex)) {
				ret = 2;
				_keystate[btnIndex] = KEYSTATE_WAIT_BURST_RELEASE;
			} else {
				_keystate[btnIndex] = KEYSTATE_IDLE;
				//TODO: keyup
			}
			break;
		case KEYSTATE_WAIT_BURST_RELEASE:
			//TODO: 加个延时计数，然后在此bursh
			if(VAL_BTN(btnIndex)) {
				_keystate[btnIndex] = KEYSTATE_IDLE;
				//TODO: burshup
			}
			break;
	}
	return ret;
}






