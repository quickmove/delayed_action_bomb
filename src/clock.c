#include <avr/io.h>
#include <avr/delay.h>
#include <stdint.h>


// 164时钟
#define SET_CP164		PORTC |= (1 << 0)
#define CLR_CP164		PORTC &= ~(1 << 0)

// 164数据
#define SET_DATA164		PORTC |= (1 << 1)
#define CLR_DATA164		PORTC &= ~(1 << 1)

// 164共级 0, 1, 2, 3
#define SET_CASCODE(i)	PORTC |= (1 << 2 + i)
#define CLR_CASCODE(i)	PORTC &= ~(1 << 2 + i)


// LED段显示位表
const uint8_t LED_NUMBER_DATA[] = { 0xfc, // 0
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

uint8_t led_number_left = 0;	// 7段数码管，左边数字的值
uint8_t led_number_right = 0;	// 7段数码管，右边数字的值


/**
* 初始化各I/O口
*
*/
void init() {
	DDRC |= (1 << 0);
	DDRC |= (1 << 1);
	DDRC |= (1 << 2);
	DDRC |= (1 << 3);
	DDRC |= (1 << 4);
	DDRC |= (1 << 5);
}

/**
* 设置4位7段数码管的位电平，低电平点亮
* PORTC 第2位开始的4位为共阴脚
*
*/
void set_led_number_position(uint8_t position) {
	uint8_t tmp1 = 0x3c;	// 0111100
	uint8_t tmp2 = 0x43;	// 1000011

	tmp1 |= PORTC;	// 取PORTC的0,1位，赋给tmp1
	tmp2 |= ~(1 << (2 + position));	//指定位置低电平

	PORTC = tmp1 & tmp2;
}


/**
* 设置某位的7段数码管显示
*
* number 显示的数值
* position 4位的7段数码管，此为指定某位，0开始
*
*/
void set_led_number(uint8_t number, uint8_t position) {
	send164data(LED_NUMBER_DATA[number]);

}

/**
* 向74164发送数据
*
*/
void send164data(uint8_t data) {
	
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

int main(void) {
	init();
	while(1) {
		uint8_t i = 0;
		
		set_led_number_position(0);
		

		for(i = 0; i < 10; i++) {
			set_led_number(i, 0);
			_delay_ms(1000);
		}

	}
}
