// ����4λ7������� ��ʾ����
// 7������ ����74164���� ������ת��
// ע���˶γ����֧�� ������4λ���ڵ�Ƭ��ĳPORT������4λ����֧�ֿ�PORT

#ifndef _7_SEG_4_DISPLAY_H
#define _7_SEG_4_DISPLAY_H

#include <avr/io.h>
#include <stdint.h>



/**
* ��ʼ��4λ7������ܽ�λ
*
*/
void init7seg4display();


/**
* ����4λ7������ܵ�λ��ƽ���͵�ƽ����
* PORTC ��2λ��ʼ��4λΪ������
*
* position 4λ��7������ܣ���Ϊָ��ĳλ��0��ʼ
*/
void set_led_number_position(uint8_t position);


/**
* ����ĳλ��7���������ʾ
*
* number ��ʾ����ֵ
* position 4λ��7������ܣ���Ϊָ��ĳλ��0��ʼ
*
*/
void set_led_number(uint8_t number, uint8_t position);


#endif
