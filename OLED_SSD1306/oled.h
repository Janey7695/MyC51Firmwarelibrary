#ifndef __OLED_H
#define __OLED_H

#include"reg52.h"

#define uchar unsigned char
#define uint unsigned int

#define OLED_CMD 0 //д����
#define OLED_DATA 1 //д����


sbit O_CS=P1^4; //Ƭѡʹ��
sbit O_RST=P1^2;//��λ
sbit O_DC=P1^3;//����/����ѡ��  0Ϊд������ 1Ϊд������
sbit O_SCL=P1^0;//ʱ��D0
sbit O_SDIN=P1^1;//����D1


//�꺯������ܽ�״̬
#define CS_NE() O_CS=0
#define CS_E() O_CS=1

#define RST_NE() O_RST=0
#define RST_E() O_RST=1

#define DC_NE() O_DC=0
#define DC_E() O_DC=1

#define SCL_L() O_SCL=0
#define SCL_H() O_SCL=1

#define SDIN_L() O_SDIN=0
#define SDIN_H() O_SDIN=1

void delay_ms(unsigned int ms);

void OLED_WR_Byte(uchar dat,uchar mode);//д���ݻ�����
void OLED_Display_On(void);//������ʾ��
void OLED_Display_Off();//�ر���ʾ��
void OLED_Init();//��ʼ��
void OLED_Clear();//����
void OLED_Set_Pos(uchar x,uchar y);//��ʾָ�붨λ
void OLED_ShowChar(uchar x,uchar y,uchar CHAR,uchar fontsize);//��ӡһ���ַ� CHARΪҪ��ʾ���ַ���fontsize�Ǵ�С(16��8)
void OLED_ShowStr(uchar x,uchar y,uchar*chr,uchar fontsize);//��ӡһ���ַ��� chrΪҪ��ʾ���ַ�����fontsize�Ǵ�С(16��8)
void OLED_DrawBMP(uchar x0,uchar y0,uchar x1,uchar y1,uchar BMP[]);//��ʾһ��λͼͼƬ


#endif