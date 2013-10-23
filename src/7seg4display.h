// 共阴4位7段数码管 显示控制
// 7段数据 调用74164驱动 做串并转化
// 注：此段程序仅支持 共阴的4位接在单片机某PORT的其中4位，不支持跨PORT

#ifndef _7_SEG_4_DISPLAY_H
#define _7_SEG_4_DISPLAY_H

#include <stdint.h>



/**
* 初始化4位7段数码管脚位
*
*/
void Display7Seg4Init();


/**
* 设置某位的7段数码管显示
*
* number 显示的数值
* position 4位的7段数码管，此为指定某位，0开始
*
*/
void Display7Seg4SetPositionNumber(uint8_t number, uint8_t position);


#endif
