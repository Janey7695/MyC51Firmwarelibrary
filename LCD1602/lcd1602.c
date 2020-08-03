#include"lcd1602.h"

void Lcd1602_delay1ms(uint i)   //误差 0us
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
由于可能使用的是4位的显示器，因此需要考虑到4位的操作
通过将h文件里面的定义作为8/4位切换开关
***/
#ifndef LCD1602_4PINS
void LcdWriteCom(uchar com){
	LCD1602_E=0;//使能
	LCD1602_RS=0;//选择发送指令的模式
	LCD1602_RW=0;//选择写入

	LCD1602_DATAPINS = com;//写入命令
	Lcd1602_delay1ms(1);//等待数据稳定
	
	LCD1602_E = 1;//写入时序
	Lcd1602_delay1ms(5);//保持时间
	LCD1602_E = 0;
}
#else //4位的操作
void LcdWriteCom(uchar com){
	LCD1602_E=0;//使能
	LCD1602_RS=0;//选择发送指令的模式
	LCD1602_RW=0;//选择写入

	LCD1602_DATAPINS = com;//传入高4位
	Lcd1602_delay1ms(1);//等待数据稳定
	
	LCD1602_E = 1;//写入时序
	Lcd1602_Delay1ms(5);//保持时间
	LCD1602_E = 0;
	
	LCD1602_DATAPINS = com << 4; //发送低四位
	Lcd1602_delay1ms(1);
	
	LCD1602_E = 1;//写入时序
	Lcd1602_delay1ms(5);//保持时间
	LCD1602_E = 0;
	
}
#endif

#ifndef LCD1602_4PINS
void LcdWriteData(uchar dat){
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_delay1ms(1);

	LCD1602_E = 1;   //写入时序
	Lcd1602_delay1ms(5);   //保持时间
	LCD1602_E = 0;
}
#else //4位操作
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	  //使能清零
	LCD1602_RS = 1;	  //选择写入数据
	LCD1602_RW = 0;	  //选择写入

	LCD1602_DATAPINS = dat;	//由于4位的接线是接到P0口的高四位，所以传送高四位不用改
	Lcd1602_delay1ms(1);

	LCD1602_E = 1;	  //写入时序
	Lcd1602_delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //写入低四位
	Lcd1602_delay1ms(1);

	LCD1602_E = 1;	  //写入时序
	Lcd1602_delay1ms(5);
	LCD1602_E = 0;
}
#endif

#ifndef LCD1602_4PINS
void LcdInit()						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
#else
void LcdInit()						  //LCD初始化子程序
{
	LcdWriteCom(0x32);	 //将8位总线转为4位总线
	LcdWriteCom(0x28);	 //在四位线下的初始化
	LcdWriteCom(0x0c);  //开显示不显示光标
	LcdWriteCom(0x06);  //写一个指针加1
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x80);  //设置数据指针起点
}
#endif