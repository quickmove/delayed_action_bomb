#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdint.h>

// 按键触发回调
typedef void (*callback_keydown_t) (uint8_t btnIndex);
typedef void (*callback_keyup_t) (uint8_t btnIndex);
typedef void (*callback_keybursh_t) (uint8_t btnIndex);
typedef void (*callback_keyburshup_t) (uint8_t btnIndex);

/**
* 初始化控制按钮的管脚
*
*/
void ButtonInit();

/**
 * 注册回调keydown
 */
void ButtonRegisterKeyDownFunc(callback_keydown_t func);
/**
 * 注册回调keyup
 */
void ButtonRegisterKeyUpFunc(callback_keyup_t func);
/**
 * 注册回调keybursh
 */
void ButtonRegisterKeyBurshFunc(callback_keybursh_t func);
/**
 * 注册回调keyburshup
 */
void ButtonRegisterKeyBurshUpFunc(callback_keyburshup_t func);

/**
 * 按键检测
 */
uint8_t ButtonCheckBtnValue(uint8_t btnIndex);


#endif
