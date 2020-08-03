#include"oled.h"
#include"oledfont.h"

/*********
对于x于y位置的值，x可以取0-127 y可以取0-7
*******/


//毫秒延时函数
void delay_ms(unsigned int ms){
	unsigned int a;
	while(ms){
		a=1800;
		while(a--);
		ms--;
	}
}


//向SSD1306写入一个字节
//dat 要写入的数据或命令
//mode 为0时写入命令，为1时写入数据
void OLED_WR_Byte(uchar dat,uchar mode){
	uchar i;
	if(mode)//判断是写入数据还是命令
		DC_E();
	else
		DC_NE();
	
	CS_NE();//片选信号拉低
	
	for(i=0;i<8;i++){
		SCL_L();//拉低时钟，准备接收数据
		if(dat&0x80)//从高位开始传送数据
		{
			SDIN_H();
		}
		else
			SDIN_L();
		SCL_H();//拉高时钟线，接收数据
		dat<<=1;//数据左移一位，移除刚刚接收的最高位
	}
	
	CS_E();//片选信号拉高，表示一帧数据接收完毕
	
	DC_E();//默认拉高
}

//设置显示指针位置
void OLED_Set_Pos(uchar x,uchar y){
	OLED_WR_Byte(0xb0+y,OLED_CMD); //使用页寻址模式的时候，64行被分为8组，因此建议的字体大小为16*8（竖16横8 字母、符号）或8*8（竖8横8）或16*16（汉字）
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);//设置seg位置的高四位
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD);//设置seg位置的低四位
	//最后高低四位组合转成10进制来决定x定位在哪一列
	//seg的设置有特殊规则
	//Lower Column Start Address (00h-0fh)
	//Higher Column Start Address (10h-1fh)
	//分别计算这2者，然后取lower的后一位作为低四位，取higher的后一位作为高四位
	//比如 lower 是03h higher是10h 则合成的八位位置码是 03h ，因此定位在第三列
}

//显示开启
void OLED_Display_On(){
	OLED_WR_Byte(0x8d,OLED_CMD); //set DCDC命令？？？ TODO:等待了解
	OLED_WR_Byte(0x14,OLED_CMD);//DCDC OFF
	OLED_WR_Byte(0xaf,OLED_CMD); //开启显示
}

//显示关闭
void OLED_Display_Off(){
	OLED_WR_Byte(0x8d,OLED_CMD); //set DCDC命令？？？ TODO:等待了解
	OLED_WR_Byte(0x14,OLED_CMD);//DCDC OFF
	OLED_WR_Byte(0xae,OLED_CMD); //关闭显示
}

//清屏
void OLED_Clear(){
	uchar i,n;
	for(i=0;i<8;i++){
		OLED_WR_Byte(0xb0+i,OLED_CMD);//定位到页
		OLED_WR_Byte(0x00,OLED_CMD);//设置seg的高四位
		OLED_WR_Byte(0x10+i,OLED_CMD);//设置seg的低四位 
		//通过上面2条设置，将定位到第一列
		for(n=0;n<128;n++)
			OLED_WR_Byte(0,OLED_DATA);//每页有128列
	}
}
//显示单个字符 TODO:编写字库(不包括汉字)，没有像LCD1602那样自带了字库。
void OLED_ShowChar(uchar x,uchar y,uchar CHAR,uchar fontsize){
	uchar i,j;
	j=CHAR-32;
	if(fontsize==16)
	{
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WR_Byte(CHAR16x8[j*16+i],OLED_DATA);
		}
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		{
			OLED_WR_Byte(CHAR16x8[j*16+i+8],OLED_DATA);
		}
	}
	else
	{
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		{
			OLED_WR_Byte(CHAR8x6[j][i],OLED_DATA);
		}
	}
}

//显示一个字符串 TODO:设置成可以适应16*16的中文字体
void OLED_ShowStr(uchar x,uchar y,uchar*chr,uchar fontsize){
	uchar j=0,spacing;
	
	if(fontsize==16) spacing=8;
	else spacing=6; //设置字间距
	
	while(chr[j]!='\0')
	{
		OLED_ShowChar(x,y,chr[j],fontsize);
		x+=spacing; //设置字间距为spacing
		
		if(x>120)//超出屏幕自动切行
		{
			x=0;
			y+=2;
		}
		j++;
	}
}

//显示位图图片 TODO:位图图库`BMP[]`
void OLED_DrawBMP(uchar x0,uchar y0,uchar x1,uchar y1,uchar BMP[])
{
	uint j=0;
	uchar x,y;
	if(y1%8==0)
		y=y1/8;
	else
		y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++)
		{
			OLED_WR_Byte(BMP[j++],OLED_DATA);
		}
	}
}

void OLED_Init(){
	RST_E();
	delay_ms(100);
	RST_NE();
	delay_ms(100);
	RST_E();
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0);
}

