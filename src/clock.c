#include <avr/io.h>
#include <avr/delay.h>
#include <stdint.h>


// 164时钟
#define SET_CP164		PORTC |= (1 << 0)
#define CLR_CP164		PORTC &= ~(1 << 0)

// 164数据
#define SET_DATA164		PORTC |= (1 << 1)
#define CLR_DATA164		PORTC &= ~(1 << 1)


// LED段显示位表
uint8_t LED_NUMBER_DATA[] = { 0xfc, // 0
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


void init() {
	DDRC |= (1 << 0);
	DDRC |= (1 << 1);
}

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
		for(i = 0; i < 10; i++) {
			send164data(LED_NUMBER_DATA[i]);
			_delay_ms(1000);
		}
	}
}
