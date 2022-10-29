#include <REGX51.H>
typedef unsigned char uchar;
typedef unsigned int uint;
sbit start= P3^0;
sbit eoc= P3^6;
sbit oe= P3^2;
sbit RS= P3^3;
sbit RW= P3^4;
sbit EN= P3^5;

uchar vol=0;
uchar str0[]={'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'};
uchar str1[]={'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'};
uchar a[]={"0123456789"};

uchar t0=0;
uchar t1=0;
uchar t2=0;


void delay(uint n)
{
	uint i=0;
	uint j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<120;j++);
	}
}
	
void adc()
{
	start=0;
	oe=0;
	start=1;
	delay(5);
	start=0;
	while(eoc!=1);
	oe=1;
	vol=P2;
	oe=0;
}


/***************************
写指令cmd
***************************/
void LCDWritecmd(uchar cmd)
{
	RS=0;
	RW=0;
	P0=cmd;
	EN=0;
	delay(2);
	EN=1;
	delay(2);
}

/***************************
写数据dat
***************************/
void LCDWritedata(uchar dat)
{
	RS=1;
	RW=0;
	P0=dat;
	EN=0;
	delay(2);
	EN=1;
	delay(2);
}

/***************************
光标定位
***************************/
void LCDGotoXY(uchar line,uchar column)
{
	if(line==0)
	{
		LCDWritecmd(0x80+column);
	}
	if(line==1)
	{
		LCDWritecmd(0x80+0x40+column);
	}
}

/***************************
输出字符串
***************************/
void LCDPrintstr(uchar *str)
{
	while(*str!='\0')
		LCDWritedata(*str++);
}

/**************************
开启1602显示
***************************/
void LCDON()
{
	LCDWritecmd(0x0c);
}
/**************************
关闭1602显示
***************************/
void LCDOFF()
{
	LCDWritecmd(0x08);
}

/**************************
1602初始化
***************************/
void LCD1602_init()
{
	LCDWritecmd(0x38);
	LCDWritecmd(0x0c);
	LCDWritecmd(0x06);
	LCDWritecmd(0x01);
}

/**************************
初始化1602显示内容
***************************/
#if 0
void LCDShowInit()
{

//	LCDGotoXY(uchar line,uchar column);
//	LCDPrintstr(uchar *str);
//	LCDGotoXY(uchar line,uchar column);
//	LCDPrintstr(uchar *str);
	uchar i=0;
	uchar j=0;

	str0[0]='v';
	str0[1]='o';
	str0[2]='l';
	str0[3]='=';
	str0[4]=t0;
	str0[5]=t1;
	str0[6]=t2;
	str0[7]=' ';
	str0[8]=' ';
	str0[9]=' ';
	str0[10]=' ';
	str0[11]=' ';
	str0[12]=' ';
	str0[13]=' ';
	str0[14]=' ';
	str0[15]=' ';
	LCDGotoXY(0,0);
	for(i=0;i<16;i++)
	{
		LCDWritedata(str0[i]);
	}
	
	str1[0]='@';
  str1[1]='D';
  str1[2]='A';
	str1[3]='T';
	str1[4]='E';	
  str1[5]=':';
  str1[6]='2';
  str1[7]='0';
  str1[8]='2';
  str1[9] ='2';
  str1[10]='.';
  str1[11]='9'; 
	str1[12]='.';
  str1[13]='2';
	str1[14]='3';
	str1[15]=' ';
	LCDGotoXY(1,0);
	for(j=0;j<16;j++)
	{
		LCDWritedata(str1[j]);
		
	}
	

}
#endif

void LCDShowInit()
{
  uchar t0=0;
	uchar t1=0;
	uchar t2=0;
	t0=vol/100;
	t1=(vol%100)/10;
	t2=vol%10;
	LCDGotoXY(0,0);
	LCDWritedata(a[t0]);
	LCDGotoXY(0,1);
	LCDWritedata(a[t1]);
  LCDGotoXY(0,2);
	LCDWritedata(a[t2]);
}



void main()
{
		LCD1602_init();

	while(1)
	{
	  LCDShowInit();
		adc();
	}
}