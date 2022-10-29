#include <reg52.h>
#include <intrins.h>
#include <0832.h>
#define uchar unsigned char
#define uint unsigned int

sbit DATO  = P1^3;
sbit DATI	 = P1^2;
sbit CS	 = P1^0;
sbit Clk = P1^1;
uchar dat=0;

unsigned char adc0832(unsigned char CH)
{
	unsigned char i,test,adval;
	adval = 0x00;
	test = 0x00;
	Clk = 0;       //��ʼ��
	DATI = 1;
	_nop_();
	CS = 0;
	_nop_();
	Clk = 1;
	_nop_();
	
	
	if ( CH == 0x00 )      //ͨ��ѡ��
	{
		Clk = 0;
		DATI = 1;      //ͨ��0�ĵ�һλ
		_nop_();
		Clk = 1;
		_nop_();
		Clk = 0;
		DATI = 0;      //ͨ��0�ĵڶ�λ
		_nop_();
		Clk = 1;
		_nop_();
	} 
	else
	{
		Clk = 0;
		DATI = 1;      //ͨ��1�ĵ�һλ
		_nop_();
		Clk = 1;
		_nop_();
		Clk = 0;
		DATI = 1;      //ͨ��1�ĵڶ�λ
		_nop_();
		Clk = 1;
		_nop_();
	}
	
	Clk = 0;
	DATI = 1;
	for( i = 0;i < 8;i++ )      //��ȡǰ8λ��ֵ
	{
		_nop_();
		adval <<= 1;
		Clk = 1;
		_nop_();
		Clk = 0;
		if (DATO)
		adval |= 0x01;
		else
		adval |= 0x00;
	}
	for (i = 0; i < 8; i++)      //��ȡ��8λ��ֵ
	{
		test >>= 1;
		if (DATO)
		test |= 0x80;
		else 
		test |= 0x00;
		_nop_();
		Clk = 1;
		_nop_();
		Clk = 0;
	}
	if (adval == test)      //�Ƚ�ǰ8λ���8λ��ֵ���������ͬ��ȥ����һֱ������ʾΪ�㣬�뽫����ȥ��
	dat = test;
	nop_();
	CS = 1;        //�ͷ�ADC0832
	DATO = 1;
	Clk = 1;
	return dat;
}
//sbit ADC0832_DO  = P1^3;
//sbit ADC0832_DI	 = P1^2;
//sbit ADC0832_CS	 = P1^0;
//sbit ADC0832_CLK = P1^1;
//
//uchar ADC0832(uchar chx) 
//{
//	
//	uchar i=0,data_c=0;
//	if((chx!=0)&&(chx!=1))return 0;
//	ADC0832_CS=0;
//	ADC0832_DO=0;//Ƭѡ,DOΪ����̬
//	_nop_();_nop_();
//	_nop_();_nop_();
//	ADC0832_CLK=0;
//	_nop_();_nop_();
//	ADC0832_DI=1;
//	ADC0832_CLK=1;
//
//	_nop_();_nop_(); //��һ�����壬��ʼλ
//	ADC0832_CLK=0;
//	_nop_();_nop_();
//	ADC0832_DI=1;
//	ADC0832_CLK=1;
//	_nop_();_nop_();//�ڶ�������,DI=1��ʾ˫ͨ������������
//	ADC0832_CLK=0;
//
//	_nop_();_nop_();
//	ADC0832_DI=chx==1?1:0;
//	ADC0832_CLK=1;
//	_nop_();_nop_(); //����������,DI=1��ʾѡ��ͨ��1(CH2)
//	ADC0832_CLK=0;
//	ADC0832_DI=0;
//	ADC0832_DO=1;    //DIתΪ����̬,DO�������̬Ϊ���������׼��
//	/*ʹ��˫ͨ��ʱ��Ҫ���������,������һλ*/
//	//ADC0832_CLK=1;
//	//_nop_();_nop_();
//	//ADC0832_CLK=0;
//	//_nop_();_nop_();
//
//	for (i=0; i<8; i++)
//	{
//		ADC0832_CLK=1;
//		_nop_();_nop_();
//		ADC0832_CLK=0;
//		_nop_();_nop_();
//		data_c=(data_c<<1)|ADC0832_DO;//��ÿ��������½���DO���һλ����,����chΪ8λ��������
//	}
//
//	ADC0832_CS=1;//ȡ��Ƭѡ һ��ת�����ڽ���
//	return data_c;//����
//}