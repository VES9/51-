#include <REGX51.H>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define schar static char
sbit IN1=P1^0;
sbit IN2=P1^1;
sbit EN1=P1^2;

void delay(uint n)
{
	uint i=0;
	uint j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;i<120;j++);
	}
	
}

void Timer0_init()
{
	TMOD=0x01;//选定定时器工作方式1
	TH0=0xd8;//定时10ms
	TL0=0xf0;
	TR0=1;
	IN2=0;
}

//void Overflow_Timer0()
//{
//	schar q;
//		if(TF0==1)
//		{
//			TF0=0;
//			q++;
//		}
//		if(q==14)	
//		{
//			
//			q=0;
//		}
//		
//}

void ISR_init()
{
	EA=1;
	EX0=0;
	ET0=1;
	EX1=0;
	ET1=0;
	ES=0;
}

void ISR_TF0() interrupt 0
{
	schar q;
	TH0=0xd8;
	TL0=0xf0;
	q++;
	if(q==2)
	{
		IN2=~IN2;
		q=0;
	}
}

void motor()
{
	IN1=0;
	IN2=1;
	EN1=1;
}

void main()
{
	Timer0_init();
	ISR_init();
	motor();
}