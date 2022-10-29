#include <REGX51.H>
#include <INTRINS.H>
#define uchar unsigned char
#define uint unsigned int
uchar t[]={"0123456789"};
	uint sec=0;
uchar q=0;
	uint min=0;
	uint hour=0;
/**************************
��������Ĵ�����λ����
***************************/
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
/**************************
���뼶��ʱ����
***************************/
void delay(uchar n)
{
	uchar i=0;
	uchar j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<120;j++);
	}
}
/**************************
дָ��cmd
***************************/
void LCDWritecmd(uchar cmd)
{
	RS=0;
	RW=0;
	P0=cmd;
	EN=1;
	delay(2);
	EN=0;
	delay(2);
}
/**************************
д����dat
***************************/
void LCDWritedata(uchar dat)
{
	RS=1;
	RW=0;
	P0=dat;
	EN=1;
	delay(2);
	EN=0;
	delay(2);
}
/**************************
��궨λ
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
/**************************
����ַ���
***************************/
void LCDPrintstr(uchar *str)
{
	while(*str!='\0')
		LCDWritedata(*str++);
}
/**************************
1602��ʼ��
***************************/
void LCD1602_init()
{
	LCDWritecmd(0x38);
	LCDWritecmd(0x0c);
	LCDWritecmd(0x06);
	LCDWritecmd(0x01);
}
/**************************
����1602��ʾ
***************************/
void LCDON()
{
	LCDWritecmd(0x0c);
}
/**************************
�ر�1602��ʾ
***************************/
void LCDOFF()
{
	LCDWritecmd(0x08);
}
/**************************
��ʼ��1602��ʾ����
***************************/
void LCDShowInit()
{
	uchar temp0,temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8=0;
	temp0=hour/10;
	temp1=hour%10;
	
	temp2=min/10;
	temp3=min%10;
	
	temp4=sec/10;
	temp5=sec%10;

	
	LCDGotoXY(0,0);
	LCDWritedata(t[temp0]);
	delay(5);
	LCDWritedata(t[temp1]);
  delay(5);
	LCDWritedata(';');
	
	LCDWritedata(t[temp2]);
	delay(5);
	LCDWritedata(t[temp3]);
  delay(5);
	LCDWritedata(';');
 
	LCDWritedata(t[temp4]);
  delay(5);
  LCDWritedata(t[temp5]);
  delay(5);

	LCDGotoXY(1,0);
  LCDPrintstr("qqq");
}



void Timer0_Init()
{
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TR0=1;
}

void ISR_init()
{
	EA=1;
	ET0=1;
	EX0=0;
	ET1=0;
	EX1=0;
	ES=0;
}

void Service_Timer0() interrupt 1
{
	

	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	q++;
	if(q==20)
	{
		sec=sec+1;
		q=0;
	}
	if(sec==60)
	{
		min=min+1;
		sec=0;
	}
	if(min==60)
	{
		hour=hour+1;
		min=0;
	
	}
	if(hour==24)
	{
		hour=0;
	
	}
}


/**************************

***************************/
void main()
{
	LCD1602_init();
  Timer0_Init();
	ISR_init();
	while(1)
	{
		LCDShowInit();
	}
}

















