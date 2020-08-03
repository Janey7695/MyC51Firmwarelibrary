#ifndef _DS18B20_H
#define _DS18B20_H

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#define ERROR 0
#define OK 1

sbit DSPORT=P3^7;

int Ds18b20ReadTemp(void);

#endif