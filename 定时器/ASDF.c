#include <REGX51.H>
#include <intrins.h>
#define uchar unsigned char
sfr AE=0x90;
sfr AR=0xA0;
uchar display[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
uchar wei[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F,0x7F,0x7F};

void delay()		//@12.000MHz
{
	uchar i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 144;
	k = 71;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void _ADC()
{
	uchar i=0;
	for(i=0;i<8;i++)
	{
		AE=display[i];
		AR=~wei[i];
		delay();
	}
}

void Timer_0()
{
	uchar q;
	TMOD=0x00;
	TH0=0xb1;
	TL0=0xe0;
	TR0=1;
	while(1)
	{
	 if(TF0==1)
	 {
		TR0=1;
		TH0=0xb1;
		TL0=0xe0;
		 q++;
	 }
	 if(q==50)
	{
		q=0;
		_ADC();
	}
	
  }
}

void main()
{
	Timer_0();
}