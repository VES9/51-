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

uchar keyboard()
{
	uchar keynum=0;
	P3=0xFF;
	P3_4=0;
	if (P3_0==0){delay();while(P3_0==0)keynum=0;}
	if (P3_1==0){delay();while(P3_1==0)keynum=4;}
	if (P3_2==0){delay();while(P3_2==0)keynum=8;}
	if (P3_3==0){delay();while(P3_3==0)keynum=12;}
	
	P3=0xFF;
	P3_5=0;
	if (P3_0==0){delay();while(P3_0==0)keynum=0;}
	if (P3_1==0){delay();while(P3_1==0)keynum=4;}
	if (P3_2==0){delay();while(P3_2==0)keynum=8;}
	if (P3_3==0){delay();while(P3_3==0)keynum=12;}
	
	P3=0xFF;
	P3_6=0;
	if (P3_0==0){delay();while(P3_0==0)keynum=0;}
	if (P3_1==0){delay();while(P3_1==0)keynum=4;}
	if (P3_2==0){delay();while(P3_2==0)keynum=8;}
	if (P3_3==0){delay();while(P3_3==0)keynum=12;}
	
	P3=0xFF;
	P3_7=0;
	if (P3_0==0){delay();while(P3_0==0)keynum=0;}
	if (P3_1==0){delay();while(P3_1==0)keynum=4;}
	if (P3_2==0){delay();while(P3_2==0)keynum=8;}
	if (P3_3==0){delay();while(P3_3==0)keynum=12;}
	
	return keynum;
}

void seg()
{
//	uchar keynum=3;

	uchar i=0;
		for(i=0;i<8;i++)
	{
		AR=~wei[i];
		AE=display[keynum];
	  delay();
	}
    
	
}

void main()
{
	while(1)
	{
	keyboard();
	seg();
	}
}




