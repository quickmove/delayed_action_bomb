//                   _                    _
//                 /_/\                 /_/\
//                /_/\/      _       _ _\_\/
//               /_/\/     /_/\     /_/_/\
//              /_/\/      \_\/      /_/\/
//             /_/\/         _      /_/\/
//            /_/\/_ _ _   /_/_ _ _/_/\/
//           /_/_/_/_/_/\  \/_/_/_/\_\/  copyright.2014
//           \_\_\_\_\_\/   \_\_\_\/       by linjing
//

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
#define KEYSTATE_WAIT_BURST_RELEASE		3

///////////////////////////
// 脚位定义


#define BTN1_PIN		PINC
#define BTN1_PORT		PORTC
#define BTN1_DDR		DDRC
#define BTN1_BIT		0

#define BTN2_PIN		PINC
#define BTN2_PORT		PORTC
#define BTN2_DDR		DDRC
#define BTN2_BIT		1

#define BTN3_PIN		PINC
#define BTN3_PORT		PORTC
#define BTN3_DDR		DDRC
#define BTN3_BIT		2

///////////////////////////
// 脚位取值

// 按键相对于按键1的bit位置偏移作为index号...
// 这里有点奇怪的写法没找到其他写法啊...

#define BTN_GLOBAL_PIN		PINC
#define VAL_BTN(index)		(BTN_GLOBAL_PIN & (1 << (BTN1_BIT + index)))

// 按键索引，相对于第0个按键
#define KEYINDEX_MODE_BUTTON		0
#define KEYINDEX_ADD_BUTTON		1
#define KEYINDEX_SUB_BUTTON		2

//////////////////////////////////////////////////////////////
// 声明

// mode键相关的回调句柄
callback_mode_button_keydown_t modeBtnKeyDownFunc;
callback_mode_button_keyup_t modeBtnKeyUpFunc;
callback_mode_button_keybursh_t modeBtnKeyBurshFunc;
callback_mode_button_keyburshup_t modeBtnKeyBurshUpFunc;

// add键相关的回调句柄
callback_add_button_keydown_t addBtnKeyDownFunc;
callback_add_button_keyup_t addBtnKeyUpFunc;
callback_add_button_keybursh_t addBtnKeyBurshFunc;
callback_add_button_keyburshup_t addBtnKeyBurshUpFunc;

// sub键相关的回调句柄
callback_sub_button_keydown_t subBtnKeyDownFunc;
callback_sub_button_keyup_t subBtnKeyUpFunc;
callback_sub_button_keybursh_t subBtnKeyBurshFunc;
callback_sub_button_keyburshup_t subBtnKeyBurshUpFunc;

void btnKeyDownFire(uint8_t btnIndex);
void btnKeyUpFire(uint8_t btnIndex);
void btnKeyBurshFire(uint8_t btnIndex);
void btnKeyBurshUpFire(uint8_t btnIndex);

/**
 * 按键当前状态
 */
static uint8_t _keystate[] = { 0, 0, 0 };

/**
 * 连发触发的延时计数
 */

static uint16_t _keyburshDelayCount[] = { 0, 0, 0 };

/**
 * 连发触发的延时计数_超时数
 */
#define KEYBURSH_DELAY_MAXCOUNT	0x40

///////////////////////////////////////////////////////////////////
// 实现

/**
 * 初始化控制按钮的管脚
 *
 */
void ButtonInit() {
	BTN1_DDR &= ~(1 << BTN1_BIT);
	BTN2_DDR &= ~(1 << BTN2_BIT);
	BTN3_DDR &= ~(1 << BTN3_BIT);
	
	BTN1_PORT |= (1 << BTN1_BIT);
	BTN2_PORT |= (1 << BTN2_BIT);
	BTN3_PORT |= (1 << BTN3_BIT);
}

/**
 * 触发按下
 */
void btnKeyDownFire(uint8_t btnIndex) {
	if (btnIndex == KEYINDEX_MODE_BUTTON) {
		if (modeBtnKeyDownFunc)
			modeBtnKeyDownFunc();
	} else if (btnIndex == KEYINDEX_ADD_BUTTON) {
		if (addBtnKeyDownFunc)
			addBtnKeyDownFunc();
	} else if (btnIndex == KEYINDEX_SUB_BUTTON) {
		if (subBtnKeyDownFunc)
			subBtnKeyDownFunc();
	}
}

/**
 * 触发按下释放
 */
void btnKeyUpFire(uint8_t btnIndex) {
	if (btnIndex == KEYINDEX_MODE_BUTTON) {
		if (modeBtnKeyUpFunc)
			modeBtnKeyUpFunc();
	} else if (btnIndex == KEYINDEX_ADD_BUTTON) {
		if (addBtnKeyUpFunc)
			addBtnKeyUpFunc();
	} else if (btnIndex == KEYINDEX_SUB_BUTTON) {
		if (subBtnKeyUpFunc)
			subBtnKeyUpFunc();
	}
}

