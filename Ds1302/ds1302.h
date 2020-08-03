#ifndef _DS1302_H
#define _DS1302_H

#include<reg52.h>
#include<intrins.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

extern uchar TIME[7];//加入全局变量
void Ds1302Write(uchar addr,uchar dat);
uchar Ds1302Read(uchar addr);
void Ds1302Init();
void Ds1302ReadTime();




#endif