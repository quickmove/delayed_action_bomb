#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdint.h>


/**
* 初始化控制按钮的管脚
*
*/
void ButtonInit();


uint8_t ButtonCheckBtnValue(uint8_t btnIndex);

#endif
