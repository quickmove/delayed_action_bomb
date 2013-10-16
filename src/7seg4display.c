#include <util/delay.h>

#include "7seg4display.h"
#include "74164.h"


// ==== 共阴极脚位设置 ===
// 共阴极4脚所在的单片机PORT
#define CASCODE_PORT		PORTC
#define CASCODE_DDR			DDRC
// 共阴极起始脚位
#define CASCODE_BIT_0		2


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

void init7seg4display() {
	uint8_t i = 0;
	for(i = 0; i < 4; i++) {
		CASCODE_DDR |= (1 << (CASCODE_BIT_0 + i));
	}
}


void set_led_number_position(uint8_t position) {
	uint8_t tmp1 = 0x3c;	// 0111100
	uint8_t tmp2 = 0x43;	// 1000011

	tmp1 |= CASCODE_PORT;	// 取共阴极脚位所在的PORT的其他位，赋给tmp1
	tmp2 |= ~(1 << (CASCODE_BIT_0 + position));	//指定位置低电平

	CASCODE_PORT = tmp1 & tmp2;
}

void set_led_number(uint8_t number, uint8_t position) {
	set_led_number_position(position);
	send164data(LED_NUMBER_DATA[number]);
}
