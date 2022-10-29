#include <REGX51.H>
#include <INTRINS.H>
#define uchar unsigned char
#define schar static char
#define uint unsigned int
sbit IN1=P1^0;
sbit IN2=P1^1;
sbit EN1=P1^2;
schar valueh[]={0x1b,0x0b};
schar valuel[]={0x58,0xb8};
void delay(uint n)
{
	uchar i=0;
	uchar j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<120;j++);
	}
}

void Timer0_init()
{
	TMOD=0x01;
	TH0=(65536-8000)/256;
	TL0=(65536-8000)%256;
	TR0=1;
	IN2=0;
}

void ISR_init()
{
	EA=1;
	EX0=0;
	ET0=1;
	EX1=0;
	ET1=0;
	ES=0;
}

void Timer0_Overflow()
{
	uchar m;
	if(TF0==1)
	{
		TF0=0;
		m++;
		if(m==10)
		{
			IN1=~IN2;
			m=0;
		}
	}
}

void TF0_ISR() interrupt 0
{
//	schar q;
//	TH0=0xd8;
//	TL0=0xf0;
//	q++;
	uint count=0;
	TH0=valueh[count];
	TL0=valuel[count];
	IN2=~IN2;
	count++;
	if(count==2)
	{
		count=0;
	}
	
//	if(q==90)
//	{
//		IN1=~IN2;
//		q=0;
//	}
}

void motor()
{
	IN1=1;
	IN2=0;
	EN1=1;
}

void main()
{
	while(1)
	{
		Timer0_init();
		ISR_init();
		motor();
	}
	
}