// 共阴4位7段数码管 显示控制
// 7段数据 调用74164驱动 做串并转化
// 注：此段程序仅支持 共阴的4位接在单片机某PORT的其中4位，不支持跨PORT

#ifndef _7_SEG_4_DISPLAY_H
#define _7_SEG_4_DISPLAY_H

#include <avr/io.h>
#include <stdint.h>



/**
* 初始化4位7段数码管脚位
*
*/
void init7seg4display();


/**
* 设置4位7段数码管的位电平，低电平点亮
* PORTC 第2位开始的4位为共阴脚
*
* position 4位的7段数码管，此为指定某位，0开始
*/
void set_led_number_position(uint8_t position);


/**
* 设置某位的7段数码管显示
*
* number 显示的数值
* position 4位的7段数码管，此为指定某位，0开始
*
*/
void set_led_number(uint8_t number, uint8_t position);


#endif
