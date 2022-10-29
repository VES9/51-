#include "ds1302.h"

unsigned char time[8] = {0x00,0x45,0x19,0x18,0x10,0x01,0x21,0x20};//秒分时 日月周 年

/*DS1302单字节读数据函数*/
unsigned char ds1302_readByte(unsigned char dat)
{
	unsigned char i = 0;
	for(i=0;i<8;i++)  
	{
		dat = dat >> 1;	 //左移一次 低位开始 共有效左移7次
		if(DAT == 1) 		
			dat = dat | 0x80;	 //高位置1
		else
			dat = dat & 0x7F;	 //高位置0	
		CLK = 1; //时钟拉高表示这位已经结束
		CLK = 0; //时钟拉低开始接收新的数据位
	}	
	return dat;

}

/*DS1302单字节写地址或者数据函数*/
void ds1302_writeByte(unsigned char addrOrData)
{
	unsigned char i = 0;
	for(i=0;i<8;i++)   
	{
		DAT = addrOrData & 0x01;	//开始传输低位 
		addrOrData = addrOrData >> 1;//右移一位
		CLK = 1;					 //拉高时钟表示已经发送
		CLK = 0;					 //拉低时钟准备继续放新的数据位
	}
					
}

/*DS1302时钟模块写命令函数*/
void ds1302_writeCom(unsigned char addr,unsigned char dat)
{
 	RST = 0; //拉低RST
	CLK = 0; //拉低时钟
	RST = 1; //使能打开
	ds1302_writeByte(addr);	 //写入要写的地址
	ds1302_writeByte(dat);	 //写入地址的数据
	RST = 0; //关闭 表示结束
}

/*DS1302时钟模块读数据函数*/
unsigned char ds1302_readData(unsigned char addr)
{
	unsigned char dat = 0;
	RST = 0; //拉低RST
	CLK = 0; //拉低时钟
	RST = 1; //打开使能
	ds1302_writeByte(addr);		//写入要读的地址
	dat = ds1302_readByte(dat);	//读取地址的数据
	RST = 0; //关闭 表示结束
	
	return dat; //返回读取到的数据
}

/*DS1302时钟模块读取日期和时间函数*/
void ds1302_read_DateAndTime()
{
	time[0] = ds1302_readData(DS1302_READ_YEAR);  //读取年
	time[1] = ds1302_readData(DS1302_READ_MONTH); //读取月
	time[2] = ds1302_readData(DS1302_READ_DAY);   //读取日
	time[3] = ds1302_readData(DS1302_READ_HOUR);  //读取时
	time[4] = ds1302_readData(DS1302_READ_MINUTE);//读取分
	time[5] = ds1302_readData(DS1302_READ_SECOND);//读取秒
	time[6] = ds1302_readData(DS1302_READ_WEEK);  //读取周		
}

/*DS1302时钟模块初始化函数*/
void ds1302_init()
{
	RST = 0; //关闭RST
	CLK = 0; //拉低时钟
	ds1302_writeCom(DS1302_WRITE_PROTECT,0x00); //关闭写保护 这样才能进行写操作
	ds1302_burst_write(DS1302_WRITE_TIME);	//初始化全部时间
	//ds1302_initTime(); //初始时间：2021年10月18日 19点45分00秒 周一	
	ds1302_writeCom(DS1302_WRITE_PROTECT,0x80); //开启写保护 只读模式
		
}

