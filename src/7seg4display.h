//       _/             _/                            _/
//      _/
//     _/           _/_/     _/  _/_/             _/_/
//    _/             _/     _/_/    _/             _/
//   _/             _/     _/      _/             _/
//  _/             _/     _/      _/       _/    _/
// _/_/_/_/_/   _/_/_/   _/      _/   _/    _/_/  copyright by linjing. 2014

// ����4λ7������� ��ʾ����
// 7������ ����74164���� ������ת��
// ע���˶γ����֧�� ������4λ���ڵ�Ƭ��ĳPORT������4λ����֧�ֿ�PORT

#ifndef _7_SEG_4_DISPLAY_H
#define _7_SEG_4_DISPLAY_H

#include <stdint.h>

void Display7Seg4Init();
void Display7Seg4SetPositionNumber(uint8_t number, uint8_t position);
void Flash7Seg4Dot();


#endif
