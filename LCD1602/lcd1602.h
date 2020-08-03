#ifndef _LCD1602_H
#define _LCD1602_H

#include"reg52.h"

//#define LCD1602_4PINS  //当使用的是4位的数据传输时定义，如果是8位传输则取消这个定义

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

#define LCD1602_DATAPINS P0  //数据bus总线
sbit LCD1602_E=P2^7;
sbit LCD1602_RS=P2^6;
sbit LCD1602_RW=P2^5;

void Lcd1602_delay1ms(uint i); //1ms延时
void LcdWriteCom(uchar com); //写入8位命令函数
void LcdWriteData(uchar dat); //写入8位数据
void LcdInit();//初始化函数

#endif