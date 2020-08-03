#include"ds18b20.h"

//void delay1ms(void)
//{
//    uchar i,j;
//    for(i=199;i>0;i--)
//    for(j=1;j>0;j--);
//}
//void delay760us(void)
//{
//    unsigned char i,j;
//    for(i=151;i>0;i--)
//    for(j=1;j>0;j--);
//}
//void delay15us(void)
//{
//    unsigned char i,j;
//    for(i=2;i>0;i--)
//    for(j=1;j>0;j--);
//}

////初始化函数
//uchar Ds18b20Init(){
//	uchar i;
//	i++; //不严格简单延时
//	DSPORT=0;
//	delay760us();
//	DSPORT=1;
//	i=0;
//	while(DSPORT)
//	{
//		
//		i++;
//		if(i>5000)
//			return ERROR;
//	}
//	led1=0;
//	return OK;
//}

////写时序  由低到高
//void Ds18b20WriteByte(uchar dat){
//	uint i=0;
//	uchar j=0;
//	for(i=0;i<8;i++){
//		DSPORT=0;
//		delay15us();
//		DSPORT=dat&0x01; //取dat最低位
//		j=6;
//		while(j--);//延时约68us
//		DSPORT=1;
//		dat>>=1;//右移一位，下次就能取到下一位
//	}
//}

////读时序  由高到低
//uchar Ds18b20ReadByte(void){
//	uint  i;
//	uchar recvdat,j;
//	for(i=0;i<8;i++){
//		DSPORT=1;
//		DSPORT=0;
//		delay15us();
//		DSPORT=1;
//		delay15us();
//		j=DSPORT;
//		recvdat=(recvdat>>1)|(j<<7);
//		delay15us();
//		delay15us();
//	}
//	return recvdat;
//}

////开始温度转换
//void Ds18b20ChangeTemp(){
//	int i;
//	Ds18b20Init();
//	delay1ms();
//	Ds18b20WriteByte(0xcc);
//	Ds18b20WriteByte(0x44);
//	i=90;
//	while(i!=0)
//	{
//		delay1ms();
//	}
//	led2=0;
//}

////传送温度数据
//void Ds18b20ReadTemp(){
//	Ds18b20Init();
//	delay1ms();
//	Ds18b20WriteByte(0xcc);
//	Ds18b20WriteByte(0xbe);
//	led3=0;
//}

////获取温度
//int GetTemp(){
//	int temp=0;
//	uchar tml,tmh;
//	Ds18b20ChangeTemp();
//	Ds18b20ReadTemp();
//	tml=Ds18b20ReadByte();
//	tmh=Ds18b20ReadByte();
//	temp=tmh;
//	temp<<=8;
//	temp|=tml;
//	led4=0;
//	return temp;
//}

void Delay1ms(unsigned int y)
{
	unsigned int x;
	for(y;y>0;y--)
		for(x=110;x>0;x--);
}

unsigned char Ds18b20Init()
{
	unsigned int i;
	DSPORT=0;			 
	i=70;	
	while(i--);
	DSPORT=1;			
	i=0;
	while(DSPORT)	
	{
		i++;
		if(i>5000)
			return 0;
	}
	return 1;
}


void Ds18b20WriteByte(unsigned char dat)
{
	unsigned int i,j;
	for(j=0;j<8;j++)
	{
		DSPORT=0;			
		i++;
		DSPORT=dat&0x01; 
		i=6;
		while(i--); 
		DSPORT=1;	
		dat>>=1;
	}
}


unsigned char Ds18b20ReadByte()
{
	unsigned char byte,bi;
	unsigned int i,j;	
	for(j=8;j>0;j--)
	{
		DSPORT=0;
		i++;
		DSPORT=1;
		i++;
		bi=DSPORT;	
		
		byte=(byte>>1)|(bi<<7);						  
		i=4;		
		while(i--);
	}				
	return byte;
}

void  Ds18b20ChangTemp()
{
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);		
	Ds18b20WriteByte(0x44);	 
   
}

void  Ds18b20ReadTempCom()
{	

	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);	 
	Ds18b20WriteByte(0xbe);	 
}


int Ds18b20ReadTemp()
{
	int temp=0;
	unsigned char tmh,tml;
	Ds18b20ChangTemp();			 
	Ds18b20ReadTempCom();			
	tml=Ds18b20ReadByte();		
	tmh=Ds18b20ReadByte();		
	temp=tmh;
	temp<<=8;
	temp|=tml;
	return temp;
}