#include <REGX51.H>
#include <INTRINS.H>
#define uchar unsigned char
#define uint unsigned int

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
	LCDGotoXY(0,0);
	LCDPrintstr("LCD TEST1");
	LCDGotoXY(1,0);
	LCDPrintstr("LCD TEST2");
}
/**************************

***************************/
void main()
{
	LCD1602_init();
	LCDShowInit();
	while(1)
	{
		
	}
}

