#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "74164.h"
#include "7seg4display.h"


uint8_t led_number_left = 0;	// 7段数码管，左边数字的值
uint8_t led_number_right = 0;	// 7段数码管，右边数字的值


/**
* 初始化各设备对应单片机I/O口
*
*/
void init() {
	IC164Init();
	Display7Seg4Init();
}




int main(void) {
	init();
	while(1) {
	
		//uint8_t i = 0;

		//for(i = 0; i < 10; i++) {
			//set_led_number(i, 0);
			//_delay_ms(1000);
		//}
	
		uint8_t leftnum = 9;
		uint8_t rightnum = 35;
		uint8_t numbers[4];
	
		numbers[0] = leftnum / 10;
		numbers[1] = leftnum % 10;
		numbers[2] = rightnum / 10;
		numbers[3] = rightnum % 10;
	
		uint8_t i = 0;
		for(i = 0; i < 4; i++) {
			Display7Seg4SetPositionNumber(numbers[i], i);
			_delay_ms(10);
		}
	}
}
