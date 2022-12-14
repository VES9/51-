/***************************
@Author:ZSX
@Date:2022.9.21.20.59
@Description:PWM pulse speed regulation
@LastEditTime:2022.9.23.15.52
@LastEditors:ZSX
@Filepath:C:\Users\13973\Objects\pwm
***************************/

#include <REGX51.H>
#include <INTRINS.H>
#include <MATH.H>
#define uchar unsigned char
#define uint unsigned int
typedef int i8;
typedef float f8;
typedef char c8;

/***************************
定义特殊寄存器的位变量
***************************/
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
sbit e0=P2^0;
sbit e1=P2^1;
sbit e2=P2^2;
sbit e3=P2^3;
sbit IN1=P3^0;
sbit IN2=P3^1;
sbit EN1=P3^2;

bit flag=0;//
uint PWM=0;//
uchar speed=0;
uchar speedvalue=10;
uchar valueh[]={0xe0,0xf8};
uchar valuel[]={0xc0,0x30};
uchar str0[]={'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'};
uchar str1[]={'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'};

/***************************
毫秒级延时函数
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
void LCDShowInit()
{
//	LCDGotoXY(uchar line,uchar column);
//	LCDPrintstr(uchar *str);
//	LCDGotoXY(uchar line,uchar column);
//	LCDPrintstr(uchar *str);
	uchar i=0;
	uchar j=0;
	str0[0]='@';
	str0[1]='A';
	str0[2]='U';
	str0[3]='T';
	str0[4]='H';
	str0[5]='O';
	str0[6]='R';
	str0[7]=':';
	str0[8]='Z';
	str0[9]='S';
	str0[10]='X';
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

/**************************
定时器0初始化
***************************/
void Timer0_init()
{
	TMOD=0x01;
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	TR0=1;
}

/**************************
定时器1初始化
***************************/
//void Timer1_init()
//{
//	TMOD=0x10;
//	TH1=0;
//	TL1=0;
//	TR1=1;
//}

/**************************
中断初始化
***************************/
void ISR_init()
{
	EA=1;
	ET0=1;
	EX0=0;
	ET1=0;
	EX1=0;
	ES=0;
}

/**************************
定时器0溢出处理
***************************/
#if 0
void OverFlow_Timer0()
{
	uchar p=0;
	if(TF0==1)
	{
		p++;
		TF0=0;
	}
	if(P=10)
	{
		//FUNCTION_0
		delay(2);
		p=0;
	}
}
#endif
/**************************
定时器1溢出处理
***************************/
#if 0
void OverFlow_Timer1()
{
	uchar q=0;
	if(TF1==1)
	{
		q++;
		TF1=0;
	}
	if(q=10)
	{
		//FUNCTION_1
		delay(2);
		q=0;
	}
}
#endif
/**************************
定时器0中断服务
***************************/
void Service_Timer0() interrupt 1
{
//	uchar count=0;
//	TH0=valueh[count];
//	TL0=valueh[count];
//	count++;
	uchar count0=0;
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	count0++;
	if(count0==20)
		count0=0;
	if(count0>=speedvalue)
	{
		EN1=1;
	}
	else
	{
		EN1=0;
	}
	
//	IN2=~IN2;
//	if(count==2)
//	{
//		IN2=~IN2;
//		count=0;
//	}
}

/**************************
定时器1中断服务
***************************/
#if 0
void Service_Timer1() interrupt 3
{
	uchar count1=0;
	TH1=0;
	TL1=0;
	if(count1==20)
	{
		count1=0;
    TR1=0;
		speed=TH0;	
	  speed=(speed<<8)|TL0;
    //	speed+=TL0;	 
	  speed=speed*2.49504;
		flag=~flag;
    TR1=1;
	}
}
#endif
/*
*电机打开
*/
void MotorOpen()
{
	IN1=1;
	IN2=0;
	EN1=1;
}

/*
*电机关闭
*/
void MotorClose()
{
	IN1=0;
	IN2=0;
	EN1=0;
}

/*
*电机加速
*/
void MotorSpeedUp()
{
	if(speedvalue>0)
	{
		speedvalue-=2;
	}
}

/*
*电机减速
*/
void MotorSpeedDown()
{
	if(speedvalue<=20)
	{
		speedvalue+=2;
	}
}

/**************************
按键实现电机开关，加速，
减速功能
***************************/
void Button1()
{
	
	if(e0==0)
	{
		delay(2);
		while(e0==0)
		{
			MotorOpen();
		}//FUNCTION_0:OPEN DC MOTOR
		return;
	}
	if(e1==0)
	{
		delay(2);
		while(e1==0)
		{
			MotorSpeedUp();
		}//FUNCTION_1:SPEED UP
		return;
	}
	if(e2==0)
	{
		delay(2);
		while(e2==0)
		{
			MotorSpeedDown();
		}//FUNCTION_2:SPEED DOWN
		return;
	}
	if(e3==0)
	{
		delay(2);
		while(e3==0)
		{
			MotorClose();
		}//FUNCTION_3:CLOSE DC MOTOR
		return;
	}
	
	
}

/**************************
使用switch实现按键选择功能
***************************/
#if 0
void Button2(uchar keynum2)
{
	uchar i,j=0;
	c8 key=0;
	key=P2&0X0F;
	switch(key)
	{
		case 0x0e:MotorOpen(); break;
		case 0x0d:MotorSpeedUp(); break;
	  case 0x0b:MotorSpeedDown(); break;
	  case 0x07:MotorClose(); break;
  }
}
#end if

/**************************
主函数
***************************/
void main()
{
	Timer0_init();
	LCD1602_init();
  
	ISR_init();
	while(1)
	{LCDShowInit();
		Button1();
	}
  
}