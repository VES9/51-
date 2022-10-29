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
	Clk = 0;       //初始化
	DATI = 1;
	_nop_();
	CS = 0;
	_nop_();
	Clk = 1;
	_nop_();
	
	
	if ( CH == 0x00 )      //通道选择
	{
		Clk = 0;
		DATI = 1;      //通道0的第一位
		_nop_();
		Clk = 1;
		_nop_();
		Clk = 0;
		DATI = 0;      //通道0的第二位
		_nop_();
		Clk = 1;
		_nop_();
	} 
	else
	{
		Clk = 0;
		DATI = 1;      //通道1的第一位
		_nop_();
		Clk = 1;
		_nop_();
		Clk = 0;
		DATI = 1;      //通道1的第二位
		_nop_();
		Clk = 1;
		_nop_();
	}
	
	Clk = 0;
	DATI = 1;
	for( i = 0;i < 8;i++ )      //读取前8位的值
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
	for (i = 0; i < 8; i++)      //读取后8位的值
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
	if (adval == test)      //比较前8位与后8位的值，如果不相同舍去。若一直出现显示为零，请将该行去掉
	dat = test;
	nop_();
	CS = 1;        //释放ADC0832
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
//	ADC0832_DO=0;//片选,DO为高阻态
//	_nop_();_nop_();
//	_nop_();_nop_();
//	ADC0832_CLK=0;
//	_nop_();_nop_();
//	ADC0832_DI=1;
//	ADC0832_CLK=1;
//
//	_nop_();_nop_(); //第一个脉冲，起始位
//	ADC0832_CLK=0;
//	_nop_();_nop_();
//	ADC0832_DI=1;
//	ADC0832_CLK=1;
//	_nop_();_nop_();//第二个脉冲,DI=1表示双通道单极性输入
//	ADC0832_CLK=0;
//
//	_nop_();_nop_();
//	ADC0832_DI=chx==1?1:0;
//	ADC0832_CLK=1;
//	_nop_();_nop_(); //第三个脉冲,DI=1表示选择通道1(CH2)
//	ADC0832_CLK=0;
//	ADC0832_DI=0;
//	ADC0832_DO=1;    //DI转为高阻态,DO脱离高阻态为输出数据作准备
//	/*使用双通道时不要加这个脉冲,否则会错一位*/
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
//		data_c=(data_c<<1)|ADC0832_DO;//在每个脉冲的下降沿DO输出一位数据,最终ch为8位二进制数
//	}
//
//	ADC0832_CS=1;//取消片选 一个转换周期结束
//	return data_c;//返回
//}