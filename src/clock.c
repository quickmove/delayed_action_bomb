#include <avr/io.h>
#include <avr/delay.h>
#include <stdint.h>


// 164ʱ��
#define SET_CP164		PORTC |= (1 << 0)
#define CLR_CP164		PORTC &= ~(1 << 0)

// 164����
#define SET_DATA164		PORTC |= (1 << 1)
#define CLR_DATA164		PORTC &= ~(1 << 1)

// 164���� 0, 1, 2, 3
#define SET_CASCODE(i)	PORTC |= (1 << 2 + i)
#define CLR_CASCODE(i)	PORTC &= ~(1 << 2 + i)


// LED����ʾλ��
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

uint8_t led_number_left = 0;	// 7������ܣ�������ֵ�ֵ
uint8_t led_number_right = 0;	// 7������ܣ��ұ����ֵ�ֵ


/**
* ��ʼ����I/O��
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
* ����4λ7������ܵ�λ��ƽ���͵�ƽ����
* PORTC ��2λ��ʼ��4λΪ������
*
*/
void set_led_number_position(uint8_t position) {
	uint8_t tmp1 = 0x3c;	// 0111100
	uint8_t tmp2 = 0x43;	// 1000011

	tmp1 |= PORTC;	// ȡPORTC��0,1λ������tmp1
	tmp2 |= ~(1 << (2 + position));	//ָ��λ�õ͵�ƽ

	PORTC = tmp1 & tmp2;
}


/**
* ����ĳλ��7���������ʾ
*
* number ��ʾ����ֵ
* position 4λ��7������ܣ���Ϊָ��ĳλ��0��ʼ
*
*/
void set_led_number(uint8_t number, uint8_t position) {
	send164data(LED_NUMBER_DATA[number]);

}

/**
* ��74164��������
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
