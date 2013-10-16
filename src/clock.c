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
	init164();
	init7seg4display();
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
