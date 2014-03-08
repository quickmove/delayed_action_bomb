//       _/             _/                            _/
//      _/
//     _/           _/_/     _/  _/_/             _/_/
//    _/             _/     _/_/    _/             _/
//   _/             _/     _/      _/             _/
//  _/             _/     _/      _/       _/    _/
// _/_/_/_/_/   _/_/_/   _/      _/   _/    _/_/  copyright by linjing. 2014

#include <avr/io.h>
#include <util/delay.h>

#include "7seg4display.h"
#include "74164.h"


// ==== 共阴极脚位设置 ===
// 共阴极4脚所在的单片机PORT
#define CASCODE_PORT		PORTD
#define CASCODE_DDR			DDRD
// 共阴极起始脚位
#define CASCODE_BIT_0		0

// 脚位mask，用于运算时取共阴极4个顺序脚位
// 共阴极脚位mask		00001111
#define CASCODE_MASK	0x0F
// 共阴极脚位反umask 	11110000
#define CASCODE_UMASK	0xF0


// LED段显示位表
const uint8_t LED_NUMBER_DATA[] = { 
							  0xfc, // 0
							  0x60, // 1
							  0xda, // 2
							  0xf2, // 3
							  0x66, // 4
							  0xb6, // 5
							  0xbe, // 6
							  0xe0, // 7
							  0xfe, // 8
							  0xf6	// 9
							 };

#define DOT_PORT		PORTD
#define DOT_DDR			DDRD
#define DOT_BIT			4

#define SET_DOT			DOT_PORT |= (1 << DOT_BIT)
#define CLR_DOT			DOT_PORT &= ~(1 << DOT_BIT)


/**
* 设置4位7段数码管的位电平，低电平点亮
* PORTC 第2位开始的4位为共阴脚
*
* position 4位的7段数码管，此为指定某位，0开始
*/
void Display7Seg4SetPosition(uint8_t position);

/**
* 初始化4位7段数码管脚位
*
*/
void Display7Seg4Init() {
	uint8_t i = 0;
	for(i = 0; i < 4; i++) {
		CASCODE_DDR |= (1 << (CASCODE_BIT_0 + i));
	}

	DOT_DDR |= (1 << DOT_BIT);
}


void Display7Seg4SetPosition(uint8_t position) {
	uint8_t tmp1 = CASCODE_MASK;
	uint8_t tmp2 = CASCODE_UMASK;

	tmp1 |= CASCODE_PORT;	// 取共阴极脚位所在的PORT的其他位，赋给tmp1
	tmp2 |= ~(1 << (CASCODE_BIT_0 + position));	//指定位置低电平

	CASCODE_PORT = tmp1 & tmp2;
}

/**
* 设置某位的7段数码管显示
*
* number 显示的数值
* position 4位的7段数码管，此为指定某位，0开始
*
*/
void Display7Seg4SetPositionNumber(uint8_t number, uint8_t position) {
	Display7Seg4SetPosition(position);
	IC164SendData(LED_NUMBER_DATA[number]);
}

static uint8_t flash7segflag = 0;
/**
 * 闪烁中间的那秒点
 */
void Flash7Seg4Dot(void) {
	if(flash7segflag) {
		flash7segflag = 0;
		SET_DOT;
	} else {
		flash7segflag = 1;
		CLR_DOT;
	}
}
