//       _/             _/                            _/
//      _/
//     _/           _/_/     _/  _/_/             _/_/
//    _/             _/     _/_/    _/             _/
//   _/             _/     _/      _/             _/
//  _/             _/     _/      _/       _/    _/
// _/_/_/_/_/   _/_/_/   _/      _/   _/    _/_/  copyright by linjing. 2014

#include "74164.h"

#include <avr/io.h>


// ==== 164脚位设置 ====

#define CP164_PORT		PORTB
#define CP164_DDR		DDRB
#define CP164_BIT		0

#define DATA164_PORT	PORTB
#define DATA164_DDR	DDRB
#define DATA164_BIT	1


// ==== 164脚位操作 ====

// 164时钟
#define SET_CP164		CP164_PORT |= (1 << CP164_BIT)
#define CLR_CP164		CP164_PORT &= ~(1 << CP164_BIT)

// 164数据
#define SET_DATA164		DATA164_PORT |= (1 << DATA164_BIT)
#define CLR_DATA164		DATA164_PORT &= ~(1 << DATA164_BIT)

/**
* 初始化164脚位
*
*/
void IC164Init() {
	CP164_DDR |= (1 << CP164_BIT);
	DATA164_DDR |= (1 << DATA164_BIT);
}

/**
* 向74164发送数据
*
* data 数据
*/
void IC164SendData(uint8_t data) {
	
	uint8_t i = 7;
	for(i = 0; i < 8; i++) {
		
		if((1 << i) & data)
			SET_DATA164;
		else
			CLR_DATA164;

		CLR_CP164;
		SET_CP164;
		
	}
}
