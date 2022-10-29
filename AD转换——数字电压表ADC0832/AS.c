#include <reg52.h>
#include <intrins.h>
#include <0832.h>
#define uchar unsigned char
#define uint unsigned int
uchar dd[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xc6,0xff};

//sbit led=P1^0;
uint ch0=0,ch1=0;


void delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}

void display1(uchar yi,uchar er)
{
  P3=0x01;
  P0=dd[yi];
  delay1ms();
  P0=0xff;

  P3=0x02;
  P0=dd[er]+0x80;
  delay1ms();
  P0=0xff;

}

void display2(uchar san,uchar si)
{
  P3=0x04;
  P0=dd[san];
  delay1ms();
  P0=0xff;

  P3=0x08;
  P0=dd[si];
  delay1ms();
  P0=0xff;
}


void main()
{

  while(1)
   {
   	 //ch0=ADC0832(0)/2.55;
	 ch1=adc0832(1)*1.97;
	 display1(ch1/1000,ch1%1000/100);
	 display2(ch1%100/10,ch1%10);
   }
}