#ifndef _LCD1602_H
#define _LCD1602_H

#include"reg52.h"

//#define LCD1602_4PINS  //��ʹ�õ���4λ�����ݴ���ʱ���壬�����8λ������ȡ���������

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#define LCD1602_DATAPINS P0  //����bus����
sbit LCD1602_E=P2^7;
sbit LCD1602_RS=P2^6;
sbit LCD1602_RW=P2^5;

void Lcd1602_delay1ms(uint i); //1ms��ʱ
void LcdWriteCom(uchar com); //д��8λ�����
void LcdWriteData(uchar dat); //д��8λ����
void LcdInit();//��ʼ������

#endif