/**
 * 触发连发
 */
void btnKeyBurshFire(uint8_t btnIndex) {
	if (btnIndex == KEYINDEX_MODE_BUTTON) {
		if (modeBtnKeyBurshFunc)
			modeBtnKeyBurshFunc();
	} else if (btnIndex == KEYINDEX_ADD_BUTTON) {
		if (addBtnKeyBurshFunc)
			addBtnKeyBurshFunc();
	} else if (btnIndex == KEYINDEX_SUB_BUTTON) {
		if (subBtnKeyBurshFunc)
			subBtnKeyBurshFunc();
	}
}

/**
 * 触发连发释放
 */
void btnKeyBurshUpFire(uint8_t btnIndex) {
	if (btnIndex == KEYINDEX_MODE_BUTTON) {
		if (modeBtnKeyBurshUpFunc)
			modeBtnKeyBurshUpFunc();
	} else if (btnIndex == KEYINDEX_ADD_BUTTON) {
		if (addBtnKeyBurshUpFunc)
			addBtnKeyBurshUpFunc();
	} else if (btnIndex == KEYINDEX_SUB_BUTTON) {
		if (subBtnKeyBurshUpFunc)
			subBtnKeyBurshUpFunc();
	}
}

/**
 * 扫描 指定索引号的按键
 */
void ButtonByIndexScan(uint8_t btnIndex) {

	switch (_keystate[btnIndex]) {
	case KEYSTATE_IDLE:
		if (!VAL_BTN(btnIndex)) {
			_keystate[btnIndex] = KEYSTATE_WAIT_DOWN_VALID;
		}
		break;
	case KEYSTATE_WAIT_DOWN_VALID:
		if (VAL_BTN(btnIndex)) {
			_keystate[btnIndex] = KEYSTATE_IDLE;
		} else {
			_keystate[btnIndex] = KEYSTATE_WAIT_DOWN_RELEASE;
			// fire_keydown
			btnKeyDownFire(btnIndex);
		}
		break;
	case KEYSTATE_WAIT_DOWN_RELEASE:
		if (!VAL_BTN(btnIndex)) {
			// 加个计数，表示按键按下延时一会儿然后进入连发的姿势，并计数清零
			_keyburshDelayCount[btnIndex]++;
			if (_keyburshDelayCount[btnIndex] > KEYBURSH_DELAY_MAXCOUNT) {
				_keystate[btnIndex] = KEYSTATE_WAIT_BURST_RELEASE;
				_keyburshDelayCount[btnIndex] = 0;
			}
		} else {
			_keystate[btnIndex] = KEYSTATE_IDLE;
			_keyburshDelayCount[btnIndex] = 0;
			// fire_keyup
			btnKeyUpFire(btnIndex);
		}
		break;
	case KEYSTATE_WAIT_BURST_RELEASE:
		// fire_bursh
		btnKeyBurshFire(btnIndex);

		if (VAL_BTN(btnIndex)) {
			_keystate[btnIndex] = KEYSTATE_IDLE;
			// fire_burshup
			btnKeyBurshUpFire(btnIndex);
		}
		break;
	}
}

void ButtonRegisterModeButtonKeyDownFunc(callback_mode_button_keydown_t func) {
	modeBtnKeyDownFunc = func;
}
void ButtonRegisterModeButtonKeyUpFunc(callback_mode_button_keyup_t func) {
	modeBtnKeyUpFunc = func;
}
void ButtonRegisterModeButtonKeyBurshFunc(callback_mode_button_keybursh_t func) {
	modeBtnKeyBurshFunc = func;
}
void ButtonRegisterModeButtonKeyBurshUpFunc(
		callback_mode_button_keyburshup_t func) {
	modeBtnKeyBurshUpFunc = func;
}

void ButtonRegisterAddButtonKeyDownFunc(callback_add_button_keydown_t func) {
	addBtnKeyDownFunc = func;
}

void ButtonRegisterAddButtonKeyUpFunc(callback_add_button_keyup_t func) {
	addBtnKeyUpFunc = func;
}
void ButtonRegisterAddButtonKeyBurshFunc(callback_add_button_keybursh_t func) {
	addBtnKeyBurshFunc = func;
}

void ButtonRegisterAddButtonKeyBurshUpFunc(
		callback_add_button_keyburshup_t func) {
	addBtnKeyBurshUpFunc = func;
}

void ButtonRegisterSubButtonKeyDownFunc(callback_sub_button_keydown_t func) {
	subBtnKeyDownFunc = func;
}

void ButtonRegisterSubButtonKeyUpFunc(callback_sub_button_keyup_t func) {
	subBtnKeyUpFunc = func;
}

void ButtonRegisterSubButtonKeyBurshFunc(callback_sub_button_keybursh_t func) {
	subBtnKeyBurshFunc = func;
}

void ButtonRegisterSubButtonKeyBurshUpFunc(
		callback_sub_button_keyburshup_t func) {
	subBtnKeyBurshUpFunc = func;
}
