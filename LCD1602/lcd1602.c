#include"lcd1602.h"

void Lcd1602_delay1ms(uint i)   //��� 0us
{
    uchar a,b;
		for (; i>0; i--)
		{
			for (b=199;b>0;b--)
			{
					for(a=1;a>0;a--);
			}      
	} 	
}
/***
���ڿ���ʹ�õ���4λ����ʾ���������Ҫ���ǵ�4λ�Ĳ���
ͨ����h�ļ�����Ķ�����Ϊ8/4λ�л�����
***/
#ifndef LCD1602_4PINS
void LcdWriteCom(uchar com){
	LCD1602_E=0;//ʹ��
	LCD1602_RS=0;//ѡ����ָ���ģʽ
	LCD1602_RW=0;//ѡ��д��

	LCD1602_DATAPINS = com;//д������
	Lcd1602_delay1ms(1);//�ȴ������ȶ�
	
	LCD1602_E = 1;//д��ʱ��
	Lcd1602_delay1ms(5);//����ʱ��
	LCD1602_E = 0;
}
#else //4λ�Ĳ���
void LcdWriteCom(uchar com){
	LCD1602_E=0;//ʹ��
	LCD1602_RS=0;//ѡ����ָ���ģʽ
	LCD1602_RW=0;//ѡ��д��

	LCD1602_DATAPINS = com;//�����4λ
	Lcd1602_delay1ms(1);//�ȴ������ȶ�
	
	LCD1602_E = 1;//д��ʱ��
	Lcd1602_Delay1ms(5);//����ʱ��
	LCD1602_E = 0;
	
	LCD1602_DATAPINS = com << 4; //���͵���λ
	Lcd1602_delay1ms(1);
	
	LCD1602_E = 1;//д��ʱ��
	Lcd1602_delay1ms(5);//����ʱ��
	LCD1602_E = 0;
	
}
#endif

#ifndef LCD1602_4PINS
void LcdWriteData(uchar dat){
	LCD1602_E = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd1602_delay1ms(1);

	LCD1602_E = 1;   //д��ʱ��
	Lcd1602_delay1ms(5);   //����ʱ��
	LCD1602_E = 0;
}
#else //4λ����
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	  //ʹ������
	LCD1602_RS = 1;	  //ѡ��д������
	LCD1602_RW = 0;	  //ѡ��д��

	LCD1602_DATAPINS = dat;	//����4λ�Ľ����ǽӵ�P0�ڵĸ���λ�����Դ��͸���λ���ø�
	Lcd1602_delay1ms(1);

	LCD1602_E = 1;	  //д��ʱ��
	Lcd1602_delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //д�����λ
	Lcd1602_delay1ms(1);

	LCD1602_E = 1;	  //д��ʱ��
	Lcd1602_delay1ms(5);
	LCD1602_E = 0;
}
#endif

#ifndef LCD1602_4PINS
void LcdInit()						  //LCD��ʼ���ӳ���
{
 	LcdWriteCom(0x38);  //����ʾ
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
#else
void LcdInit()						  //LCD��ʼ���ӳ���
{
	LcdWriteCom(0x32);	 //��8λ����תΪ4λ����
	LcdWriteCom(0x28);	 //����λ���µĳ�ʼ��
	LcdWriteCom(0x0c);  //����ʾ����ʾ���
	LcdWriteCom(0x06);  //дһ��ָ���1
	LcdWriteCom(0x01);  //����
	LcdWriteCom(0x80);  //��������ָ�����
}
#endif