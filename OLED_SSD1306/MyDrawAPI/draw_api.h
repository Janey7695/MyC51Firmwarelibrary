#ifndef __DRAW_API_H
#define __DRAW_API_H



#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif

void Draw_Point(uchar x,uchar y);//���Ƶ�����
void Draw_Line(uchar x1,uchar y1,uchar x2,uchar y2);//����һ��ֱ�ߣ�����x1<x2��
void Draw_Rect(uchar x1,uchar y1,uchar x2,uchar y2,uchar Full);//����һ�����Σ�(x1,y1)�����Ͻ����꣬��һ�������½����꣬Full=1Ϊ���ģʽ��=0Ϊ�����
void Draw_Tri(uchar x1,uchar y1,uchar x2,uchar y2,uchar x3,uchar y3);//����һ��������
void Draw_Circle(uchar x,uchar y,uchar r);//����һ��Բ
void DisPlay();//��ʾ���Ƶ�ͼ��
void CanvasClear();//��ջ���

#endif