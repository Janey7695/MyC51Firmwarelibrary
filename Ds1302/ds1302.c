#include"ds1302.h"

//读/写（写的话在读的基础上减1）寄存器的地址，从左往右依次是：秒、分、时、日、月、星期、年、写保护寄存器
uchar code READ_RTC_ADDR[7]={0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};
uchar code WRITE_RTC_ADDR[7]={0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
//初始化的时间，BCD编码，从左往右是秒、分、时、日、月、星期、年
uchar TIME[7]={0x40,0x49,0x11,0x01,0x01,0x01,0x20};

//写字节函数（地址+数据）
void Ds1302Write(uchar addr,uchar dat)
{
    uchar n;
    RST=0;
    _nop_(); //先把ce拉低
    SCLK=0;//把时钟线拉低，ce需要在sclk低电平的情况下才能拉高
    _nop_();
    RST=1;//将ce拉高，准备开始输入命令
    _nop_();

    for(n=0;n<8;n++)//先写入地址
    {
        DSIO=addr&0x01;
        addr>>=1;//数据从低位开始传送，每传送完一位，地址就像右移位一位
        SCLK=1;
        _nop_();//sclk上升沿ds1302读数据
        SCLK=0;
        _nop_();
    }
    for(n=0;n<8;n++)//写入数据
    {
        DSIO=dat&0x01;
        dat>>=1;
        SCLK=1;
        _nop_();//sclk上升沿ds1302读数据
        SCLK=0;
        _nop_();
    }
    RST=0;//传输数据接收，ce拉低
    _nop_();
}

//读数据函数（输入地址，返回数据）
uchar Ds1302Read(uchar addr){
    uchar n,dat,dat1;
    RST=0;
    _nop_();
    SCLK=0;
    _nop_();
    RST=1;
    _nop_();

    for(n=0;n<8;n++)//先写入地址
    {
        DSIO=addr&0x01;
        addr>>=1;//数据从低位开始传送，每传送完一位，地址就像右移位一位
        SCLK=1;
        _nop_();//sclk上升沿ds1302读数据
        SCLK=0;
        _nop_();
    }

    for(n=0;n<8;n++)
    {
        dat1=DSIO;
        dat=(dat>>1)|(dat1<<7);
        SCLK=1;
        _nop_();
        SCLK=0;
        _nop_();//ds1302下降沿，放置数据
    }

    RST=0;
    _nop_();
    SCLK=1;
    _nop_();
    DSIO=0;
    _nop_();
    DSIO=1;
    _nop_();
    return dat;
}


void Ds1302Init(){
    uchar n;
    Ds1302Write(0x8e,0x00);//关闭写保护位
    for(n=0;n<7;n++)
    {
        Ds1302Write(WRITE_RTC_ADDR[n],TIME[n]);
    }
    Ds1302Write(0x8e,0x80);//开启写保护功能
}

void Ds1302ReadTime()
{
    uchar n;
    for(n=0;n<7;n++)
    {
        TIME[n]=Ds1302Read(READ_RTC_ADDR[n]);
    }
}